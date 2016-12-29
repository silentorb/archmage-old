#pragma once

#include <string>
#include "Library.h"

namespace archmage {

  Project &load_project_from_string(const std::string &json, Library &library);
  Project &load_project(const std::string &filename, Library &library);
  Project &load_project_from_file(const std::string &path, Library &library);
  void reference_dependency(const std::string &name, Library &library);
}