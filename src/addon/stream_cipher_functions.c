#include "./include/utils.h"
#include <node_api.h>

/** Init Stream Cipher functions */
void InitStreamCipherFunctions(napi_env env, napi_value exports) {
    napi_value encrypt_fn, decrypt_fn;
    napi_create_function(env, NULL, 0, StreamCipherEncrypt, NULL, &encrypt_fn);
    napi_create_function(env, NULL, 0, StreamCipherDecrypt, NULL, &decrypt_fn);

    napi_set_named_property(env, exports, "stream_encrypt", encrypt_fn);
    napi_set_named_property(env, exports, "stream_decrypt", decrypt_fn);
}
