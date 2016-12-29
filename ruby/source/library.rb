class Library
  attr_reader :units

  def initialize()
    @units = {}
    @incomplete_units = {}
  end

  def create_unit(name)
    raise "Duplicate unit: #{name}" if @units.has_key? name
    unit = Unit.new name
    @units[name] = unit
    unit
  end

  def add_unit(unit)
    if @incomplete_units.has_key? unit.name

    end

    units[unit.name] = unit
  end

  def get_unit(name)
    return @units[name] if @units.has_key? name
    return @incomplete_units[name] if @incomplete_units.has_key? name

    nil
  end
end