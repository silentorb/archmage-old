#include "reporting.h"
#include <iostream>
#include <algorithm>
#include <Project.h>
#include <Workspace.h>
#include <archmage/reporting/Workspace_Report.h>

using namespace std;

namespace archmage {

  using namespace reporting;

  const string join(initializer_list<string> strings, const string &delimiter) {
    string result;
    for (auto &item : strings) {
      if (item.size() == 0)
        continue;

      if (result.size() > 0)
        result += delimiter + item;
      else
        result = item;
    }

    return result;
  }

  const string format_status_category(const std::vector<File_Status> &files, File_State state, const string &label) {
    auto count = count_if(files.begin(), files.end(), [state](const File_Status &file) {
      return file.get_state() == state;
    });

    if (count == 0)
      return "";

    return to_string(count) + " " + label;
  }

  const string format_file_summary(const std::vector<File_Status> &files) {
    return join(
      {
        format_status_category(files, File_State::_new, "new"),
        format_status_category(files, File_State::modified, "modified"),
        format_status_category(files, File_State::deleted, "deleted"),
        format_status_category(files, File_State::renamed, "renamed"),
      }, "  ");
  }

  void print_report(const Workspace_Report &report) {
    if (report.get_changed_projects().size() == 0) {
      cout << "No projects have been modified." << endl;
    }
    else {
      cout << "The following projects are modified:" << endl;
      for (auto &project: report.get_changed_projects()) {
        cout << "  " + project->get_name() + "\t\t\t\t" + format_file_summary(project->get_changed_files()) << endl;
      }
    }
  }
}