#ifndef UTILS_H
#define UTILS_H

#include <node_api.h>

// ------ XOR Functions
napi_value XOREncrypt(napi_env env, napi_callback_info info);
napi_value XORDecrypt(napi_env env, napi_callback_info info);

// ------ Stream Cipher Functions
napi_value StreamCipherEncrypt(napi_env env, napi_callback_info info);
napi_value StreamCipherDecrypt(napi_env env, napi_callback_info info);

// ------ Store Secret
napi_value StoreSecret(napi_env env, napi_callback_info info);
napi_value RetrieveSecret(napi_env env, napi_callback_info info);

// ------- Middleware Functions
napi_value SanitizeInput(napi_env env, napi_callback_info info);

#endif
