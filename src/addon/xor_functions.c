#include "./include/utils.h"
#include <node_api.h>

/** Init XOR functions */
void InitXORFunctions(napi_env env, napi_value exports) {
    napi_value encryptFn, decryptFn;
    napi_create_function(env, NULL, 0, XOREncrypt, NULL, &encryptFn);
    napi_create_function(env, NULL, 0, XORDecrypt, NULL, &decryptFn);

    napi_set_named_property(env, exports, "xor_encrypt", encryptFn);
    napi_set_named_property(env, exports, "xor_decrypt", decryptFn);
}
