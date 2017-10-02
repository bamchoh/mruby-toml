# mruby-toml   [![Build Status](https://travis-ci.org/bamchoh/mruby-toml.svg?branch=master)](https://travis-ci.org/bamchoh/mruby-toml)

[WIP]

Toml parser for mruby. this library is using [libtoml](https://github.com/ajwans/libtoml)

## limitation

This library doesn't parse TOML_DATE type. it returns nil.

## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'bamchoh/mruby-toml'
end
```
## example
```ruby
p Toml.parser("bar = 1")
#=> {bar => 1}
```

## License
under the MIT License:
- see LICENSE file
