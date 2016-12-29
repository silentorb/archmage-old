create_library(projection)

include_directories(
  ${BOOST_PATH}
  ${RAPIDJSON_PATH}/include
)

target_link_libraries(projection ${boost_lib_filesystem} ${boost_lib_regex} ${boost_lib_system})
