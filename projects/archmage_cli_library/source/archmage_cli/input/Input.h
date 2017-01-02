#pragma once

#include <vector>
#include <string>
#include "Flag.h"
#include "Input_Library.h"

namespace archmage {

  class Input {
      std::vector<Flag> flags;
      std::vector<std::string> tokens;
      std::string command_name;

  public:
      Input(int argument_count, char *const *arguments, const Input_Library & library);

      const std::vector<Flag> &get_flags() const {
        return flags;
      }

      const std::vector<std::string> &get_tokens() const {
        return tokens;
      }

      const std::string &get_command_name() const {
        return command_name;
      }
  };
}