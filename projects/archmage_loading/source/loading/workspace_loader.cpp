#include "workspace_loader.h"
#include "rapidjson/document.h"
#include "rapidjson/schema.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <pathing.h>
#include <rapidjson/stringbuffer.h>
#include "load_file.h"

using namespace rapidjson;
using namespace std;
using namespace boost;

namespace projection {

  static unique_ptr <SchemaDocument> workspace_schema;
  static unique_ptr <SchemaValidator> workspace_validator;

  static void initialize_validator() {
    Document schema_document;
    schema_document.Parse(

#include "schema/workspace.json"
    );

    workspace_schema = unique_ptr<SchemaDocument>(new SchemaDocument(schema_document));
    workspace_validator = unique_ptr<SchemaValidator>(new SchemaValidator(*workspace_schema));
  }

  void validate_workspace_json(Document &document) {
    if (!workspace_validator.get()) {
      initialize_validator();
    }

    if (!document.Accept(*workspace_validator)) {
      StringBuffer sb;
      workspace_validator->GetInvalidSchemaPointer().StringifyUriFragment(sb);
      printf("Invalid schema: %s\n", sb.GetString());
      printf("Invalid keyword: %s\n", workspace_validator->GetInvalidSchemaKeyword());
      sb.Clear();
      workspace_validator->GetInvalidDocumentPointer().StringifyUriFragment(sb);
      printf("Invalid document: %s\n", sb.GetString());
      throw "";
    }
  }

  void load_config(Document &document, const string &workspace_path, const string &config_path) {
    auto json = load_file(pathing::join(workspace_path, config_path));
    document.Parse(json.c_str());
    if (document.HasMember("includes")) {
      auto includes = document["includes"].GetArray();
      for (auto &include_path : includes) {
        Document second_document;
        load_config(second_document, workspace_path, include_path.GetString());

        for (auto it = second_document.MemberBegin(); it != second_document.MemberEnd(); ++it) {
          string name = it->name.GetString();
          if (name == "projects") {
            auto &projects = it->value;
            auto &destination = document["projects"];
            for (auto it2 = projects.MemberBegin(); it2 != projects.MemberEnd(); ++it2) {
              if (!document.HasMember(it2->name))
                destination.AddMember(it2->name, it2->value, document.GetAllocator());
            }
          }
          else if (name == "children") {
            auto &projects = it->value;
            auto &destination = document["children"];
            for (auto it2 = projects.MemberBegin(); it2 != projects.MemberEnd(); ++it2) {
              if (!document.HasMember(it2->name))
                destination.AddMember(it2->name, it2->value, document.GetAllocator());
            }
          }
          else if (name != "includes" && !document.HasMember(it->name)) {
            document.AddMember(it->name, it->value, document.GetAllocator());
          }
        }
      }
    }
  }

  void load_projects(Document &document, Project_Source &project_source) {
    auto &projects = document["projects"];
    for (auto it = projects.MemberBegin(); it != projects.MemberEnd(); ++it) {
      auto name = it->name.GetString();
      auto info = it->value.GetString(); // Will be used eventually
      auto version_range = Version_Range(info);
      project_source.resolve(name, version_range);
    }
  }

  std::unique_ptr <Workspace> load_workspace_from_file(const std::string &path,
                                                       const Project_Source_Factory &project_source_factory) {
    Document document;
    auto boost_path = filesystem::path(path);
    auto workspace_path = boost_path.parent_path().string();
    auto filename = boost_path.filename().string();
    load_config(document, workspace_path, filename);
    validate_workspace_json(document);

    auto registry_path = pathing::relative(workspace_path, document["registry_path"].GetString());
    auto projects_path = pathing::relative(workspace_path, document["projects_path"].GetString());

    auto workspace = unique_ptr<Workspace>(new Workspace(
      projects_path,
      registry_path
    ));

    auto project_source = project_source_factory(registry_path, workspace->get_library());
    load_projects(document, *project_source);

    return workspace;
  }

}