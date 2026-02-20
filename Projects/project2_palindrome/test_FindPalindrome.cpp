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
TEST_CASE("my test recursion from Destiny", "[FindPalindrome]")
{
	FindPalindrome p;

	REQUIRE(p.add("draw"));
	REQUIRE(p.add("O"));
	REQUIRE(p.add("Coward"));
	REQUIRE(p.number() == 1);
}

//Test basic functionality
TEST_CASE("Basic functionality", "[FindPalindrome]")
{
	//number returns the number of found palindromes
	FindPalindrome p;

	REQUIRE(p.add("draw"));
	REQUIRE(p.add("O"));
	REQUIRE(p.add("Coward"));
	REQUIRE(p.number() == 1);

	REQUIRE(p.add("a"));
	REQUIRE(p.add("AA"));
	REQUIRE(p.add("AaA"));
	REQUIRE(p.number() == 4);


	//clear clears the word bank vector and the found palindrome vector
	p.clear();
	REQUIRE(p.number() == 0);
}

TEST_CASE("Test add with reference value", "[FindPalindrome]")
{
	FindPalindrome p;
	//test that should return false with empty string
	REQUIRE(p.add("") == false);

	//check if every character is a-z or A-Z, otherwise return false.
	REQUIRE(p.add("adbs12") == false);
	REQUIRE(p.add("1") == false);

	//check for duplicate words that are also in the wordvector
	p.add("eve");
	p.add("aaa");
	p.add("purple");

	REQUIRE(p.add("eve") == false);
	REQUIRE(p.add("aaa") == false);
	REQUIRE(p.add("purple") == false);
	REQUIRE(p.add("dumpster") == true);
}

TEST_CASE("Test add with string vector part 1", "[FindPalindrome]")
{
	FindPalindrome p;

	std::vector <std::string> myStringVector;

	//check for empty vector
	REQUIRE(p.add("") == false);

	//check for empty word in vector
	myStringVector.push_back("year");
	myStringVector.push_back("bobTheBuilder");
	myStringVector.push_back("");
	myStringVector.push_back("cup");
	myStringVector.push_back("tatertot");
	REQUIRE(p.add(myStringVector) == false);

	p.clear();
	myStringVector.clear();

	//check that all strings only have a-z and A-Z
	myStringVector.push_back("redbull");
	myStringVector.push_back("solar");
	myStringVector.push_back("123");
	REQUIRE(p.add(myStringVector) == false);
	
	p.clear();
	myStringVector.clear();
}

TEST_CASE("Test add with string vector part 2", "[FindPalindrome]")
{
	FindPalindrome p;
	std::vector <std::string> myStringVector;
	
	//more tests for invalid characters
	myStringVector.push_back("red_bull");
	myStringVector.push_back("solar");
	myStringVector.push_back("oprah");
	REQUIRE(p.add(myStringVector) == false);

	p.clear();
	myStringVector.clear();

	//check for duplicate words that are in the word bank already
	myStringVector.push_back("aaa");
	myStringVector.push_back("ismy");
	myStringVector.push_back("awesome");
	myStringVector.push_back("testcase");
	myStringVector.push_back("pleasegivegoodgrade");	
	REQUIRE(p.add(myStringVector) == true);

	myStringVector.push_back("awesome");
	REQUIRE(p.add(myStringVector) == false);

	p.clear();
	myStringVector.clear();

	//check for dups in the string vector
	myStringVector.push_back("pleasegivegoodgrade");
	myStringVector.push_back("pleasegivegoodgrade");
	myStringVector.push_back("pleasegivegoodgrade");
	REQUIRE(p.add(myStringVector) == false);

}

//In the above example, after we’ve added "a", "AA", and "AaA", every "sentence" permutation is a palindrome, 
//therefore the number of sentence palindromes is N!. This should be a test case!
TEST_CASE("permutation count", "[FindPalindrome]")
{
	FindPalindrome p;

	p.add("b");
	p.add("bB");
	p.add("bBb");
	p.add("BbbB");
	p.add("BbBbb");
	p.add("BBBbbb");

	REQUIRE(p.number() == 720);
}

TEST_CASE("Test cut test 1", "[FindPalindrome]")
{
	FindPalindrome p;
	std::vector <std::string> myStringVector;

	myStringVector.push_back("eevve");	//not a palindrome but e is odd and v is even; odd count = 1
	REQUIRE(p.cutTest1(myStringVector) == true); 
	myStringVector.clear();

	myStringVector.push_back("eevvve");	//not a palindrome but e is odd and v is odd; odd count = 2
	REQUIRE(p.cutTest1(myStringVector) == false); 
	myStringVector.clear();
	
	myStringVector.push_back("eeevvvve");	//not a palindrome but e is even and v is even; odd count = 0
	REQUIRE(p.cutTest1(myStringVector) == true);
}

TEST_CASE("Test cut test 2", "[FindPalindrome]")
{

}

TEST_CASE("Test toVector function", "[FindPalindrome]")
{

}

TEST_CASE("Test invalid cases, with words", "[FindPalindrome]")
{

}

TEST_CASE("Test invalid cases, with empty strings", "[FindPalindrome]")
{

}