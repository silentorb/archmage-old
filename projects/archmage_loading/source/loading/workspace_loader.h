#pragma once

#include "Workspace.h"
#include "Project_Source.h"
#include <string>
#include <memory>

namespace projection {

  std::unique_ptr<Workspace> load_workspace_from_file(const std::string &path,
                                                      const Project_Source_Factory &project_source_factory);
}