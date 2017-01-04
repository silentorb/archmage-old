create_library(archmage)
require(repoman projection archmage_cpp archmage_loading)

include_directories(
  ${BOOST_PATH}
)

target_link_libraries(archmage ${boost_lib_filesystem} ${boost_lib_regex} ${boost_lib_system})
