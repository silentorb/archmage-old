#pragma once

#include <string>
#include <stdexcept>
#include <Version.h>

namespace projection {

  class Project;

  class Project_Source {
  public:
      virtual Project &create_project(const std::string &name, const Version & version) = 0;
      virtual Project &resolve(const std::string &name, const Version_Range &version_range) = 0;
  };

  class Version_Not_Found : public std::runtime_error {
      Version_Range version_range;

  public:
      Version_Not_Found(Version_Range &version_range, const std::string &message) :
        runtime_error(message), version_range(version_range) {}

      Version_Not_Found(const Version_Range &version_range) :
        runtime_error("Version not found: " + version_range.get_string()), version_range(version_range) {}
  };

  class Version_Conflict : public std::runtime_error {
      Version_Range version_range;
      Project &project;

  public:
      Version_Conflict(const Version_Range &version_range, Project &project)
        : runtime_error(""), version_range(version_range), project(project) {}
  };
}