#include <boost/filesystem/operations.hpp>
#include <Repository.h>
#include "remote.h"
#include <Tag.h>

using namespace std;
using namespace boost;

namespace projection {

  void ensure_project_is_present(Project &project, Workspace & workspace) {
    auto full_path = workspace.get_project_path(project);
    if (filesystem::exists(full_path + "/.git"))
      return;

    filesystem::create_directories(full_path);
//    filesystem::create_directories(filesystem:: path(full_path).parent_path());
    repoman::Repository repo(full_path);
    repo.clone(project.get_url());
    auto tag = repo.get_tag(project.get_version().get_full_string());
    repo.checkout(tag);
  }

  void clone_missing_projects(Workspace &workspace) {
    for (auto project : workspace.get_projects()) {
      ensure_project_is_present(*project, workspace);
    }

  }
}