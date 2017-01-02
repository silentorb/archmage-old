#include <loading/project_loader.h>
#include <boost/filesystem/operations.hpp>
#include "Registry.h"
#include "Library.h"

using namespace std;
using namespace boost;

namespace projection {

  Registry::Registry(const std::string &path, Library &library) :
    path(path), library(library) {}

  Project &Registry::create_project(const std::string &name, const Version &version) {
    return library.create_project(name, version);
  }

  std::vector<Version> Registry::get_versions(const std::string &path) {
    vector<Version> result;
    for (auto &file : filesystem::directory_iterator(path)) {
      result.push_back(file.path().stem().string());
    }
    return result;
  }

  Version Registry::find_version_match(const Version_Range &version_range, const std::vector<Version> &versions) {
    for (auto &version: versions) {
      if (version_range.matches(version)) {
        return version;
      }
    }

    throw Version_Not_Found(version_range);
  }

  Project &Registry::resolve(const std::string &name, const Version_Range &version_range) {
    auto project = library.get_project_or_null(name);
    if (project) {
      if (!version_range.matches(project->get_version()))
        throw Version_Conflict(version_range, *project);

      return *project;
    }

    auto project_path = path + "/projects/" + name;
    auto versions = get_versions(project_path);
    auto version = find_version_match(version_range, versions);
    return load_project_from_file(project_path + "/" + version.get_full_string() + ".json", *this, path);
  }

  std::unique_ptr<Project_Source> Registry::factory(const std::string &path, Library &library) {
    return unique_ptr<Project_Source>(new Registry(path, library));
  }
}