create_library(projection_cpp)
require(projection)

include_directories(
  ${BOOST_PATH}
  ${RAPIDJSON_PATH}/include
)

target_link_libraries(projection_cpp ${boost_lib_filesystem} ${boost_lib_regex} ${boost_lib_system})
