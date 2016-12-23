def format_file_count(count)
  count == 1 ? "1 file" : "#{count} files"
end

def format_file_category(files, category_name, category_key)
  count = files.count { |key, file| file.type == category_key }
  return '' if count == 0
  # format_file_count(count) + ' ' + category_name
  "#{count} #{category_name}"
end

def format_files(files, status_types)
  mapped = status_types.map { |category| format_file_category(files, category[:name], category[:key]) }
  mapped.join '   '
end

def print_report(report)
  if report.modified_projects.length == 0
    puts "No projects are modified."
  else
    status_types = [
        {
            :name => 'modified',
            :key => 'M'
        },
        {
            :name => 'new',
            :key => 'N'
        },
        {
            :name => 'deleted',
            :key => 'D'
        },
    ]

    puts "The following projects are modified:"
    report.modified_projects.each do |entry|
      puts "  #{entry.unit.name}\t\t\t\t" + format_files(entry.files, status_types)
    end
  end
  puts
end