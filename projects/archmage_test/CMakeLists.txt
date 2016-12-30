create_test(archmage_test)
require(archmage repoman)

link_external_static(googletest gtest)
target_link_libraries(archmage_test ${boost_lib_filesystem} ${boost_lib_system} ${GIT_PATH}/lib/libgit2.dll.a)

include_directories(
  ${BOOST_PATH}
)

if (MINGW)
  target_link_libraries(archmage_test "${MYTHIC_DEPENDENCIES}/googletest/lib/libgtest_main.a")
elseif (MSVC)

endif ()

add_resources(resources)