#include "./include/utils.h"
#include <node_api.h>

/** Init Middleware Functions */
void InitMiddlewareFunctions(napi_env env, napi_value exports) {
    napi_value sanitize_fn;
    napi_create_function(env, NULL, 0, SanitizeInput, NULL, &sanitize_fn);
    napi_set_named_property(env, exports, "sanitizeInput", sanitize_fn);
}
