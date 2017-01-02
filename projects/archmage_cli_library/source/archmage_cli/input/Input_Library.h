#pragma once

#include <vector>
#include <string>
#include "Flag.h"
#include "Command.h"

namespace archmage {

  class Input_Library {
      std::vector<Command> commands;
      std::vector<Flag_Definition> flags;

      void initialize_commands();
      void initialize_flags();

  public:
      Input_Library();

//      const std::vector<Flag_Definition> &get_flags() const {
//        return flags;
//      }

      const std::vector<Command> &get_commands() const {
        return commands;
      }

      const Flag_Definition &find_flag(const std::string &text) const;
      const Command &get_command(const std::string &name) const;
  };

  class Invalid_Flag_Format : std::runtime_error {
  public:
      Invalid_Flag_Format(const std::string &flag) : runtime_error("Invalid flag format: " + flag) {}

  };

  class Invalid_Flag : std::runtime_error {
  public:
      Invalid_Flag(const std::string &flag) : runtime_error("Invalid flag: " + flag) {}

  };
}