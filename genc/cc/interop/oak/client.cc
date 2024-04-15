/* Copyright 2024, The GenC Authors.

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

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "genc/cc/interop/oak/client.h"
#include "cc/client/client.h"

namespace genc {

absl::StatusOr<std::unique_ptr<oak::client::OakClient>> CreateOakClient() {
  // TODO(b/333410413): Do something.
  return absl::UnimplementedError("This functionality is not implemented.");
}

}  // namespace genc
