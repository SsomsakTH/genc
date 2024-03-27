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

#ifndef GENERATIVE_COMPUTING_JAVA_SRC_JAVA_ORG_GENERATIVECOMPUTING_RUNTIME_JNI_OWNED_VALUE_ID_JNI
#define GENERATIVE_COMPUTING_JAVA_SRC_JAVA_ORG_GENERATIVECOMPUTING_RUNTIME_JNI_OWNED_VALUE_ID_JNI

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_org_generativecomputing_OwnedValueId_ref(JNIEnv *,
                                                                      jclass,
                                                                      jlong);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
#endif  // GENERATIVE_COMPUTING_JAVA_SRC_JAVA_ORG_GENERATIVECOMPUTING_RUNTIME_JNI_OWNED_VALUE_ID_JNI