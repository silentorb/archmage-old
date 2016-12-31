#include "Library.h"

using namespace std;

namespace projection {

  Project *Library::get_project_or_null(const std::string &name) const {
    if (projects_map.count(name))
      return projects_map.at(name).get();

    if (incomplete_projects.count(name))
      return incomplete_projects.at(name).get();

    return nullptr;
  }

  Project &Library::create_project(const std::string &name) {
    if (projects_map.count(name))
      throw runtime_error("Duplicate project: " + name + ".");

    auto project = new Project(name);
    projects_map[name] = unique_ptr<Project>(project);
    projects.push_back(project);
    return *project;
  }
}