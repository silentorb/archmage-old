#include "Project_Source.h"
#include "rapidjson/document.h"
#include "load_file.h"
#include <stdexcept>
#include <Project.h>
#include <pathing.h>
#include <boost/filesystem/path.hpp>

using namespace rapidjson;
using namespace std;

namespace projection {

  Version_Range create_version_range(const string &version_source) {
    auto version = Version(version_source);
    return Version_Range(new Single_Version_Range(version));
  }

  void set_project_url(Project &project, const string &url, const string &base_path) {
    if (url.substr(0, 4) != "git@" && url.substr(0, 4) != "http")
      project.set_url(pathing::relative(base_path, url));
    else
      project.set_url(url);
  }

  Project &load_project(Document &document, Project_Source &project_source, const string &base_path) {
    auto &project = project_source.create_project(document["name"].GetString());
    set_project_url(project, document["url"].GetString(), base_path);

    if (document.HasMember("dependencies")) {
      auto &dependencies = document["dependencies"];
      for (auto it = dependencies.MemberBegin(); it != dependencies.MemberEnd(); ++it) {
        auto name = it->name.GetString();
        auto info = it->value.GetString();
        auto version_range = create_version_range(info);
        project.add_dependency(project_source.resolve(name), version_range);
      }
    }

    return project;
  }

  Project &load_project_from_string(const std::string &json, Project_Source &project_source, const string &base_path) {
    Document document;
    document.Parse(json.c_str());
    return load_project(document, project_source, base_path);
  }

  Project &load_project_from_file(const std::string &path, Project_Source &project_source, const string &base_path) {
    auto json = load_file(path);
    return load_project_from_string(json, project_source,base_path);
  }

}