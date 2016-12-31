#pragma once

#include <memory>
#include <vector>

namespace archmage {
  namespace reporting {

    enum class File_State {
        none,
        _new,
        modified,
        deleted,
        renamed,
    };

    class File_Status {
        const std::string &path;
        File_State mode;

    public:
        File_Status(const std::string &path, File_State mode) : path(path), mode(mode) {}
    };

    class Project_Status {
        std::vector<File_Status> changes;

    public:
        void add_change(const File_Status &file_status) {
          changes.push_back(file_status);
        }

        const std::vector<File_Status> &get_changed_files() const {
          return changes;
        }
    };

    class Workspace_Report {
        projection::Workspace &workspace;
        std::vector<std::unique_ptr<Project_Status>> changed_projects;

        void analyze();
        std::unique_ptr<Project_Status> get_project_status(projection::Project &project);

    public:
        Workspace_Report(projection::Workspace &workspace);

        const std::vector<std::unique_ptr<Project_Status>> &get_changed_projects() const {
          return changed_projects;
        }
    };
  }
}