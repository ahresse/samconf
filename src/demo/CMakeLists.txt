# SPDX-License-Identifier: MIT
add_executable(
  samprobe
  samprobe.c
)

target_link_libraries(
  samprobe
  PRIVATE
    samconf
)

if (INSTALL_SAMCONF_DEMOS)
  install(TARGETS samprobe DESTINATION ${CMAKE_INSTALL_BINDIR})
endif (INSTALL_SAMCONF_DEMOS)
