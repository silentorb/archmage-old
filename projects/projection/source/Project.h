#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Version.h"

namespace projection {

  class Project_Reference;

  class Project {
      std::string name;
      std::string url;
      std::string path;
      Version version;
      std::vector<Project_Reference> dependencies;
      std::vector<Project *> dependents;

  public:
      Project(const std::string &name, const Version &version) :
        name(name), version(version) {}

      void add_dependency(Project &dependency, Version_Range &version_range) {
        dependencies.emplace_back(dependency, version_range);
        dependency.dependents.push_back(this);
      }

      const std::string &get_name() const {
        return name;
      }

      const std::vector<Project_Reference> &get_dependencies() const {
        return dependencies;
      }

      const std::vector<Project *> &get_dependents() const {
        return dependents;
      }

      const std::string &get_url() const {
        return url;
      }

      void set_url(const std::string &value) {
        url = value;
      }

      const std::string &get_path() const {
        return path;
      }

      void set_path(const std::string &value) {
        path = value;
      }

      const Version & get_version()const {
        return version;
      }
  };

  class Project_Reference {
      Project &unit;
      Version_Range version;

  public:
      Project_Reference(Project &unit, Version_Range &version) :
        unit(unit), version(version) {}
  };
}