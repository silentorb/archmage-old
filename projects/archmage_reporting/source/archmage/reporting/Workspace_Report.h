#pragma once

#include <memory>
#include <vector>

namespace projection {
  class Project;
  class Workspace;
}

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
        File_State state;

    public:
        File_Status(const std::string &path, File_State state) : path(path), state(state) {}

        const std::string &get_path() const {
          return path;
        }

        File_State get_state() const {
          return state;
        }
    };

    class Project_Status {
        std::vector<File_Status> changes;
        projection::Project &project;

    public:
        Project_Status(projection::Project &project) : project(project) {}

        void add_change(const File_Status &file_status) {
          changes.push_back(file_status);
        }

        const std::vector<File_Status> &get_changed_files() const {
          return changes;
        }

        const std::string get_name() const {
          return project.get_name();
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