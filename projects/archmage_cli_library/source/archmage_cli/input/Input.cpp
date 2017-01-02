#include "Input.h"

using namespace std;

namespace archmage {

  Input::Input(int argument_count, char *const *arguments, const Input_Library &library) {
    for (int i = 0; i < argument_count; ++i) {
      auto argument = string(arguments[i]);
      if (argument[0] == '-') {
        auto flag_definition = library.find_flag(argument);
        string value;
//        if (flag_definition.has_value()) {
//          if (i == argument_count - 1)
//            throw runtime_error("Flag " + argument + " requires an argument");
//
//        }
        Flag flag(flag_definition, value);
      }
      else {
        tokens.push_back(argument);
      }
    }

    if (tokens.size() == 0) {
      command_name = "help";
    }
    else {
      command_name = tokens[0];
      tokens.erase(tokens.begin());
    }
  }
}