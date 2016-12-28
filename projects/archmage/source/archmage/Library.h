#pragma once

#include "Project.h"
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace archmage {

  class Unit_Source {
  public:
      virtual std::unique_ptr<Project> get_unit(const std::string &name) = 0;
  };

  class Library {
      std::map<std::string, std::unique_ptr<Project>> units;
      std::map<std::string, std::unique_ptr<Project>> incomplete_units;

      Project *get_unit_or_null(const std::string &name) const;
  };
}