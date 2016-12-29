require 'json'
require 'library'
require 'unit_loader'
require 'registry'
require 'remote'

class Workspace

  private

  def Workspace.load_config(workspace_path, config_path)
    json = File.read(workspace_path + '/' + config_path)
    data = JSON.parse(json)
    if data.key? 'includes'
      data['includes'].each do |include_path|
        data2 = Workspace.load_config(workspace_path, include_path)
        data.merge!(data2)
      end
    end

    data
  end

  public

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
    data = Workspace.load_config(workspace_path, 'workspace.json')

    projects_path = Workspace.make_relative workspace_path, data['projects_path']
    registry_path = Workspace.make_relative workspace_path, data['registry_path']

    library = Library.new
    registry = Registry.new registry_path, library
    load_library data['projects'], registry

    Workspace.new(projects_path, library)
  end

end