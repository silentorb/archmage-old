
require 'yaml'
require 'git'
require 'pp'
require 'logger'

# git = Git.open('foo', :log => Logger.new(STDOUT))

git = Git.init('foo')

pp git