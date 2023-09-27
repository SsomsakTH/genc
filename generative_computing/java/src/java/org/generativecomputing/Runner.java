/* Copyright 2023, The Generative Computing Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License
==============================================================================*/

package org.generativecomputing;

/** Interface for running Generative Computing computations. */
public final class Runner {
  public static Runner create(Computation computation) {
    return new Runner(computation, Executor.create());
  }

  public static Runner create(Computation computation, long executorHandle) {
    return new Runner(computation, Executor.create(executorHandle));
  }

  public String call(Value[] args) {
    if (args.length != 1) {
      throw new IllegalArgumentException("Input args should be exactly size 1");
    }
    OwnedValueId argVal = this.executor.createValue(args[0]);
    OwnedValueId resultVal = this.executor.createCall(this.computationVal.ref(), argVal.ref());
    Value result = this.executor.materialize(resultVal.ref());
    this.executor.dispose(argVal.ref());
    this.executor.dispose(resultVal.ref());
    return result.getStr();
  }

  private Runner(Computation computation, Executor executor) {
    this.computation = computation;
    this.executor = executor;
    Value computationValue = Value.newBuilder().setComputation(this.computation).build();
    this.computationVal = this.executor.createValue(computationValue);
  }

  private final Computation computation;
  private final Executor executor;
  private final OwnedValueId computationVal;
}
