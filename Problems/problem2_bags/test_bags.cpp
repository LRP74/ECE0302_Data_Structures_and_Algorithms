#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"
#include "dynamic_bag.hpp"

TEST_CASE("Calling all public methods of LimitedSizeBag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("Calling all public methods of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

//
// My Limited bag test cases
// test cases should check functionality of add, remove, isEmpty, getsizeof, contains, clear, frequency, and = overload
//
TEST_CASE("Testing limited bag isEmpty and currentSize functions for basic functionality", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;

  REQUIRE(L1.isEmpty() == true);  //default bag is empty
  REQUIRE(L1.getCurrentSize() == 0);  //default bag size is 0
}
TEST_CASE("Testing limited bag addd and currentSize functions for basic functionality", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;  

  for (int i = 0; i < 5; i++) //add 5 items
  {
    L1.add(i + 1);
  }
  
  for (int i = 0; i < 5; i++) //check if they are in the bag
  {
    REQUIRE(L1.contains(i + 1) == true);
  }
  
  REQUIRE(L1.getCurrentSize() == 5);  //check size is 5
}
TEST_CASE("Testing limited bag getFrequency functions for basic functionality", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;
  for (int i = 0; i < 5; i++) //add 5 items
  {
    L1.add(i + 1);
  }
  
  for (int i = 0; i < 5; i++) //check frequency of each item is 1
  {
    REQUIRE(L1.getFrequencyOf(i + 1) == 1);
  }
}

TEST_CASE("Testing limited bag remove functions for basic functionality", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;

  for (int i = 0; i < 5; i++) //add 5 items
  {
    L1.add(i + 1);
  }

  L1.remove(3); //remove item 3

  REQUIRE(L1.getCurrentSize() == 4);  //check size again
  REQUIRE(L1.contains(3) == false); //make sure 3 is gone

  REQUIRE(L1.add(7) == true); //add another element
}
  
TEST_CASE("Testing limited bag assignment operator for basic functionality", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;

  for (int i = 0; i < 5; i++) //add 5 items
  {
    L1.add(i + 1);
  }

  LimitedSizeBag<int> L2;
  L2 = L1;

  REQUIRE((L1 == L2) == true);  //test assignment operator
}

TEST_CASE("Test limited bag for clear function", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;

  for (int i = 0; i < 5; i++) //add 5 items
  {
    L1.add(i + 1);
  }

  L1.clear();
  REQUIRE(L1.isEmpty() == true); //check if clear worked
}

TEST_CASE("Test limited bag functions for removing from empty bag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;

  REQUIRE(L1.remove(10) == false); //removing from empty bag
}

TEST_CASE("Test limited bag functions for adding to full bag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;
  for (int i = 0; i < LimitedSizeBag<int>::maxsize; i++)
  {
    L1.add(i);
  }

  REQUIRE(L1.add(101) == false); //adding to full bag
}

TEST_CASE("Test limited bag functions for getting frequency of item not in bag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> L1;

  REQUIRE(L1.getFrequencyOf(200) == 0); //frequency of item not in bag

  L1.clear();
  REQUIRE(L1.isEmpty() == true); //check if clear worked
}

TEST_CASE("Testing limited bag X functions for basic functionality using doubles", "[LimitedSizeBag]")
{
  LimitedSizeBag<double> L1;

  REQUIRE(L1.isEmpty() == true);
  REQUIRE(L1.getCurrentSize() == 0);

  for (int i = 0; i < 5; i++)
  {
    L1.add(i + 1);
  }
  
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(L1.contains(i + 1) == true);
  }
  
  REQUIRE(L1.getCurrentSize() == 5);
  
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(L1.getFrequencyOf(i + 1) == 1);
  }

  L1.remove(3);

  REQUIRE(L1.getCurrentSize() == 4);
  REQUIRE(L1.contains(3) == false);

  REQUIRE(L1.add(7) == true);

  LimitedSizeBag<double> L2;
  L2 = L1;

  REQUIRE((L1 == L2) == true);
}

