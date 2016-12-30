#include "Workspace.h"

namespace projection {

  Workspace::Workspace(const std::string &projects_path, const std::string &registry_path) : projects_path(
    projects_path), registry_path(registry_path), library(new Library()) {}
}