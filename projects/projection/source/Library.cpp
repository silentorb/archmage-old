#include "Library.h"

using namespace std;

namespace projection {

  Project *Library::get_project_or_null(const std::string &name) const {
    if (projects.count(name))
      return projects.at(name).get();

    if (incomplete_projects.count(name))
      return incomplete_projects.at(name).get();

    return nullptr;
  }

  Project &Library::create_project(const std::string &name) {
    if (projects.count(name))
      throw runtime_error("Duplicate project: " + name + ".");

    auto project = new Project(name);
    projects[name] = unique_ptr<Project>(project);
    return *project;
  }
}