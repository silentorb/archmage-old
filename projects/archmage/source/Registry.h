#pragma once

#include <loading/Project_Source.h>

namespace projection {

  class Library;

  class Registry : public Project_Source {
      const std::string path;
      const std::string url;
      Library &library;

      std::vector<Version> get_versions(const std::string &path);
      Version find_version_match(const Version_Range &version_range, const std::vector<Version> &versions);

  public:
      Registry(const std::string &path, Library &library);
      Project &create_project(const std::string &name, const Version &version) override;
      Project &resolve(const std::string &name, const Version_Range &version_range) override;
      static std::unique_ptr<Project_Source> factory(const std::string &path, Library &library);
  };


}