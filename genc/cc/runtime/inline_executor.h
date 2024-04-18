/* Copyright 2023, The GenC Authors.

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

#ifndef GENC_CC_RUNTIME_INLINE_EXECUTOR_H_
#define GENC_CC_RUNTIME_INLINE_EXECUTOR_H_

#include <memory>

#include "absl/status/statusor.h"
#include "genc/cc/runtime/executor.h"
#include "genc/cc/runtime/intrinsic_handler.h"
#include "genc/cc/runtime/threading.h"

namespace genc {

// Creates an executor that specializes in handling inline intrinsic calls.
absl::StatusOr<std::shared_ptr<Executor>> CreateInlineExecutor(
    std::shared_ptr<IntrinsicHandlerSet> handler_set,
    std::shared_ptr<ThreadPool> thread_pool = nullptr);

}  // namespace genc

#endif  // GENC_CC_RUNTIME_INLINE_EXECUTOR_H_
