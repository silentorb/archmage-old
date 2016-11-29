require 'git'

def ensure_project_is_present(unit, projects_path)
  base_path = projects_path
  base_path += '/' + unit.path unless unit.path.nil? || unit.path.empty?
  full_path = base_path + '/' + unit.name
  return if Dir.exists? full_path

  FileUtils.mkdir_p base_path

  git = Git.clone(unit.url, full_path)
end