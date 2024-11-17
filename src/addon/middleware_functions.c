#include "./include/utils.h"
#include <node_api.h>

/** Init Middleware Functions */
void InitMiddlewareFunctions(napi_env env, napi_value exports) {
    napi_value sanitize_fn;
    napi_create_function(env, NULL, 0, SanitizeInput, NULL, &sanitize_fn);
    napi_set_named_property(env, exports, "sanitizeInput", sanitize_fn);

    napi_value setIPsFn, setDomainsFn, filterFn;
    napi_create_function(env, NULL, 0, set_blacklisted_ips, NULL, &setIPsFn);
    napi_set_named_property(env, exports, "setBlacklistedIPs", setIPsFn);
    napi_create_function(env, NULL, 0, set_malicious_domains, NULL, &setDomainsFn);
    napi_set_named_property(env, exports, "setMaliciousDomains", setDomainsFn);
    napi_create_function(env, NULL, 0, filter_request, NULL, &filterFn);
    napi_set_named_property(env, exports, "filterRequest", filterFn);
}
