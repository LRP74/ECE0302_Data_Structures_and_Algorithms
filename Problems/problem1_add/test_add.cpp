#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "add.hpp"
#include "math.h"

TEST_CASE("Test add", "[Add]")
{
  Add<int> a;
  REQUIRE(a.call(1, 2) == 3);
}

TEST_CASE("Test add with long", "[Add]")
{
  Add<long> longAdder;
  long result = longAdder.call(32256, 65535);
  REQUIRE(result == 97791);
}

TEST_CASE("Test add with doubles", "[Add]")
{
  Add<double> doubleAdder;
  double expected = 7.0;
  double threshold = 1e-9;
  double sum = doubleAdder.call(3.0 - sqrt(2.0), 4.0 + sqrt(2.0));

  REQUIRE(std::abs(sum - expected) < threshold);
}

TEST_CASE("Test add with chars", "[Add]")
{
  Add<char> charAdder;
  char result = charAdder.call('2', '3');
  REQUIRE(result == 'e');
}

TEST_CASE("Test add with std::string", "[Add]")
{
  Add<std::string> stringAdder;
  std::string result = stringAdder.call("2", "5");
  REQUIRE(result == "25");
}

TEST_CASE("Test add with bool", "[Add]")
{
  Add<bool> boolAdder;
  bool result = boolAdder.call(true, true);
  REQUIRE(result == true);
}

/*
1.The first thing I can think of is we didn't test the constructor even though it doesn't take
parameters or anything. We also haven't tested any ADT or how it would add objects. We also
haven't tested that Add works as an AbstractOperator. We only test Add directly.

2. We do not need to overload for any of the primative data types we used. But, you would need to
overload the addition operator if you wanted to add objects or ADTs. The unittests we have only
test primative data types. I don't see any comments or indication on how the interface is supposed
to be used. So, if I gave I wouldn't know that I couldn't give it objects without reviewing the code.


*/