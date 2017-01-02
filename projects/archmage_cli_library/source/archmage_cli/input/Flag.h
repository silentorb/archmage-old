#pragma once

#include <string>

namespace archmage {

  class Flag_Definition {
      std::string name;
      char shortcut;
      bool _has_value = false;

  public:
      bool has_value()const {
        return _has_value;
      }

      const std::string &get_name() const {
        return name;
      }

      char get_shortcut() const {
        return shortcut;
      }
  };

  class Flag {
      Flag_Definition &definition;
      std::string value;

  public:
      Flag(Flag_Definition &definition, const std::string &value = "") :
        definition(definition), value(value) {}
  };
}