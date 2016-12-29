#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <Repository.h>
#include <iostream>

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
  repoman::Repository repo(path);
  repo.add_all();
  repo.commit("First commit.");
}

void each_file(const filesystem::path &dir_path,
               const std::function<void(const filesystem::path &file)> &action) {
  if (!filesystem::exists(dir_path))
    return;

  filesystem::directory_iterator end_itr; // default construction yields past-the-end
  for (filesystem::directory_iterator itr(dir_path);
       itr != end_itr;
       ++itr) {
    if (filesystem::is_directory(itr->status())) {
      each_file(itr->path(), action);
    }
    else {
      action(itr->path());
    }
  }
}

void setup() {
  try {
    each_file("temp", [](const filesystem::path &file) {
      filesystem::permissions(file, filesystem::add_perms | filesystem::owner_write | filesystem::group_write |
                                    filesystem::others_write);
    });
    filesystem::remove_all("temp");
  }
  catch (const boost::filesystem::filesystem_error &ex) {
    std::cerr << endl << ex.what() << endl;
  }

  filesystem::create_directories("temp/repos");
  create_test_repo("audio");
  create_test_repo("mythic");
}

TEST(Workspace, general) {
  setup();

//  ASSERT_TRUE(false);
//  EXPECT_EQ(60, 1);
}
