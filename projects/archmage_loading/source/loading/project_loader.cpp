#include "Project_Source.h"
#include "load_file.h"
#include <Project.h>
#include <pathing.h>
#include <boost/filesystem/path.hpp>
#include "rapidjson/document.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

namespace projection {

  static unique_ptr<SchemaDocument> project_schema;
  static unique_ptr<SchemaValidator> project_validator;

  void initialize_validator() {
    Document schema_document;
    schema_document.Parse(

#include "schema/project.json"
    );

    project_schema = unique_ptr<SchemaDocument>(new SchemaDocument(schema_document));
    project_validator = unique_ptr<SchemaValidator>(new SchemaValidator(*project_schema));
  }

  void validate_project_json(Document &document) {
    if (!project_validator.get()) {
      initialize_validator();
    }

    if (!document.Accept(*project_validator)) {
      StringBuffer sb;
      project_validator->GetInvalidSchemaPointer().StringifyUriFragment(sb);
      printf("Invalid schema: %s\n", sb.GetString());
      printf("Invalid keyword: %s\n", project_validator->GetInvalidSchemaKeyword());
      sb.Clear();
      project_validator->GetInvalidDocumentPointer().StringifyUriFragment(sb);
      printf("Invalid document: %s\n", sb.GetString());
    }
  }

  void set_project_url(Project &project, const string &url, const string &base_path) {
    if (url.substr(0, 4) != "git@" && url.substr(0, 4) != "http")
      project.set_url(pathing::relative(base_path, url));
    else
      project.set_url(url);
  }

  Project &load_project(Document &document, Project_Source &project_source, const string &base_path) {
    validate_project_json(document);

    auto &project = project_source.create_project(
      document["name"].GetString(),
      Version(document["version"].GetString()));

    set_project_url(project, document["url"].GetString(), base_path);

    if (document.HasMember("dependencies")) {
      auto &dependencies = document["dependencies"];
      for (auto it = dependencies.MemberBegin(); it != dependencies.MemberEnd(); ++it) {
        auto name = it->name.GetString();
        auto info = it->value.GetString();
        auto version_range = Version_Range(info);
        auto &dependency = project_source.resolve(name, version_range);
        project.add_dependency(dependency, version_range);
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
    return load_project_from_string(json, project_source, base_path);
  }

}