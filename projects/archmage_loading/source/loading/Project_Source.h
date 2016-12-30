#pragma once

#include <string>

namespace projection {

  class Project;

  class Project_Source {
  public:
      virtual Project &create_project(const std::string &name) = 0;
      virtual Project &resolve(const std::string &name) = 0;
  };
}