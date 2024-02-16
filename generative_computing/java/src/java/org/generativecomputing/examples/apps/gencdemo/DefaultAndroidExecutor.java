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

package org.generativecomputing.examples.apps.gencdemo;

import android.content.Context;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import org.chromium.net.CronetEngine;
import src.java.org.generativecomputing.interop.backends.googleai.GoogleAiClient;
import src.java.org.generativecomputing.interop.backends.openai.OpenAiClient;
import src.java.org.generativecomputing.interop.network.CronetEngineProvider;
import src.java.org.generativecomputing.interop.network.HttpClientImpl;

/**
 * An executor used in Generative Computing demos on Android. This contains clients and other
 * objects generally used across different demos. Please use this as a reference example to create
 * your own executor for your use-cases.
 */
public final class DefaultAndroidExecutor {
  public DefaultAndroidExecutor(Context context) {
    cronetEngine = CronetEngineProvider.createCronetEngine(context);
    cronetCallbackExecutorService = Executors.newFixedThreadPool(THREADPOOL_SIZE);
    httpClient = new HttpClientImpl(cronetEngine, cronetCallbackExecutorService);
    openAiClient = new OpenAiClient(httpClient, OPENAI_SERVER_URL, OPEN_AI_API_KEY);
    googleAiClient = new GoogleAiClient(httpClient);
    executorHandle = createAndroidExecutor(openAiClient, googleAiClient);
  }

  public long getExecutorHandle() {
    return executorHandle;
  }

  public long cleanupAndroidExecutor() {
    return cleanupAndroidExecutorState();
  }

  // Objects are referenced in C++ over JNI.
  public OpenAiClient openAiClient;
  public GoogleAiClient googleAiClient;

  private static final int THREADPOOL_SIZE = 4;
  private static final String OPENAI_SERVER_URL = "https://api.openai.com/v1/chat/completions";
  // Fill in Open AI API key.
  private static final String OPEN_AI_API_KEY = "";

  private final CronetEngine cronetEngine;
  private final ExecutorService cronetCallbackExecutorService;
  private final HttpClientImpl httpClient;
  private final long executorHandle;

  private native long createAndroidExecutor(
      OpenAiClient openAiClient, GoogleAiClient googleAiClient);

  private native long cleanupAndroidExecutorState();

  static {
    System.loadLibrary("app");
  }
}
