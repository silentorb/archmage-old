#include <algorithm>
#include <boost/filesystem/operations.hpp>
#include "pathing.h"

using namespace std;

namespace pathing {

  const std::string join(const std::string &first, const std::string &second) {
    if (first.size() == 0)
      return second;

    if (second.size() == 0)
      return first;

    auto a = first[first.size() - 1];
    auto b = second[second.size() - 1];
    if (a != '/' && b != '/')
      return first + "/" + second;

    if (a == '/' && b == '/')
      return first + "/" + second.substr(1);

    return first + second;
  }

  const std::string join(std::initializer_list<std::string> tokens) {
    string result;
    for (auto &token: tokens) {
      result = join(result, token);
    }
  }

  const std::string resolve(const std::string path) {
    string result = boost::filesystem::canonical(path).string();
    std::replace(result.begin(), result.end(), '\\', '/');
    return result;
  }

  const std::string relative(const string &workspace_path, const string &path) {
    return pathing::resolve(pathing::join(workspace_path, path));
//    string joined = (workspace_path / path).string();
//    std::replace(joined.begin(), joined.end(), '\\', '/');
////    auto joined = filesystem::path(joined_path);
//
//    string result = filesystem::canonical(joined).string();
//    std::replace(result.begin(), result.end(), '\\', '/');
//    return result;
  }
}