# SPDX-License-Identifier: MIT
find_package(json-c REQUIRED)
find_package(safu REQUIRED)

add_library(
  samconf_test_utils STATIC
  private/createMockConfigUtil.c
)

target_include_directories(
  samconf_test_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
)

target_link_libraries(
  samconf_test_utils
  PUBLIC
    samconf
)
