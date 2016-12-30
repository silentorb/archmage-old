#include "workspace_loader.h"
#include "rapidjson/document.h"
#include <boost/filesystem/path.hpp>
#include <Registry.h>
#include <boost/filesystem/operations.hpp>
#include "Project_Source.h"
#include "load_file.h"

using namespace rapidjson;
using namespace std;
using namespace boost;

namespace projection {

  void load_config(Document &document, const string &workspace_path, const string &config_path) {
    auto json = load_file(workspace_path + "/" + config_path);
    document.Parse(json.c_str());
    if (document.HasMember("includes")) {
      auto includes = document["includes"].GetArray();
      for (auto &include_path : includes) {
        Document second_document;
        load_config(second_document, workspace_path, include_path.GetString());
        for (auto it = second_document.MemberBegin(); it != second_document.MemberEnd(); ++it) {
          document.AddMember(it->name, it->value, document.GetAllocator());
        }
      }
    }
  }

  void load_projects(Document &document, Project_Source &project_source) {
    auto &projects = document["projects"];
    for (auto it = projects.MemberBegin(); it != projects.MemberEnd(); ++it) {
      auto name = it->name.GetString();
      auto info = it->value.GetString(); // Will be used eventually
      project_source.resolve(name);
    }
  }

  std::string make_relative(const filesystem::path &workspace_path, const filesystem::path &path) {
    string joined = (workspace_path / path).string();
    std::replace(joined.begin(), joined.end(), '\\', '/');
//    auto joined = filesystem::path(joined_path);

    string result = filesystem::canonical(joined).string();
    std::replace(result.begin(), result.end(), '\\', '/');
    return result;
  }

  std::unique_ptr<Workspace> load_workspace_from_file(const std::string &path) {
    Document document;
    auto boost_path = filesystem::path(path);
    auto workspace_path = boost_path.parent_path();
    auto filename = boost_path.filename().string();
    load_config(document, workspace_path.string(), filename);

    auto registry_path = make_relative(workspace_path, document["registry_path"].GetString());
    auto projects_path = make_relative(workspace_path, document["projects_path"].GetString());

    auto workspace = unique_ptr<Workspace>(new Workspace(
      projects_path,
      registry_path
    ));

    Registry registry(registry_path, workspace->get_library());
    load_projects(document, registry);

    return workspace;
  }
}