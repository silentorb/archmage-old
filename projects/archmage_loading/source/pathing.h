#pragma once

#include <string>

namespace pathing {

  const std::string join(const std::string &first, const std::string &second);
  const std::string join(std::initializer_list<std::string> tokens);
  const std::string resolve(const std::string path);
  const std::string relative(const std::string &workspace_path, const std::string &path);
}