#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"
#include "linked_list.hpp"

TEST_CASE("Lists: Test ArrayList 1-index Edge Cases", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty());

  REQUIRE_FALSE(list.insert(0, 0)); // invalid
  REQUIRE(list.isEmpty());          // still empty

  REQUIRE(list.insert(1, 1));     // valid
  REQUIRE(list.getLength() == 1); // length is 1

  REQUIRE_FALSE(list.remove(0));  // invalid
  REQUIRE(list.getLength() == 1); // length is still 1

  REQUIRE(list.remove(1)); // valid
  REQUIRE(list.isEmpty()); // now empty

  list.insert(1, 301);
  list.insert(2, 302);

  REQUIRE(list.getEntry(1) == 301);
  REQUIRE(list.getEntry(2) == 302);

  REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(list.setEntry(0, 300), std::out_of_range);

  // pos = 1 is the first list item, that also indicates pos = n is the last list item
  // your insertion at pos=n is valid (which makes the old last item shift to right),
  // and your insertion at pos=n+1 is also valid (which appends to the end of the list)
  // your removal at pos=1 is valid, but your removal at pos=n+1 is invalid
}

TEST_CASE("Lists: Test LinkedList 1-index Edge Cases", "[LinkedList]")
{
  LinkedList<int> list;
  REQUIRE(list.isEmpty());

  REQUIRE_FALSE(list.insert(0, 0)); // invalid
  REQUIRE(list.isEmpty());          // still empty

  REQUIRE(list.insert(1, 1));     // valid
  REQUIRE(list.getLength() == 1); // length is 1

  REQUIRE_FALSE(list.remove(0));  // invalid
  REQUIRE(list.getLength() == 1); // length is still 1

  REQUIRE(list.remove(1)); // valid
  REQUIRE(list.isEmpty()); // now empty

  list.insert(1, 301);
  list.insert(2, 302);

  REQUIRE(list.getEntry(1) == 301);
  REQUIRE(list.getEntry(2) == 302);

  REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(list.setEntry(0, 300), std::out_of_range);

  // pos = 1 is the first list item, that also indicates pos = n is the last list item
  // your insertion at pos=n is valid (which makes the old last item shift to right),
  // and your insertion at pos=n+1 is also valid (which appends to the end of the list)
  // your removal at pos=1 is valid, but your removal at pos=n+1 is invalid
}

//
// my test cases for clear() efficiency and ArrayList insert() when full
//
TEST_CASE("Lists: Test LinkedList clear() inefficiency", "[LinkedList]")
{
  LinkedList<int> list;
  for (int i = 1; i <= 5; i++)
  {
    list.insert(i, i);
  }
  REQUIRE(list.getLength() == 5);

  list.clear();
  REQUIRE(list.isEmpty());
  // The clear() implementation is inefficient because it removes each item one by one, which involves 
  //shifting the remaining items and updating pointers for each removal. This results in O(n^2) time complexity in the worst 
  //case, where n is the number of items in the list. A more efficient implementation would simply delete all nodes without shifting,
  // resulting in O(n) time complexity.
}

TEST_CASE("Lists: Test ArrayList clear() efficiency", "[ArrayList]")
{
  ArrayList<int> list;
  for (int i = 1; i <= 5; i++)
  {
    list.insert(i, i);
  }
  REQUIRE(list.getLength() == 5);

  list.clear();
  REQUIRE(list.isEmpty());
  // The clear() implementation for ArrayList is efficient because it simply resets the item count to zero, 
  // without needing to shift any items or update pointers. This results in O(1) time complexity, regardless of the number of items in the list.
}

TEST_CASE("Lists: Test ArrayList insert() when full", "[ArrayList]")
{
  ArrayList<int> list;
  for (int i = 1; i <= 5; i++)
  {
    REQUIRE(list.insert(i, i)); // Insert until full
  }
  REQUIRE_FALSE(list.insert(6, 6)); // Attempt to insert when full should fail
}

TEST_CASE("Lists: Test LinkedList insert() when full", "[LinkedList]")
{
  LinkedList<int> list;
  for (int i = 1; i <= 5; i++)
  {
    REQUIRE(list.insert(i, i)); // Insert until full
  }
  REQUIRE(list.insert(6, 6)); // LinkedList should allow insertion beyond initial size
}

TEST_CASE("Test linked list clear() on empty list", "[LinkedList]")
{
  LinkedList<int> list;
  REQUIRE(list.isEmpty());
  list.clear(); // Clearing an already empty list should not cause any issues
  REQUIRE(list.isEmpty());
}

TEST_CASE("Test array list clear() on empty list", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty());
  list.clear(); // Clearing an already empty list should not cause any issues
  REQUIRE(list.isEmpty());
}

TEST_CASE("Test linked list insert() at position 1 on empty list", "[LinkedList]")
{
  LinkedList<int> list;
  REQUIRE(list.isEmpty());
  REQUIRE(list.insert(1, 10)); // Inserting at position 1 on an empty list should be valid
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 10);
}

TEST_CASE("Test array list insert() at position 1 on empty list", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty());
  REQUIRE(list.insert(1, 10)); // Inserting at position 1 on an empty list should be valid
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 10);
}

TEST_CASE("Test all linked list functions for normal operations", "[LinkedList]")
{
  LinkedList<int> list;
  REQUIRE(list.isEmpty());
  REQUIRE(list.insert(1, 10));
  REQUIRE(list.insert(2, 20));
  REQUIRE(list.insert(3, 30));
  REQUIRE(list.getLength() == 3);
  REQUIRE(list.getEntry(1) == 10);
  REQUIRE(list.getEntry(2) == 20);
  REQUIRE(list.getEntry(3) == 30);
  list.setEntry(2, 25);
  REQUIRE(list.getEntry(2) == 25);
  REQUIRE(list.remove(1));
  REQUIRE(list.getLength() == 2);
}

TEST_CASE("Test all array list functions for normal operations", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty());
  REQUIRE(list.insert(1, 10));
  REQUIRE(list.insert(2, 20));
  REQUIRE(list.insert(3, 30));
  REQUIRE(list.getLength() == 3);
  REQUIRE(list.getEntry(1) == 10);
  REQUIRE(list.getEntry(2) == 20);
  REQUIRE(list.getEntry(3) == 30);
  list.setEntry(2, 25);
  REQUIRE(list.getEntry(2) == 25);
  REQUIRE(list.remove(1));
  REQUIRE(list.getLength() == 2);
}