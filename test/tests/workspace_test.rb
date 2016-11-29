require 'minitest/autorun'
require 'workspace'
require 'git'

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

  def test_fail
    workspace = Workspace.load 'test/resources/workspace'
    assert_equal 2, workspace.library.units.length

    workspace.clone_missing_projects
    assert Dir.exists?('test/temp/projects/audio')
    assert Dir.exists?('test/temp/projects/mythic')
  end
end