def format_file_count(files)
  files.length == 1 ? "1 file" : "#{files.length} files"
end

def print_report(report)
  if report.modified_projects.length == 0
    puts "No projects are modified."
  else
    puts "The following projects are modified:"
    report.modified_projects.each do |entry|
      puts "  #{entry.unit.name}\t\t\t\t" + format_file_count(entry.details)
    end
  end
  puts
end