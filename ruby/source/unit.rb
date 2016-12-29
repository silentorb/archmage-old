require 'version'

class Unit
  attr_reader :name
  attr_reader :dependencies
  attr_reader :dependents
  attr_reader :path
  attr_accessor :url

  def initialize(name)
    @name = name
    @dependencies = []
    @dependents = []
    @path = ''
    @url = ''
  end

  def add_dependency(unit, version)
    @dependencies << Unit_Reference.new(unit, version)
    unit.add_dependent(self)
  end

  def add_dependent(unit)
    @dependents << unit
  end

end

class Unit_Reference

  def initialize(unit, version)
    @unit = unit
    @version = version
  end
end