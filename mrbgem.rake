MRuby::Gem::Specification.new('mruby-toml') do |spec|
  spec.license = 'MIT'
  spec.authors = 'bamchoh'

  spec.linker.libraries << %w(toml)
end
