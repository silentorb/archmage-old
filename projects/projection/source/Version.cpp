#include <regex>
#include "Version.h"
#include <boost/regex.hpp>

using namespace std;

namespace projection {

  Version::Version(const std::string &source) {
    boost::regex pattern{R"(^(\d+)(?:\.(\d+))?(?:\.(\d+))?(?:\-(\w+))?$)"};
    boost::smatch result;
    if (!boost::regex_search(source, result, pattern))
      throw Invalid_Version_Format(source);

    auto x = result.size();
    major = stoul(result[1]);
    if (result[2].matched) {
      minor = stoul(result[2]);

      if (result[3].matched) {
        patch = stoul(result[3]);
      }
    }

    if (result[4].matched) {
      branch = result[4];
    }
  }

  bool Version::matches(const Version &version) const {
    return version.major == major
           && version.minor == minor;
  }

  Version_Range::Version_Range(const std::string &pattern) {
    auto version = Version(pattern);
    internal = shared_ptr<Version_Range_Internal>(new Single_Version_Range(version));
  }

  bool Single_Version_Range::matches(const Version &version) const {
    return version.matches(this->version);
  }

  const std::string Version::get_string() const {
    auto result = to_string(major);

    if (minor != UNDEFINED)
      result += "." + to_string(minor);

    if (patch != UNDEFINED)
      result += "." + to_string(patch);

    return result;
  }

  const std::string Version::get_full_string() const {
    return to_string(major)
           + "." + to_string(minor != UNDEFINED ? minor : 0)
           + "." + to_string(patch != UNDEFINED ? patch : 0);
  }
}