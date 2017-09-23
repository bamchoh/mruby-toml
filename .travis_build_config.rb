MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem '../mruby-toml'
  conf.enable_test
  
  conf.cc do |cc|
    cc.include_paths << "../libtoml"
  end
  
  conf.linker do |linker|
    linker.library_paths << "../libtoml"
  end
end
