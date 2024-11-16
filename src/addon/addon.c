#include "./include/utils.h"
#include <node_api.h>

void InitXORFunctions(napi_env env, napi_value exports);
void InitStreamCipherFunctions(napi_env env, napi_value exports);

/** Module Initialization 🚀 */
napi_value Init(napi_env env, napi_value exports) {
    InitXORFunctions(env, exports);
    InitStreamCipherFunctions(env, exports);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
