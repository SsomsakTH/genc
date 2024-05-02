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

#ifndef GENC_C_INTEROP_OAK_OAK_API_H_
#define GENC_C_INTEROP_OAK_OAK_API_H_

#include <stddef.h>
#include <stdint.h>

// NOTE: Intended use of this API for interoperability with Oak and Confidential
// Computing:
//
// 1. The caller is a process running in a TEE in a Confidential Space VM that
//    exposes an instance of `oak.session.v1.UnarySession` to its clients. The
//    remote clients run the Oak protocol (using the Oak client library).
//
// 2. Upon starting, the caller should call to `oak_generate_hpke_key_pair()`,
//    which obtains a key pair by a call to Oak's crypto code, presumably from
//    `oak_containers_orchestrator/src/crypto.rs`. The returned key pair is
//    packaged in the `OakHpkeKeyPair` structure and returned to the caller.
//    The caller treats it as an opaque structure, used as an argument to the
//    subsequent encryption/decryption and evidence creation calls. The caller
//    takes ownership of the structrue, and calls `oak_delete_hpke_key_pair` to
//    dispose of it later when no longer needed.
//
// 3. Upon receiving the `GenEndorsedEvidence` call from a remote client, the
//    caller first calls `oak_get_public_key`, passing the key pair as an
//    argument, to extract a key that is used as a nonce for a subsequent call
//    to the Confidential Space attestation API. Once it gets the attestation
//    report in the form of a JWT token, the caller passes the token bytes in a
//    call to `oak_create_endorsed_evidence` to producte the endorsed evidence
//    proto that will be returned to the client.
//
// 4. Upon receiving `Invoke` client call, the caller uses `oak_decrypt_request`
//    to decrypt the request, and `oak_encrypt_response` to encrypt the reply.

// NOTE: The definitions in this file can be re-generated by entering the
// corresponding Rust directory (`rust/interop/oak`) and calling the following
// command: `cbindgen --crate oak_api --output oak_api.h`. Be sure to retain
// the copyright notice and all the comments in this file when using this tool.

// A data structure that represents a key pair for HPKE, holding information
// associated with the `EncryptionKeyHandle` in Oak. The inside of this
// structure is opaque to the caller. The caller uses it only as an argument
// to the API below.
struct OakHpkeKeyPair {
  // TODO(b/333410413): Replace this.
  int32_t boo;
};

extern "C" {

// Creates a key pair for HPKE that will be subsequently used to establish
// encrypted communication. Returns `nullptr` if unsuccessful. Caller takes
// ownership of the memory, and must later call `oak_delete_hpke_key_pair`
// to properly dispose of it (don't just call `delete`).
extern OakHpkeKeyPair *oak_generate_hpke_key_pair();

// Deletes a key pair previously allocated with `oak_generate_hpke_key_pair`
// and relinquishes ownership of the memory.
extern void oak_delete_hpke_key_pair(OakHpkeKeyPair *key_pair);

// TODO(b/333410413): Define the rest of this API, as follows:
//
// Returns the public key from the key pair, in the form required to pass as a
// nonce for attestation, as a buffer with serialized bytes. Returns `nullptr`
// if unsuccessful. Caller retains ownership of the key pair, and takes
// ownership of the returned buffer.
// `extern ... oak_get_public_key(...);`
//
// Constructs an instance of `com.google.oak.session.v1.EndorsedEvidence`, and
// returns it as a buffer with serialized bytes, based on the attestation
// report passed here as a serialized bytes representing the JWT token obtained
// from Confidential Space. Returns `nullptr` if unsuccessful. Caller retains
// ownership of the report, and takes ownership of the returned buffer.
// `extern ... oak_create_endorsed_evidence(...);`
//
// Decrypts an instance of `oak.crypto.v1.EncryptedRequest` proto, passed as a
// buffer with serialized bytes. Returns decrypted bytes as a buffer, or
// `nullptr` if unsuccessful. Caller retains ownership of the key pair and the
// request, and takes ownership of the returned buffer.
// `extern ... oak_decrypt_request(...);`
//
// Encrypts an instance of `oak.crypto.v1.EncryptedResponse` proto, passed as a
// buffer with serialized bytes. Returns encrypted bytes as a buffer, or
// `nullptr` if unsuccessful. Caller retains ownership of the key pair and the
// response, and takes ownership of the returned buffer.
// `extern ... oak_encrypt_response(...);`

}  // extern "C"

#endif  // GENC_C_INTEROP_OAK_OAK_API_H_