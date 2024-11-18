#include "../include/middleware_helpers.h"
#include "../include/utils.h"
#include <node_api.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOKEN_SIZE 64

/** @internal Helper function to generate a random string */
void generate_random_string(char *buffer, size_t size) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < size; i++) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buffer[size] = '\0';
}

/** Generate CSRF Token */
napi_value GenerateCSRFToken(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Secret key is required");
        return NULL;
    }

    // Get the secret key
    napi_value secret_key_value = args[0];
    size_t secret_key_length;
    napi_get_value_string_utf8(env, secret_key_value, NULL, 0, &secret_key_length);
    char *secret_key = (char *)malloc(secret_key_length + 1);
    napi_get_value_string_utf8(env, secret_key_value, secret_key, secret_key_length + 1, NULL);

    char random_string[TOKEN_SIZE];
    generate_random_string(random_string, TOKEN_SIZE);

    // HMAC for token (Hash-based message authentication code)
    unsigned char *hmac = HMAC(EVP_sha256(), secret_key, strlen(secret_key),
                               (unsigned char *)random_string, strlen(random_string), NULL, NULL);

    // Convert HMAC to hexadecimal
    char token[TOKEN_SIZE * 2 + 1];
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&token[i * 2], "%02x", hmac[i]);
    }

    napi_value result;
    napi_create_string_utf8(env, token, NAPI_AUTO_LENGTH, &result);

    free(secret_key);
    return result;
}

/** Validate CSRF Token */
napi_value ValidateCSRFToken(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 2) {
        napi_throw_error(env, NULL, "Token and secret key are required");
        return NULL;
    }

    // Get the token
    napi_value token_value = args[0];
    size_t token_length;
    napi_get_value_string_utf8(env, token_value, NULL, 0, &token_length);
    char *token = (char *)malloc(token_length + 1);
    napi_get_value_string_utf8(env, token_value, token, token_length + 1, NULL);

    // Get the secret key
    napi_value secret_key_value = args[1];
    size_t secret_key_length;
    napi_get_value_string_utf8(env, secret_key_value, NULL, 0, &secret_key_length);
    char *secret_key = (char *)malloc(secret_key_length + 1);
    napi_get_value_string_utf8(env, secret_key_value, secret_key, secret_key_length + 1, NULL);

    // Regenerate expected token
    char random_string[TOKEN_SIZE];
    strncpy(random_string, token, TOKEN_SIZE);

    unsigned char *hmac = HMAC(EVP_sha256(), secret_key, strlen(secret_key),
                               (unsigned char *)random_string, strlen(random_string), NULL, NULL);

    char expected_token[TOKEN_SIZE * 2 + 1];
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&expected_token[i * 2], "%02x", hmac[i]);
    }

    napi_value result;
    napi_get_boolean(env, strcmp(token, expected_token) == 0, &result);

    free(token);
    free(secret_key);
    return result;
}