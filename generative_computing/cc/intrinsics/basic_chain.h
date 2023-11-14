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

#include <optional>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "generative_computing/cc/intrinsics/intrinsic_uris.h"
#include "generative_computing/cc/runtime/intrinsic_handler.h"
#include "generative_computing/proto/v0/computation.pb.h"

#ifndef GENERATIVE_COMPUTING_CC_INTRINSICS_BASIC_CHAIN_H_
#define GENERATIVE_COMPUTING_CC_INTRINSICS_BASIC_CHAIN_H_

namespace generative_computing {
namespace intrinsics {
class BasicChain : public ControlFlowIntrinsicHandlerBase {
 public:
  BasicChain() : ControlFlowIntrinsicHandlerBase(kBasicChain) {}
  virtual ~BasicChain() {}
  absl::Status CheckWellFormed(const v0::Intrinsic& intrinsic_pb) const final;
  absl::StatusOr<ValueRef> ExecuteCall(const v0::Intrinsic& intrinsic_pb,
                                       std::optional<ValueRef> arg,
                                       Context* context) const final;
};
}  // namespace intrinsics
}  // namespace generative_computing

#endif  // GENERATIVE_COMPUTING_CC_INTRINSICS_BASIC_CHAIN_H_
