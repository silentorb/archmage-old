require 'optparse'

options = {}
OptionParser.new do |args|
  args.banner = "Usage: example.rb [options]"

  args.on("-v", "--[no-]verbose", "Run verbosely") do |v|
    options[:verbose] = v
  end
end.parse!