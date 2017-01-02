#include <boost/filesystem.hpp>
#include <iostream>
#include <archmage_cli/input/process_input.h>

using namespace boost;
using namespace std;

int main(int argument_count, char *const arguments[]) {
  archmage::process_input(argument_count, arguments);

  return 0;
}
