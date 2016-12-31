#pragma once

#include "Project.h"
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace projection {

//  class Unit_Source {
//  public:
//      virtual std::unique_ptr<Project> get_project(const std::string &name) = 0;
//  };

  class Library {
      std::vector<Project *> projects;
      std::map<std::string, std::unique_ptr<Project>> projects_map;
      std::map<std::string, std::unique_ptr<Project>> incomplete_projects;

  public:
      Project *get_project_or_null(const std::string &name) const;
      Project &create_project(const std::string &name, const Version &version);

      const std::vector<Project *> &get_projects() const {
        return projects;
      }
  };
}