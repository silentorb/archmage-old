#include "process_input.h"
#include "Command.h"
#include "Input_Library.h"
#include "Input.h"
#include <iostream>

using namespace std;

namespace archmage {

  void process_input(int argument_count, char *const *arguments) {
    if (true) {
      for (int i = 0; i < argument_count; ++i) {
        cout << to_string(i) << " " << arguments[i] << endl;
      }
    }

    Input_Library library;
    Input input(argument_count, arguments, library);

    auto &command = library.get_command(input.get_command_name());
    command(input);
  }

}