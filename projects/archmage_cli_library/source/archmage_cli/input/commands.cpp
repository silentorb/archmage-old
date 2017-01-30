#include <Workspace.h>
#include <loading/workspace_loader.h>
#include <Registry.h>
#include <archmage/reporting/Workspace_Report.h>
#include <archmage_cli/output/reporting.h>
#include "commands.h"
#include <iostream>

using namespace std;

namespace archmage {
  namespace commands {

    unique_ptr<projection::Workspace> load_workspace() {
      return projection::load_workspace_from_file("workspace.json", projection::Registry::factory);
    }

    void help(const Input &input) {

    }

    void push(const Input &input) {
      auto workspace = load_workspace();
      auto report = reporting::Workspace_Report(*workspace);

    }

    void status(const Input &input) {
      auto workspace = load_workspace();
      auto report = reporting::Workspace_Report(*workspace);
      cout << endl;
      print_report(report);
      cout << endl;
    }
  }
}
