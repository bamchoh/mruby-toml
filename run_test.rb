#!/usr/bin/env ruby

if __FILE__ == $PROGRAM_NAME
  require 'fileutils'
  FileUtils.mkdir_p 'tmp'
  unless File.exists?('tmp/mruby')
    system 'git clone https://github.com/mruby/mruby.git tmp/mruby'
  end
  exit system(%Q[cd tmp/mruby; MRUBY_CONFIG=\"#{File.expand_path __FILE__}\" ./minirake #{ARGV.join(' ')}])
end

MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem File.dirname(File.expand_path(__FILE__))
end

MRuby::Build.new("test") do |conf|
  toolchain :gcc
  conf.enable_test
  conf.gembox 'default'
  conf.gem File.dirname(File.expand_path(__FILE__))
end

