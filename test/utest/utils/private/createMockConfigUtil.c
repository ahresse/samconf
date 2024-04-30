// SPDX-License-Identifier: MIT
#include <safu/common.h>
#include <safu/log.h>

#include "samconf/json_backend.h"
#include "samconf/test_utils.h"

samconfConfigStatusE_t samconfUtilCreateMockConfig(json_object *jobj, bool isSigned, samconfConfig_t *config) {
    int n;
    samconfConfigStatusE_t result = SAMCONF_CONFIG_OK;
    samconfConfig_t *subconfig;
    json_object *newJobj;
    const char *key;
    struct lh_entry *entry;

    config->isSigned = isSigned;

    json_type type = json_object_get_type(jobj);
    switch (type) {
        case json_type_object:
            config->type = SAMCONF_CONFIG_VALUE_OBJECT;
            entry = json_object_get_object(jobj)->head;
            while (entry) {
                key = (char *)entry->k;
                newJobj = (json_object *)entry->v;
                if (newJobj == NULL) {
                    safuLogErr("Failed to load Object from Map");
                    result = SAMCONF_CONFIG_PARSE_ERROR;
                    break;
                }
                entry = entry->next;
                result = samconfConfigNew(&subconfig);
                if (result != SAMCONF_CONFIG_OK) {
                    break;
                }
                subconfig->key = strdup(key);
                result = samconfUtilCreateMockConfig(newJobj, isSigned, subconfig);
                if (result != SAMCONF_CONFIG_OK) {
                    samconfConfigDelete(subconfig);  // ensuring cleanup of unlinked subconfig
                    break;
                }
                result = samconfConfigAdd(config, subconfig);
                if (result != SAMCONF_CONFIG_OK) {
                    samconfConfigDelete(subconfig);  // ensuring cleanup of unlinked subconfig
                    break;
                }
            }
            break;

        case json_type_array:
            config->type = SAMCONF_CONFIG_VALUE_ARRAY;
            n = json_object_array_length(jobj);
            for (int idx = 0; idx < n; idx++) {
                newJobj = json_object_array_get_idx(jobj, idx);
                if (newJobj == NULL) {
                    result = SAMCONF_CONFIG_PARSE_ERROR;
                    safuLogErr("Failed to load Object from Array");
                    break;
                }
                result = samconfConfigNew(&subconfig);
                if (result != SAMCONF_CONFIG_OK) {
                    break;
                }
                result = samconfUtilCreateMockConfig(newJobj, isSigned, subconfig);
                if (result != SAMCONF_CONFIG_OK) {
                    samconfConfigDelete(subconfig);  // ensuring cleanup of unlinked subconfig
                    break;
                }
                result = samconfConfigAdd(config, subconfig);
                if (result != SAMCONF_CONFIG_OK) {
                    samconfConfigDelete(subconfig);  // ensuring cleanup of unlinked subconfig
                    break;
                }
                subconfig->key = safuAllocMem(NULL, DECIMAL_DIGITS_BOUND(idx));
                snprintf(subconfig->key, DECIMAL_DIGITS_BOUND(idx), "%i", idx);
            }
            break;

        case json_type_string:
            result = samconfConfigSetString(config, json_object_get_string(jobj));
            break;
        case json_type_int:
            result = samconfConfigSetInt(config, json_object_get_int(jobj));
            break;
        case json_type_boolean:
            result = samconfConfigSetBool(config, json_object_get_boolean(jobj));
            break;
        case json_type_double:
            result = samconfConfigSetReal(config, json_object_get_double(jobj));
            break;
        default:
            break;
    }

    return result;
}

samconfConfigStatusE_t samconfUtilCreateMockConfigFromStr(const char *jstr, bool isSigned, samconfConfig_t *config) {
    samconfConfigStatusE_t result = SAMCONF_CONFIG_OK;
    json_object *testJobj = NULL;

    testJobj = json_tokener_parse(jstr);
    result = samconfUtilCreateMockConfig(testJobj, isSigned, config);
    json_object_put(testJobj);

    return result;
}
