require 'git'

def get_path(unit, projects_path)
  base_path = projects_path
  base_path += '/' + unit.path unless unit.path.nil? || unit.path.empty?
  return base_path + '/' + unit.name
end

def ensure_project_is_present(unit, projects_path)
  full_path = get_path(unit, projects_path)
  return if Dir.exists? full_path

  FileUtils.mkdir_p File.dirname(full_path)

  git = Git.clone(unit.url, full_path)
end


def clone_missing_projects(workspace)
  workspace.library.units.each do |name, unit|
    ensure_project_is_present unit, workspace.projects_path
  end
end

class Report
  attr_reader :modified_projects

  def initialize()
    @modified_projects = []
  end

  def add_modified_project(project)
    @modified_projects << project
  end
end

def get_project_status(unit, projects_path)
  full_path = get_path(unit, projects_path)
  git = Git.open full_path
  git.lib.diff_files
end

# def status_is_modified?(status)
#   # x = status.changed
#   # return status.untracked.length > 0 || status.changed.length > 0 || status.added.length > 0 || status.deleted.length > 0
# end

class Modified_Project
    attr_reader :unit

  def initialize(unit, status)
    @unit = unit
    @status = status
  end

  def details()
    @status
  end
end

def get_report(workspace)
  report = Report.new
  workspace.library.units.each do |name, unit|
    status = get_project_status unit, workspace.projects_path
    if status.length > 0
      report.add_modified_project Modified_Project.new(unit, status)
    end
  end
  report
end