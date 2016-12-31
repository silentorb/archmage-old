#include <Workspace.h>
#include <Repository.h>
#include "Workspace_Report.h"

using namespace std;
using namespace projection;

namespace archmage {
  namespace reporting {

    enum Git_Status {
        CURRENT = 0,

        INDEX_NEW = (1u << 0),
        INDEX_MODIFIED = (1u << 1),
        INDEX_DELETED = (1u << 2),
        INDEX_RENAMED = (1u << 3),
        INDEX_TYPECHANGE = (1u << 4),

        WT_NEW = (1u << 7),
        WT_MODIFIED = (1u << 8),
        WT_DELETED = (1u << 9),
        WT_TYPECHANGE = (1u << 10),
        WT_RENAMED = (1u << 11),
        WT_UNREADABLE = (1u << 12),

        IGNORED = (1u << 14),
        CONFLICTED = (1u << 15),
    };

    Workspace_Report::Workspace_Report(projection::Workspace &workspace) :
      workspace(workspace) {
      analyze();
    }

    File_State translate_state(unsigned int flags) {
      if (flags & (Git_Status::INDEX_NEW | Git_Status::WT_NEW))
        return File_State::_new;

      if (flags & (Git_Status::INDEX_DELETED | Git_Status::WT_DELETED))
        return File_State::deleted;

      if (flags & (Git_Status::INDEX_RENAMED | Git_Status::WT_RENAMED))
        return File_State::renamed;

      if (flags & (Git_Status::INDEX_MODIFIED | Git_Status::WT_MODIFIED))
        return File_State::modified;

      return File_State::none;
    }

    unique_ptr<Project_Status> Workspace_Report::get_project_status(Project &project) {
      auto full_path = workspace.get_project_path(project);
      repoman::Repository repo(full_path);
      repo.open();
      auto status = unique_ptr<Project_Status>(new Project_Status());

      repo.enumerate_status([& status](const std::string &path, unsigned int flags) {
        auto file_state = translate_state(flags);
        if (file_state != File_State::none)
          status->add_change({path, file_state});
      });

      return status;
    }

    void Workspace_Report::analyze() {
      for (auto project : workspace.get_projects()) {
        auto status = get_project_status(*project);
        if (status->get_changed_files().size() > 0) {
          changed_projects.push_back(std::move(status));
        }
      }
    }
  }
}