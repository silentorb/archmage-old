#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost;
using namespace std;

int main(int argc, char *const argv[]) {
  std::cout << "Wow!!!!!";
  try {
    filesystem::copy_directory("nowhere", "nowhere2");
//    filesystem::remove_all("temp");
  }
  catch(const boost::filesystem::filesystem_error &ex) {
    std::cout << "Wow!!!!!";
    int k = 0;
  }
  catch(...) {
    std::cout << "Wow!!!!!2";
    int k = 0;
  }

  return 0;
}
