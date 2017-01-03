#pragma once

#include <string>
#include <vector>
#include "Library.h"

namespace projection {

  class Workspace {
      std::string projects_path;
      std::string registry_path;
      std::unique_ptr<Library> library;
      std::vector<std::unique_ptr<Workspace>> children;

  public:
      Workspace(const std::string &projects_path, const std::string &registry_path);

      const std::string &get_projects_path() const {
        return projects_path;
      }

      void set_projects_path(const std::string &value) {
        projects_path = value;
      }

      const std::string &get_registry_path() const {
        return registry_path;
      }

      void set_registry_path(const std::string &value) {
        registry_path = value;
      }

      Library &get_library() const {
        return *library;
      }

      const std::vector<Project *> &get_projects() const {
        return library->get_projects();
      }

      const std::string get_project_path(Project &project);
  };
}