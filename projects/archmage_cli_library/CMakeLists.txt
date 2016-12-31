create_library(archmage_cli_library)
require(archmage archmage_reporting)

include_directories(
  ${BOOST_PATH}
)
target_link_libraries(archmage_cli_library ${boost_lib_filesystem} ${boost_lib_system} ${GIT_PATH}/lib/libgit2.dll.a)
