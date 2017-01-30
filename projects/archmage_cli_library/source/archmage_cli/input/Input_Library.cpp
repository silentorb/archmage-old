#include "Input_Library.h"
#include "commands.h"

namespace archmage {

  Input_Library::Input_Library() {
    initialize_flags();
    initialize_commands();
  }

  void Input_Library::initialize_commands() {
    commands = {
      {"help", commands::help},
      {"push", commands::push},
      {"status", commands::status},
    };
  }

  void Input_Library::initialize_flags() {

  }

  int get_hyphen_count(const std::string &text) {
    int result = 0;
    for (int i = 0; i < text.size(); ++i) {
      if (text[i] != '-')
        break;

      ++result;
    }
    return result;
  }

  const Flag_Definition &Input_Library::find_flag(const std::string &text) const {
    if (text.size() == 1)
      throw Invalid_Flag_Format(text);

    auto hyphen_count = get_hyphen_count(text);

    if (hyphen_count == text.size())
      throw Invalid_Flag_Format(text);

    if (hyphen_count == 1) {
      if (text.size() > 2)
        throw Invalid_Flag_Format(text);

      auto key = text[1];
      for (auto &definition: flags) {
        if (definition.get_shortcut() == key)
          return definition;
      }

      throw Invalid_Flag(text);
    }
    else if (hyphen_count == 2) {
      auto name = text.substr(2);
      for (auto &definition: flags) {
        if (definition.get_name() == name)
          return definition;
      }

      throw Invalid_Flag(text);
    }
    else {
      throw Invalid_Flag_Format(text);
    }

  }

  const Command &Input_Library::get_command(const std::string &name) const {
    for (auto &command: commands) {
      if (command.get_name() == name)
        return command;
    }

    throw std::runtime_error("Invalid command: " + name + ".");
  }

}