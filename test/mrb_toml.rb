##
## Toml Test
##

assert("Toml#parse(root of hash") do
  exp = {"bar" => 1}
  assert_equal(exp, Toml.parse("bar = 1"))
end

assert("Toml#parse(table)") do
  exp = {"foo" => {"bar" => 1}}
  assert_equal(exp, Toml.parse("[foo]\nbar = 1\n"))
end

assert("Toml#parse(array)") do
  exp = {"bar" => [1,2,3]}
  assert_equal(exp, Toml.parse("bar = [1,2,3]"))
end

assert("Toml#parse(array of tables)") do
  exp = {"foo" => [{"bar" => 1, "fiz" => 2}, {"abc" => 3, "def" => 4}]}
  assert_equal(exp, Toml.parse("[[foo]]\nbar = 1\nfiz = 2\n\n[[foo]]\nabc = 3\ndef = 4\n"))
end

