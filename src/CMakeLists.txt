# SPDX-License-Identifier: MIT
include(weak_library.cmake)
include(static_from_shared.cmake)

if (SAMCONF_DEMOS)
  add_subdirectory(demo)
endif (SAMCONF_DEMOS)
add_subdirectory(samconf)

if (INSTALL_SAMCONF_TOOLS)
  install(FILES ${PROJECT_SOURCE_DIR}/src/signature.sh
          PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
          DESTINATION ${CMAKE_INSTALL_BINDIR})
endif (INSTALL_SAMCONF_TOOLS)
