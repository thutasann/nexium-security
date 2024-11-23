#include "../include/utils.h"
#include <node_api.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SESSION_ID_LENGTH 32
#define MAX_SESSIONS 1024
#define SESSION_TIMEOUT 3600 // 1 hour in seconds

typedef struct {
    char session_id[SESSION_ID_LENGTH + 1];
    time_t created_at;
} session_t;

static session_t session_store[MAX_SESSIONS];

/** Generate a secure randome session ID */
napi_value GenerateSessionId(napi_env env, napi_callback_info info) {
    unsigned char buffer[SESSION_ID_LENGTH / 2]; // Only need half the length since each byte becomes two hex digits
    char session_id[SESSION_ID_LENGTH + 1];      // +1 for the null terminator

    // Generate secure random bytes
    if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
        napi_throw_error(env, NULL, "Failed to generate secure random bytes for session ID");
        return NULL;
    }

    // Convert bytes to a hex string
    for (int i = 0; i < sizeof(buffer); i++) {
        sprintf(&session_id[i * 2], "%02x", buffer[i]);
    }
    session_id[SESSION_ID_LENGTH] = '\0'; // Ensure null termination

    // Return the session ID to Node.js
    napi_value result;
    napi_create_string_utf8(env, session_id, NAPI_AUTO_LENGTH, &result);
    return result;
}

/** Store Session */
napi_value StoreSession(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Session ID is required");
        return NULL;
    }

    size_t session_id_length;
    char session_id[SESSION_ID_LENGTH + 1];
    napi_get_value_string_utf8(env, args[0], session_id, sizeof(session_id), &session_id_length);

    // Find an empty slot
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (session_store[i].session_id[0] == '\0') {
            strncpy(session_store[i].session_id, session_id, SESSION_ID_LENGTH);
            session_store[i].created_at = time(NULL);
            napi_value result;
            napi_get_boolean(env, 1, &result);
            return result;
        }
    }

    napi_throw_error(env, NULL, "Session store is full");
    return NULL;
}

/** Validate Session */
napi_value ValidateSession(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Session ID is required");
        return NULL;
    }

    size_t session_id_length;
    char session_id[SESSION_ID_LENGTH + 1];
    napi_get_value_string_utf8(env, args[0], session_id, sizeof(session_id), &session_id_length);

    time_t now = time(NULL);
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (strncmp(session_store[i].session_id, session_id, SESSION_ID_LENGTH) == 0) {
            if ((now - session_store[i].created_at) <= SESSION_TIMEOUT) {
                napi_value result;
                napi_get_boolean(env, 1, &result);
                return result;
            } else {
                memset(&session_store[i], 0, sizeof(session_t)); // Expire session
                napi_value result;
                napi_get_boolean(env, 0, &result);
                return result;
            }
        }
    }

    napi_value result;
    napi_get_boolean(env, 0, &result);
    return result;
}
