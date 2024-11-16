#include "../include/stream_cipher.h"
#include "../include/utils.h"
#include <node_api.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Stream Cipher Encrypt */
napi_value StreamCipherEncrypt(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    // Get input and key
    size_t input_len, key_len;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &input_len);
    napi_get_value_string_utf8(env, args[1], NULL, 0, &key_len);
    char *input = (char *)malloc(input_len + 1);
    char *key = (char *)malloc(key_len + 1);
    napi_get_value_string_utf8(env, args[0], input, input_len + 1, NULL);
    napi_get_value_string_utf8(env, args[1], key, key_len + 1, NULL);

    // Perform encryption
    unsigned char S[256];
    rc4_key_setup(S, (unsigned char *)key, key_len);
    unsigned char *output = (unsigned char *)malloc(input_len + 1);
    rc4_crypt(S, (unsigned char *)input, output, input_len);

    // Encode output as base64 for safe text representation
    char *base64_output = stream_base64_encode(output, input_len);

    // Return encrypted string as base64
    napi_value result;
    napi_create_string_utf8(env, base64_output, strlen(base64_output), &result);

    free(input);
    free(key);
    free(output);
    free(base64_output);
    return result;
}

/** Stream Cipher Decrypt */
napi_value StreamCipherDecrypt(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    // Get input and key
    size_t input_len, key_len;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &input_len);
    napi_get_value_string_utf8(env, args[1], NULL, 0, &key_len);
    char *input = (char *)malloc(input_len + 1);
    char *key = (char *)malloc(key_len + 1);
    napi_get_value_string_utf8(env, args[0], input, input_len + 1, NULL);
    napi_get_value_string_utf8(env, args[1], key, key_len + 1, NULL);

    // Decode input from base64
    size_t decoded_len;
    unsigned char *decoded_input = stream_base64_decode(input, &decoded_len);

    // Perform decryption
    unsigned char S[256];
    rc4_key_setup(S, (unsigned char *)key, key_len);
    unsigned char *output = (unsigned char *)malloc(decoded_len + 1);
    rc4_crypt(S, decoded_input, output, decoded_len);

    // Return decrypted string as UTF-8
    napi_value result;
    napi_create_string_utf8(env, (char *)output, decoded_len, &result);

    free(input);
    free(key);
    free(decoded_input);
    free(output);
    return result;
}
