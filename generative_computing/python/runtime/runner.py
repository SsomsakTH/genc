# Copyright 2023, The Generative Computing Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Libraries fo constructing runners for executing generative computations."""

from generative_computing.cc.runtime import executor_bindings
from generative_computing.proto.v0 import computation_pb2 as pb
from generative_computing.proto.v0 import executor_pb2


def _to_value_proto(arg):
  """Creates an executor value proto that corresponds to the given argument.

  Args:
    arg: A regular Python argument.

  Returns:
    A corresponding instance of `executor_pb2.Value`.

  Raises:
    TypeError: if the argument is of an unsupported type.
  """
  if isinstance(arg, pb.Computation):
    return executor_pb2.Value(computation=arg)
  if isinstance(arg, str):
    return executor_pb2.Value(**{'str': arg})
  raise TypeError('Unsupported Python argument type {}.'.format(type(arg)))


def _from_value_proto(result_pb):
  """Creates a Python value object that corresponds to the given value proto.

  Args:
    result_pb: An instance of `executor_pb2.Value`.

  Returns:
    A corresponding Python object.

  Raises:
    TypeError: if the `result_pb` is of an unsupported type.
  """
  which_result = result_pb.WhichOneof('value')
  if not which_result:
    return None
  if which_result == 'str':
    return result_pb.str
  raise TypeError('Unsupported value proto type {}.'.format(which_result))


class Runner(object):
  """Represents a runner."""

  def __init__(self, comp_pb: pb.Computation):
    """Construct a runner for the given computation proto.

    Args:
      comp_pb: The computation proto to contruct the runner for.
    """
    self._executor = executor_bindings.create_default_local_executor()
    self._comp_pb = comp_pb
    self._comp_val = self._executor.create_value(_to_value_proto(self._comp_pb))

  def __call__(self, *args, **kwargs):
    """Invoke the runner on a given set of arguments.

    This is a blocking call that performs the computation synchronously.

    Args:
      *args: Positonal args.
      **kwargs: Keyword args.

    Returns:
      The result of the computation, computed synchronously.
    """
    if kwargs:
      raise ValueError('Keyword arguments are not currently supported.')
    if not args:
      arg_val = None
    elif len(args) > 1:
      elements = [self._executor.create_value(_to_value_proto(x)) for x in args]
      arg_val = self._executor.create_struct([x.ref for x in elements])
    else:
      arg_val = self._executor.create_value(_to_value_proto(args[0]))
    result_val = self._executor.create_call(
        self._comp_val.ref, arg_val.ref if arg_val else None
    )
    result_pb = self._executor.materialize(result_val.ref)
    return _from_value_proto(result_pb)