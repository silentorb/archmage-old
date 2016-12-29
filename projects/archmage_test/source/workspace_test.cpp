#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <Repository.h>

using namespace boost;
using namespace std;

void create_file(const string &name, const string &contents) {
  ofstream file(name);
  file << contents;
}

void create_test_repo(const string &name) {
  auto path = "temp/repos/" + name;
  filesystem::create_directories(path);
  create_file(path + "/README.md", "# " + name + " documentation");
  create_file(path + "/LICENSE.txt", "This can only be used for awesomeness!");
  auto git = repoman::Repository(path);
}

void setup() {
  filesystem::remove_all("temp");
  filesystem::create_directories("temp/repos");
  create_test_repo("audio");
  create_test_repo("mythic");
}

TEST(Workspace, general) {
  setup();

//  ASSERT_TRUE(false);
//  EXPECT_EQ(60, 1);
}
