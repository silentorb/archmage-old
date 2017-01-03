create_executable(archmage_cli)
require(archmage_cli_library)

include_directories(
  ${BOOST_PATH}
)
target_link_libraries(archmage_cli ${boost_lib_regex} ${boost_lib_filesystem} ${boost_lib_system} ${GIT_PATH}/lib/libgit2.dll.a)

set_target_properties(archmage_cli
  PROPERTIES OUTPUT_NAME arch
  )