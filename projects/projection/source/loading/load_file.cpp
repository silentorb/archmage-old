#include "load_file.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace projection {
  string load_file(const std::string &path) {
    ifstream file;

    file.open(path);
    if (!file.good())
      throw std::runtime_error(string("Could not open ") + path);

    stringstream stream;
    stream << file.rdbuf();
    return stream.str();
  }

}