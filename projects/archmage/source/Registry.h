#pragma once

#include <loading/Project_Source.h>

namespace projection {

  class Library;

  class Registry : public Project_Source {
      const std:: string path;
      const std:: string url;
      Library & library;

  public:
      Registry(const std::string &path, Library &library);
      Project &create_project(const std::string &name) override;
      Project &resolve(const std::string &name) override;
  };
}