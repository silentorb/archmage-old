require 'json'
require 'unit'

def create_version_range(pattern)
  version = Version.from_string pattern
  Single_Version_Range.new version
end

# unit = Unit.from_hash(source)
# library.add_unit(unit)
# library.process_dependencies(unit, source['dependencies'])

def load_unit(source, unit_source)
  unit = unit_source.create_unit source['name']
  unit.url = source['url']
  if source.has_key? 'dependencies'
    source['dependencies'].each do |name, version_source|
      version = create_version_range version_source
      unit.add_dependency unit_source.resolve(name), version
    end
  end
  unit
end

def load_string(json, unit_source)
  source = JSON.parse json
  load_unit source, unit_source
end

def load_unit_from_file(path, unit_source)
  json = File.read path
  load_string json, unit_source
end

def load_library(projects, unit_source)
  projects.each do |name, version_source|
    unit_source.resolve name
  end
end