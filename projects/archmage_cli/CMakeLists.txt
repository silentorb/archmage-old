create_executable(archmage_cli)
require(archmage)

include_directories(
  ${BOOST_PATH}
)
target_link_libraries(archmage_cli ${boost_lib_filesystem} ${boost_lib_system} ${GIT_PATH}/lib/libgit2.dll.a)
