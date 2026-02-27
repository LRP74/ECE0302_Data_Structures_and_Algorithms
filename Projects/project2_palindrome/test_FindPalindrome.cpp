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

	myStringVector.push_back("eevve");	//not a palindrome but e is odd and v is even; odd count = 1 should pass
	REQUIRE(p.cutTest1(myStringVector) == true); 
	myStringVector.clear();

	myStringVector.push_back("eevvve");	//not a palindrome but e is odd and v is odd; odd count = 2 should fail
	REQUIRE(p.cutTest1(myStringVector) == false); 
	myStringVector.clear();

	myStringVector.push_back("eeevvvve");	//not a palindrome but e is even and v is even; odd count = 0 should pass
	REQUIRE(p.cutTest1(myStringVector) == true);
}

TEST_CASE("Test cut test 2, part 1", "[FindPalindrome]")
{
	FindPalindrome p;
	std::vector <std::string> smallerStringVector;
	std::vector <std::string> largerStringVector;

	smallerStringVector.push_back("toe");
	smallerStringVector.push_back("may");
	smallerStringVector.push_back("pop");	//total letters = 9

	largerStringVector.push_back("four");
	largerStringVector.push_back("yoga");
	largerStringVector.push_back("lard");	//total letters = 12

	REQUIRE(p.cutTest2(smallerStringVector, largerStringVector) == false);

}

TEST_CASE("Test cut test 2, part 2", "[FindPalindrome]")
{
	FindPalindrome p;
	std::vector <std::string> smallerStringVector;
	std::vector <std::string> largerStringVector;

	smallerStringVector.push_back("at");
	smallerStringVector.push_back("no");
	smallerStringVector.push_back("be");	//total letters = 6

	largerStringVector.push_back("bone");
	largerStringVector.push_back("tent");
	largerStringVector.push_back("aa");		//total letters = 10

	REQUIRE(p.cutTest2(smallerStringVector, largerStringVector) == true);
	
}

TEST_CASE("Test toVector function", "[FindPalindrome]")
{
	FindPalindrome p;

	REQUIRE(p.add("draw"));
	REQUIRE(p.add("O"));
	REQUIRE(p.add("Coward"));
	REQUIRE(p.number() == 1);

    std::vector<std::vector<std::string>> result = p.toVector();

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].size() == 3);
    REQUIRE(result[0][0] == "draw");
    REQUIRE(result[0][1] == "O");
    REQUIRE(result[0][2] == "Coward");

}

TEST_CASE("Test case-insensitive duplicate", "[FindPalindrome]")
{
	//make sure you can't add the same thing with different cases
    FindPalindrome p;

    REQUIRE(p.add("Happy"));
    REQUIRE(p.add("happy") == false);
    REQUIRE(p.add("HAPPY") == false);
    REQUIRE(p.add("hApPy") == false);
}

TEST_CASE("Test non-palindrome case", "[FindPalindrome]")
{
   //give it a non palindrome and make sure it can't find one
	FindPalindrome p;

    REQUIRE(p.add("hello"));
    REQUIRE(p.add("world"));
    REQUIRE(p.number() == 0);
}

// Write a test case demonstrating that cutTest2 fails when comparing two string vectors: 
// Vector 1 is a longer string vector with a lower frequency of the letter 'a',
//  Vector 2 is a shorter string vector with a higher frequency of the letter 'a'. 
//  (Maintain Vec1 has higher frequency of other letters)
TEST_CASE("cut test 2 checkoff", "[FindPalindrome]")
{
	FindPalindrome p;

	std::vector <std::string> vector1;
	std::vector <std::string> vector2;

	vector1.push_back("aaabbbbb");

	vector2.push_back("aaaa");

	REQUIRE(p.cutTest2(vector1, vector2) == false);

}

//Write a test case to verify that if you add each vector that is already the size of 2 and each vector is already a palindrome, 
// the object would have a number of palindromes of at least n! (n is the vector size). 
// For example, adding {"de", "ed"}, {"no", "on"}, {"pe", "ep"}, {"ab", "ba"}, it would be at least 24 palindromes.
TEST_CASE("verify vector add thing checkoff", "[FindPalindrome]")
{
	FindPalindrome p;

	std::vector <std::string> stringVector1;
	std::vector <std::string> stringVector2;
	std::vector <std::string> stringVector3;
	std::vector <std::string> stringVector4;

	stringVector1.push_back("de");
	stringVector1.push_back("ed");
	stringVector2.push_back("on");
	stringVector2.push_back("no");
	stringVector3.push_back("pe");
	stringVector3.push_back("ep");
	stringVector4.push_back("ab");
	stringVector4.push_back("ba");

	p.add(stringVector1);
	p.add(stringVector2);
	p.add(stringVector3);
	p.add(stringVector4);

	REQUIRE(p.number() >= 24);
}

//remove coward and it should be 0
TEST_CASE("remove TDD checkoff", "[FindPalindrome]")
{
	FindPalindrome p;

	REQUIRE(p.add("draw"));
	REQUIRE(p.add("O"));
	REQUIRE(p.add("Coward"));
	REQUIRE(p.number() == 1);

	p.remove("Coward");
	REQUIRE(p.number() == 0);
}

TEST_CASE("remove 2 checkoff", "[FindPalindrome]")
{
	FindPalindrome p;

	REQUIRE(p.add("a"));
	REQUIRE(p.add("AA"));
	REQUIRE(p.add("AaA"));
	REQUIRE(p.number() == 6);

	p.remove("AaA");
	REQUIRE(p.number() == 2);	
}