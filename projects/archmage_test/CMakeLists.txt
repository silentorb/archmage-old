create_test(archmage_test)
require(archmage)

link_external_static(googletest gtest)

if (MINGW)
  target_link_libraries(archmage_test "${MYTHIC_DEPENDENCIES}/googletest/lib/libgtest_main.a")
elseif (MSVC)

endif ()
