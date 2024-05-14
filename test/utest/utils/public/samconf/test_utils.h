// SPDX-License-Identifier: MIT
#pragma once

#include <json-c/json.h>
#include <samconf/samconf.h>

samconfConfigStatusE_t samconfUtilCreateMockConfig(json_object *jobj, bool isSigned, samconfConfig_t *config);
samconfConfigStatusE_t samconfUtilCreateMockConfigFromStr(const char *jstr, bool isSigned, samconfConfig_t *config);
