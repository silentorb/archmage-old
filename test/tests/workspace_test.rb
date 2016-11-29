require 'minitest/autorun'
require 'workspace'
require 'git'
require 'remote'
require 'cli'

def create_test_repo(name)
  path = 'test/temp/repos/' + name
  Dir.mkdir path
  File.write(path + '/README.md', '# ' + name + ' documentation')
  git = Git.init(path)
  git.add
  git.commit_all 'First commit.'
end

class General_Test < Minitest::Test
  def setup
    FileUtils.rm_rf 'test/temp/projects'
    FileUtils.rm_rf 'test/temp/repos'
    Dir.mkdir 'test/temp/repos'
    create_test_repo 'audio'
    create_test_repo 'mythic'
  end

  # def teardown
  # end

  def test_general
    workspace = Workspace.load 'test/resources/workspace'
    assert_equal 2, workspace.library.units.length

    clone_missing_projects workspace
    assert Dir.exists?('test/temp/projects/audio')
    assert Dir.exists?('test/temp/projects/mythic')

    File.write('test/temp/projects/mythic/README.md', '# ' + name + ' documentation\n\nModified.')

    report = get_report(workspace)
    assert_equal 1, report.modified_projects.length
    print_report(report)

  end
end