#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <string.h>
#include <iostream>
#include "bitarray.hpp"

// Given test cases for BitArray class
TEST_CASE("Bitarray: Test default construction and asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    // std::string class has compare() member function that returns 0 if the strings are equal
    // research online for more details
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction with asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction size and asString", "[bitarray]")
{
    // You can construct a string s of as s(n, c)
    // where n is the number of characters and c is the character
    std::string s(64, '0');
    BitArray b(64);
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test many given methods combined", "[bitarray]")
{
    // << is the left shift operator for integers
    // e.g., 1 << 8 is 2^8=256, 1<<15 is 2^15=32768
    std::string s((1 << 15), '0'); // string of many-many zeros
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    // Test a very long BitArray by setting, resetting, toggling, and testing bits
    for (int i = 1; i < (1 << 10); i++)
    {
        REQUIRE(b.good());

        b.set(i);                // set first 1..1023 bits to 1
        b.reset(i + (1 << 10));  // reset bits 1025..2047 to 0
        b.toggle(i + (1 << 11)); // toggle bits 2049..3071

        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1 << 10)));
        REQUIRE((
            (b.test(i + (1 << 11)) == true && s.at(i + (1 << 11)) == '0') || // either this is true
            (b.test(i + (1 << 11)) == false && s.at(i + (1 << 11)) == '1')   // or this is true
            ));
    }
}

// Write your own test cases below


TEST_CASE("Test set method with valid and invalid indices", "[bitarray]")
{
    BitArray b(10);
    REQUIRE(b.good());

    b.set(5);
    REQUIRE(b.test(5));

    b.set(0);
    REQUIRE(b.test(0));

    b.set(9);
    REQUIRE(b.test(9));

    b.set(10); // Invalid index
    REQUIRE_FALSE(b.good());

    BitArray b2(5);
    REQUIRE(b2.good());
    b2.set(-1); // Invalid index
    REQUIRE_FALSE(b2.good());
}

TEST_CASE("Test String constructor with valid and invalid inputs", "[bitarray]")
{
    BitArray b1("11111111");
    REQUIRE(b1.size() == 8);
    REQUIRE(b1.good());
    REQUIRE(b1.asString().compare("11111111") == 0);

    BitArray b2("000011112222");
    REQUIRE_FALSE(b2.good());

    BitArray b3("abcd");
    REQUIRE_FALSE(b3.good());

    BitArray b4("10101010000");
    REQUIRE(b4.size() == 11);
    REQUIRE(b4.good());
}

TEST_CASE("Test Constructor with invalid size", "[bitarray]")
{
    BitArray b(-5); // Invalid size
    REQUIRE_FALSE(b.good());

    BitArray b2(0); // Size zero is invalid
    REQUIRE_FALSE(b2.good());
}

TEST_CASE("Test reset and toggle methods", "[bitarray]")
{
    BitArray b(5);
    REQUIRE(b.good());

    b.set(2);
    REQUIRE(b.test(2));

    b.reset(2);
    REQUIRE_FALSE(b.test(2));

    b.toggle(1);
    REQUIRE(b.test(1));

    b.toggle(1);
    REQUIRE_FALSE(b.test(1));

    b.reset(5); // Invalid index
    REQUIRE_FALSE(b.good());

    BitArray b2(3);
    REQUIRE(b2.good());
    b2.toggle(-1); // Invalid index
    REQUIRE_FALSE(b2.good());
}

TEST_CASE("Test test() out of range indices", "[bitarray]")
{
    BitArray b(4);
    REQUIRE(b.good());

    REQUIRE_FALSE(b.test(4)); // Invalid index
    REQUIRE_FALSE(b.good());

    BitArray b2(6);
    REQUIRE(b2.good());
    REQUIRE_FALSE(b2.test(-2)); // Invalid index
    REQUIRE_FALSE(b2.good());
}

TEST_CASE("Test default and string constructor", "[bitarray]")
{
    BitArray b;
    BitArray bstring("00000000");

    std::string resultString = b.asString();
   
    REQUIRE((b.asString().compare(bstring.asString()) == 0));
}

//write a test case that overload < check 000<001 or 001 < 011
TEST_CASE("Test new overloaded operator", "[bitarray]")
{
    BitArray b1("00000000");
    BitArray b2("00000001");

    REQUIRE((b1 < b2) == true);   // 0 should be less than one and return true

    BitArray b3("01011100");
    BitArray b4("00100100");  

    REQUIRE((b4 < b3 ) == true);   //1 should be less than 6

    //make require statement that throws exception when cant compare strings of different lengths
    BitArray b5("0000");
    BitArray b6("000000");
    REQUIRE_THROWS_AS(b5 < b6, std::logic_error);
}
