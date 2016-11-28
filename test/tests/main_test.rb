require 'test/unit'
class General_Test < Test::Unit::TestCase
  # def setup
  # end

  # def teardown
  # end

  def test_fail
    puts "h"
    assert(false, 'Assertion was false.')
  end
end