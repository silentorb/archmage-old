create_library(archmage_reporting)
require(repoman projection)

include_directories(
  ${BOOST_PATH}
)

target_link_libraries(archmage_reporting ${boost_lib_filesystem} ${boost_lib_regex} ${boost_lib_system})
