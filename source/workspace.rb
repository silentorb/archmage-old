require 'json'
require 'library'
require 'unit_loader'
require 'registry'
require 'remote'

class Workspace
  attr_reader :projects_path
  attr_reader :library

  def initialize(projects_path, library)
    @projects_path = projects_path
    @library = library
  end

  def Workspace.make_relative(workspace_path, path)
    File.expand_path File.join(workspace_path, path)
  end

  def Workspace.load(workspace_path)
    json = File.read(workspace_path + '/workspace.json')
    data = JSON.parse(json)

    projects_path = Workspace.make_relative workspace_path, data['projects_path']
    registry_path = Workspace.make_relative workspace_path, data['registry_path']

    library = Library.new
    registry = Registry.new registry_path, library
    load_library data['projects'], registry

    Workspace.new(projects_path, library)
  end

  def clone_missing_projects()
    @library.units.each do |name, unit|
      ensure_project_is_present unit, @projects_path
    end
  end
end