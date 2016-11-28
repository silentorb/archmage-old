class Version
  def initialize(major, minor)
    @major = major
    @minor = minor
  end

  def Version.from_string(string)
    match = string.match /(\d+)\.(\d+)/
    raise "Invalid version: #{string}" if !match
    major = match[1].to_i
    minor = match[2].to_i
    Version.new(major, minor)
  end

  def matches(version)
    @major == version.major && @minor == version.minor
  end
end

class Unit
  def initialize(name)
    @name = name
  end
end

class Single_Version_Range
  def initialize(version)
    @version = version
  end

  def matches(version)
    @version.matches version
  end
end