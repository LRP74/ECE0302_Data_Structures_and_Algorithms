#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

TEST_CASE("Test adding words", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]")
{
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

/** Your Test Cases Go Here */
TEST_CASE("my test recursion", "[FindPalindrome]")
{
	FindPalindrome p;

	REQUIRE(p.add("draw"));
	REQUIRE(p.add("O"));
	REQUIRE(p.add("Coward"));
	REQUIRE(p.number() == 1);
}