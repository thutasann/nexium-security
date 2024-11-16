#include "../include/utils.h"
#include "../include/xor_helpers.h"
#include <node_api.h>
#include <stdlib.h>
#include <time.h>

/** XOR Encrypt */
napi_value XOREncrypt(napi_env env, napi_callback_info info) {
    napi_value args[2], result;
    size_t argc = 2, input_len, key_len;

    // Parse arguments
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    if (argc < 2) {
        napi_throw_error(env, NULL, "Two arguments are required: input and key.");
        return NULL;
    }

    // Get input and key
    napi_get_value_string_utf8(env, args[0], NULL, 0, &input_len);
    napi_get_value_string_utf8(env, args[1], NULL, 0, &key_len);

    char *input = (char *)calloc(input_len + 1, sizeof(char));
    char *key = (char *)calloc(key_len + 1, sizeof(char));
    unsigned char *encrypted = (unsigned char *)calloc(input_len + 1, sizeof(unsigned char));

    napi_get_value_string_utf8(env, args[0], input, input_len + 1, NULL);
    napi_get_value_string_utf8(env, args[1], key, key_len + 1, NULL);

    // Encrypt
    xor_encrypt(input, key, encrypted);

    // Encode encrypted result to Base64
    char *base64_output = base64_encode(encrypted, input_len);

    // Return Base64-encoded encrypted value
    napi_create_string_utf8(env, base64_output, NAPI_AUTO_LENGTH, &result);

    // Free allocated memory
    free(input);
    free(key);
    free(encrypted);
    free(base64_output);

    return result;
}

/** XOR Decrypt */
napi_value XORDecrypt(napi_env env, napi_callback_info info) {
    napi_value args[2], result;
    size_t argc = 2, input_len, key_len, decoded_len;

    // Parse arguments
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    if (argc < 2) {
        napi_throw_error(env, NULL, "Two arguments are required: input and key.");
        return NULL;
    }

    // Get input and key
    napi_get_value_string_utf8(env, args[0], NULL, 0, &input_len);
    napi_get_value_string_utf8(env, args[1], NULL, 0, &key_len);

    char *input = (char *)calloc(input_len + 1, sizeof(char));
    char *key = (char *)calloc(key_len + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[0], input, input_len + 1, NULL);
    napi_get_value_string_utf8(env, args[1], key, key_len + 1, NULL);

    // Decode Base64 input to get original encrypted binary
    unsigned char *decoded_input = base64_decode(input, &decoded_len);
    char *decrypted = (char *)calloc(decoded_len + 1, sizeof(char));

    // Decrypt
    xor_decrypt(decoded_input, decoded_len, key, decrypted);

    // Return decrypted value
    napi_create_string_utf8(env, decrypted, NAPI_AUTO_LENGTH, &result);

    // Free allocated memory
    free(input);
    free(key);
    free(decoded_input);
    free(decrypted);

    return result;
}