#pragma once

#include "Workspace.h"
#include <string>
#include <memory>

namespace projection {

  std::unique_ptr<Workspace> load_workspace_from_file(const std::string &path);
}