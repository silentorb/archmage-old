#include "Workspace.h"
using namespace std;

namespace projection {

  Workspace::Workspace(const std::string &projects_path, const std::string &registry_path) : projects_path(
    projects_path), registry_path(registry_path), library(new Library()) {}

  const string Workspace::get_project_path(Project &project) {
    string base_path = projects_path;
    if (project.get_path() != "")
      base_path += "/" + project.get_path();

    return base_path + "/" + project.get_name();
  }

}