#include <loading/project_loader.h>
#include "Registry.h"
#include "Library.h"

namespace projection {

  Registry::Registry(const std::string &path, Library &library) :
    path(path), library(library) {}

  Project &Registry::create_project(const std::string &name) {
    return library.create_project(name);
  }

  Project &Registry::resolve(const std::string &name) {
    auto project = library.get_project_or_null(name);
    if (project)
      return *project;

    return load_project_from_file(path + "/projects/" + name + ".json", *this);
  }

}