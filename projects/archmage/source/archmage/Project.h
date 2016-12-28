#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Version.h"

namespace archmage {

  class Project_Reference;

  class Project {
      std::string name;
      std::string url;
      std::string path;
      std::vector<Project_Reference> dependencies;
      std::vector<Project *> dependents;

  public:
      Project(const std::string &name) : name(name) {}

      void add_dependency(Project &dependency, std::shared_ptr<Version_Range> &version_range) {
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
  };

  class Project_Reference {
      Project &unit;
      std::shared_ptr<Version_Range> version;

  public:
      Project_Reference(Project &unit, std::shared_ptr<Version_Range> &version) :
        unit(unit), version(version) {}
  };
}