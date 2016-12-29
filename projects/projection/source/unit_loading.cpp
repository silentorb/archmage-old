#include "unit_loading.h"
#include "rapidjson/reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace rapidjson;
using namespace std;

namespace archmage {

  struct Unit_Parser {
      Project *result;

      bool Null() {
        cout << "Null()" << endl;
        return true;
      }

      bool Bool(bool b) {
        cout << "Bool(" << boolalpha << b << ")" << endl;
        return true;
      }

      bool Int(int i) {
        cout << "Int(" << i << ")" << endl;
        return true;
      }

      bool Uint(unsigned u) {
        cout << "Uint(" << u << ")" << endl;
        return true;
      }

      bool Int64(int64_t i) {
        cout << "Int64(" << i << ")" << endl;
        return true;
      }

      bool Uint64(uint64_t u) {
        cout << "Uint64(" << u << ")" << endl;
        return true;
      }

      bool Double(double d) {
        cout << "Double(" << d << ")" << endl;
        return true;
      }

      bool RawNumber(const char *str, SizeType length, bool copy) {
        cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
      }

      bool String(const char *str, SizeType length, bool copy) {
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
      }

      bool StartObject() {
        cout << "StartObject()" << endl;
        return true;
      }

      bool Key(const char *str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
      }

      bool EndObject(SizeType memberCount) {
        cout << "EndObject(" << memberCount << ")" << endl;
        return true;
      }

      bool StartArray() {
        cout << "StartArray()" << endl;
        return true;
      }

      bool EndArray(SizeType elementCount) {
        cout << "EndArray(" << elementCount << ")" << endl;
        return true;
      }
  };

  string load_file(const std::string &path) {
    ifstream file;

    file.open(path);
    if (!file.good())
      throw std::runtime_error(string("Could not open ") + path);

    stringstream stream;
    stream << file.rdbuf();
    return stream.str();
  }

  Project &load_project_from_string(const std::string &json, Library &library) {
    Unit_Parser handler;
    Reader reader;
    StringStream ss(json.c_str());
    reader.Parse(ss, handler);
    return *handler.result;
  }

  Project &load_project(const std::string &filename, Library &library) {
    throw runtime_error("Not implemented.");
//    return <#initializer#>;
  }

  Project &load_project_from_file(const std::string &path, Library &library) {
    auto json = load_file(path);
    return load_project_from_string(json, library);
  }

  void reference_dependency(const std::string &name, Library &library) {

  }
}