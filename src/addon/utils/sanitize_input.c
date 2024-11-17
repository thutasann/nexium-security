#include "../include/middleware_hepers.h"
#include "../include/utils.h"
#include <node_api.h>
#include <stdlib.h>
#include <string.h>

/** Sanitize Input for express middleware */
napi_value SanitizeInput(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Input string is required");
        return NULL;
    }

    size_t input_len;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &input_len);

    char *input = (char *)malloc(input_len + 1);
    if (!input) {
        napi_throw_error(env, NULL, "Memory allocation failed");
        return NULL;
    }

    napi_get_value_string_utf8(env, args[0], input, input_len + 1, NULL);
    char *sanitized = sanitize_and_escape(input);
    free(input);

    if (!sanitized) {
        napi_throw_error(env, NULL, "Sanitization failed");
        return NULL;
    }

    napi_value result;
    napi_create_string_utf8(env, sanitized, NAPI_AUTO_LENGTH, &result);
    free(sanitized);

    return result;
}