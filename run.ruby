require 'sinatra'

set :port, 3000

get '/' do
  call_python_script
  "Ruby (Sinatra) server is running!\n"
end

def call_python_script
  output = `python test.py 2>&1`
  puts "Python script output: #{output}"
  puts "Python script exited with code #{$?.exitstatus}"
end
