#include "Version.h"
#include <boost/regex.hpp>

namespace projection {

  Version::Version(const std::string &pattern) {

  }

  bool Version::matches(const Version &version) const {
    return version.primary == primary
           && version.secondary == secondary;
  }

  bool Single_Version_Range::matches(const Version &version) {
    return version.matches(this->version);
  }
}