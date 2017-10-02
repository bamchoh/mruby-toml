##
## Toml Test
##

assert("Toml#parse(root of hash") do
  toml = "bar = 1"
  exp = {"bar" => 1}
  assert_equal(exp, Toml.parse(toml))
end

assert("Toml#parse(table)") do
  toml = "[foo]\nbar = 1\n"
  exp = {"foo" => {"bar" => 1}}
  assert_equal(exp, Toml.parse(toml))
end

assert("Toml#parse(array)") do
  toml = "bar = [1,2,3]"
  exp = {"bar" => [1,2,3]}
  assert_equal(exp, Toml.parse(toml))
end

assert("Toml#parse(array of tables)") do
  toml = "[[foo]]\nbar = 1\nfiz = 2\n\n[[foo]]\nabc = 3\ndef = 4\n"
  exp = {"foo" => [{"bar" => 1, "fiz" => 2}, {"abc" => 3, "def" => 4}]}
  assert_equal(exp, Toml.parse(toml))
end

