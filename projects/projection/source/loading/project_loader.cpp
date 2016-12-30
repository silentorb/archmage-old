#include "Project_Source.h"
#include "rapidjson/document.h"
#include "load_file.h"
#include <stdexcept>
#include <Project.h>

using namespace rapidjson;
using namespace std;

namespace projection {

  Version_Range create_version_range(const string &version_source) {
    auto version = Version(version_source);
    return Version_Range(new Single_Version_Range(version));
  }

  Project &load_project(Document &document, Project_Source &project_source) {
    auto &project = project_source.create_project(document["name"].GetString());
    project.set_url(document["url"].GetString());

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

  Project &load_project_from_string(const std::string &json, Project_Source &project_source) {
    Document document;
    document.Parse(json.c_str());
    return load_project(document, project_source);
  }

  Project &load_project_from_file(const std::string &path, Project_Source &project_source) {
    auto json = load_file(path);
    return load_project_from_string(json, project_source);
  }

}