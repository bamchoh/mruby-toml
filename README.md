# mruby-toml   [![Build Status](https://travis-ci.org/bamchoh/mruby-toml.svg?branch=master)](https://travis-ci.org/bamchoh/mruby-toml)
Toml class
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
p Toml.hi
#=> "hi!!"
t = Toml.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
