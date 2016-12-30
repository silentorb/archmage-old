#include <boost/filesystem/operations.hpp>
#include <Repository.h>
#include "remote.h"
#include "Library.h"

using namespace std;
using namespace boost;

namespace projection {

  const string get_path(Project &project, const string &projects_path) {
    string base_path = projects_path;
    if (project.get_path() != "")
      base_path += "/" + project.get_path();

    return base_path + "/" + project.get_name();
  }

  void ensure_project_is_present(Project &project, const string &projects_path) {
    auto full_path = get_path(project, projects_path);
    if (filesystem::exists(full_path))
      return;

    filesystem::create_directories(full_path);
//    filesystem::create_directories(filesystem:: path(full_path).parent_path());
    repoman::Repository repo(full_path);
    repo.clone(project.get_url());
  }

  void clone_missing_projects(Workspace &workspace) {
    for (auto &entry : workspace.get_library().get_projects()) {
      ensure_project_is_present(*entry.second, workspace.get_projects_path());
    }

  }
}