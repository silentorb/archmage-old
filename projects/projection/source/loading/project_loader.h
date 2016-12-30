#pragma once

#include <string>
#include "Library.h"
#include "Project_Source.h"

namespace projection {

  Project &load_project_from_string(const std::string &json, Project_Source &project_source);
  Project &load_project(const std::string &filename, Project_Source &library);
  Project &load_project_from_file(const std::string &path, Project_Source &project_source);
  void reference_dependency(const std::string &name, Project_Source &library);
}