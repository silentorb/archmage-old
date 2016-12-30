#pragma once

#include <string>
#include "Library.h"
#include "Project_Source.h"

namespace projection {

  Project &load_project_from_file(const std::string &path, Project_Source &project_source,
                                  const std::string &base_path);
}