//
// My Dynamic bag test cases
// test cases should check functionality of add, remove, isEmpty, getsizeof, contains, clear, frequency, and = overload
//
TEST_CASE("Testing dynamic bag isEmpty and currentSize functions for basic functionality", "[DynamicBag]")
{
  DynamicBag<int> D1;

  REQUIRE(D1.isEmpty() == true);  //default bag is empty
  REQUIRE(D1.getCurrentSize() == 0);  //default bag size is 0
}

TEST_CASE("Testing dynamic bag add and currentSize functions for basic functionality", "[DynamicBag]")
{
  DynamicBag<int> D1;
  for (int i = 0; i < 5; i++) //add 5 items
  {
    D1.add(i + 1);
  }
  for (int i = 0; i < 5; i++) //check if they are in the bag
  {
    REQUIRE(D1.contains(i + 1) == true);
  }
  REQUIRE(D1.getCurrentSize() == 5);  //check size is 5
}

TEST_CASE("Testing dynamic bag getFrequency functions for basic functionality", "[DynamicBag]")
{
  DynamicBag<int> D1;
  for (int i = 0; i < 5; i++) //add 5 items
  {
    D1.add(i + 1);
  }
  for (int i = 0; i < 5; i++) //check frequency of each item is 1
  {
    REQUIRE(D1.getFrequencyOf(i + 1) == 1);
  }
}
TEST_CASE("Testing dynamic bag remove functions for basic functionality", "[DynamicBag]")
{
  DynamicBag<int> D1;
  for (int i = 0; i < 5; i++) //add 5 items
  {
    D1.add(i + 1);
  }
  D1.remove(3); //remove item 3
  REQUIRE(D1.getCurrentSize() == 4);  //check size again
  REQUIRE(D1.contains(3) == false); //make sure 3 is gone
  REQUIRE(D1.add(7) == true); //add another element
}
TEST_CASE("Testing dynamic bag assignment operator for basic functionality", "[DynamicBag]")
{
  DynamicBag<int> D1;
  for (int i = 0; i < 5; i++) //add 5 items
  {
    D1.add(i + 1);
  }
  DynamicBag<int> D2;
  D2 = D1;
  REQUIRE((D1 == D2) == true);  //test assignment operator
}
TEST_CASE("Test dynamic bag for clear function", "[DynamicBag]")
{
  DynamicBag<int> D1;
  for (int i = 0; i < 5; i++) //add 5 items
  {
    D1.add(i + 1);
  }
  D1.clear();
  REQUIRE(D1.isEmpty() == true); //check if clear worked
}

TEST_CASE("Test dynamic bag functions for removing from empty bag", "[DynamicBag]")
{
  DynamicBag<int> D1;

  REQUIRE(D1.remove(10) == false); //removing from empty bag
}

TEST_CASE("Test dynamic bag functions for getting frequency of item not in bag", "[DynamicBag]")
{
  DynamicBag<int> D1;

  REQUIRE(D1.getFrequencyOf(200) == 0); //frequency of item not in bag

  D1.clear();
  REQUIRE(D1.isEmpty() == true); //check if clear worked
}

TEST_CASE("Testing dynamic bag functions for basic functionality using doubles", "[DynamicBag]")
{
  DynamicBag<double> D1;

  REQUIRE(D1.isEmpty() == true);
  REQUIRE(D1.getCurrentSize() == 0);

  for (int i = 0; i < 5; i++)
  {
    D1.add(i + 1);
  }
  
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(D1.contains(i + 1) == true);
  }
  
  REQUIRE(D1.getCurrentSize() == 5);
  
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(D1.getFrequencyOf(i + 1) == 1);
  }

  D1.remove(3);

  REQUIRE(D1.getCurrentSize() == 4);
  REQUIRE(D1.contains(3) == false);

  REQUIRE(D1.add(7) == true);

  DynamicBag<double> D2;
  D2 = D1;

  REQUIRE((D1 == D2) == true);
}