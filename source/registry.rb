class Registry

  def initialize(path, library)
    @path = path
    @url = ''
    @library = library
  end

  def create_unit(name)
    @library.create_unit name
  end

  def resolve(name)
    unit = @library.get_unit name
    return unit if unit
    load_unit_from_file(@path + '/units/' + name + '.json', self)
  end
end