#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "sorted_list.hpp"
#include "list.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]")
{
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}

TEST_CASE("SortedList: Testing insert", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z')
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck;
  for (int i = 1; i <= 26; ++i)
  {
    getEntryCheck = (lst.getEntry(i) == 'a' + i - 1);
    if (!getEntryCheck)
    {
      break;
    }
  }
  REQUIRE(getEntryCheck);
}

TEST_CASE("SortedList: Testing remove", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a' + size)
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size - 1);
  REQUIRE(lst.getEntry(3) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size - 2);
  REQUIRE(lst.getEntry(6) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size - 3);
  REQUIRE(lst.getEntry(1) == 'b');
}

TEST_CASE("SortedList: Testing getPosition and repeated items", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');
  lst.insert('e');
  lst.insert('f');
  lst.insert('e');

  REQUIRE(lst.getLength() == 8);
  REQUIRE(lst.getPosition('a') == 1);
  REQUIRE(lst.getPosition('b') == 2);
  REQUIRE(lst.getPosition('c') == 3);
  REQUIRE(lst.getPosition('d') == 4);
  REQUIRE(lst.getPosition('e') == 5);
  REQUIRE(lst.getPosition('f') == 8);

  lst.clear();
  REQUIRE_THROWS(lst.getPosition('a'));
}

TEST_CASE("SortedList: Testing constructor from unsorted list", "[sorted list]")
{
  List<char> unsorted;

  unsorted.insert(1, 'a');
  unsorted.insert(2, 'd');
  unsorted.insert(3, 'e');
  unsorted.insert(4, 'c');
  unsorted.insert(5, 'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 1);
  REQUIRE(sorted.getPosition('b') == 2);
  REQUIRE(sorted.getPosition('c') == 3);
  REQUIRE(sorted.getPosition('d') == 4);
  REQUIRE(sorted.getPosition('e') == 5);
}

TEST_CASE("SortedList: Testing list and sorted list std::out_of_range exceptions", "[sorted list]")
{
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(2, 'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(1, 'a'), std::out_of_range);

  lst.insert(1, 'a');
  lst.insert(2, 'b');

  REQUIRE_THROWS_AS(lst.remove(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(4, 'c'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(3, 'c'), std::out_of_range);

  SortedList<char> sorted;
  sorted.insert('a');
  sorted.insert('b');
  sorted.insert('c');
  sorted.insert('d');
  sorted.insert('e');

  REQUIRE_THROWS_AS(sorted.removeAt(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.removeAt(-1), std::out_of_range);
}

/* Your tests here */
// List Tests

// Test List::insert throws std::out_of_range for invalid position
TEST_CASE("List: Testing insert throws std::out_of_range for invalid position", "[list]")
{
  List<char> lst;

  REQUIRE_THROWS_AS(lst.insert(0, 'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(2, 'b'), std::out_of_range);

  lst.insert(1, 'a');
  lst.insert(2, 'b');

  REQUIRE_THROWS_AS(lst.insert(4, 'c'), std::out_of_range);
}
// Test List::remove throws std::out_of_range for invalid position
TEST_CASE("List: Testing remove throws std::out_of_range for invalid position", "[list]")
{
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.remove(2), std::out_of_range);

  lst.insert(1, 'a');
  lst.insert(2, 'b');

  REQUIRE_THROWS_AS(lst.remove(3), std::out_of_range);
}

// SortedList Tests

// Test default constructor makes an empty list
TEST_CASE("SortedList: Testing default constructor makes an empty list", "[sorted list]")
{
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);
}

// Test constructor from unsorted list makes it sorted 
TEST_CASE("SortedList: Testing constructor from unsorted list makes it sorted", "[sorted list]")
{
  List<char> unsorted;

  unsorted.insert(1, 'd');
  unsorted.insert(2, 'b');
  unsorted.insert(3, 'e');
  unsorted.insert(4, 'a');
  unsorted.insert(5, 'c');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getLength() == 5);
  REQUIRE(sorted.getEntry(1) == 'a');
  REQUIRE(sorted.getEntry(2) == 'b');
  REQUIRE(sorted.getEntry(3) == 'c');
  REQUIRE(sorted.getEntry(4) == 'd');
  REQUIRE(sorted.getEntry(5) == 'e');
}

// Test remove successfully removes an existing item
TEST_CASE("SortedList: Testing remove throws std::invalid_argument when is not found", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('b');
  lst.insert('c');

  REQUIRE_THROWS_AS(lst.remove('d'), std::invalid_argument);
}

// Test remove throws std::invalid_argument when item not found
TEST_CASE("SortedList: Testing remove on an existing item", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('b');
  lst.insert('c');

  lst.remove('b');
  REQUIRE(lst.getLength() == 2);
  REQUIRE(lst.getEntry(1) == 'a');
  REQUIRE(lst.getEntry(2) == 'c');
}

// Test removeAt 
TEST_CASE("SortedList: Testing removeAt", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('b');
  lst.insert('c');

  lst.removeAt(2);
  REQUIRE(lst.getLength() == 2);
  REQUIRE(lst.getEntry(1) == 'a');
  REQUIRE(lst.getEntry(2) == 'c');
}

// Test removeAt throws std::out_of_range on invalid position
TEST_CASE("SortedList: Testing removeAt throws std::out_of_range on invalid position", "[sorted list]")
{
  SortedList<char> lst;

  REQUIRE_THROWS_AS(lst.removeAt(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.removeAt(2), std::out_of_range);

  lst.insert('a');
  lst.insert('b');

  REQUIRE_THROWS_AS(lst.removeAt(3), std::out_of_range);
}

// Test getPosition returns correct position for existing item
TEST_CASE("SortedList: Testing getPosition returns correct position for existing item", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('c');
  lst.insert('e');
  lst.insert('b');
  lst.insert('d');

  REQUIRE(lst.getPosition('a') == 1);
  REQUIRE(lst.getPosition('b') == 2);
  REQUIRE(lst.getPosition('c') == 3);
  REQUIRE(lst.getPosition('d') == 4);
  REQUIRE(lst.getPosition('e') == 5);
}

// Test getPosition throws std::invalid_argument when item not found
TEST_CASE("SortedList: Testing getPosition throws std::invalid_argument when item not found", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('b');
  lst.insert('c');

  REQUIRE_THROWS_AS(lst.getPosition('d'), std::invalid_argument);
}

// Test with a different data type
TEST_CASE("SortedList: Testing with different data type", "[sorted list]")
{
  SortedList<int> lst;

  lst.insert(5);
  lst.insert(3);
  lst.insert(8);
  lst.insert(1);

  REQUIRE(lst.getLength() == 4);
  REQUIRE(lst.getEntry(1) == 1);
  REQUIRE(lst.getEntry(2) == 3);
  REQUIRE(lst.getEntry(3) == 5);
  REQUIRE(lst.getEntry(4) == 8);

  REQUIRE(lst.getPosition(3) == 2);
  REQUIRE_THROWS_AS(lst.getPosition(10), std::invalid_argument);

  lst.remove(3);
  REQUIRE(lst.getLength() == 3);
  REQUIRE_THROWS_AS(lst.getPosition(3), std::invalid_argument);
}
// Test with a different data type std::string
TEST_CASE("SortedList: Testing with std::string data type", "[sorted list]")
{
  SortedList<std::string> lst;
  lst.insert("ECE302");
  lst.insert("Pitt");
  lst.insert("Challenging");
  REQUIRE(lst.getLength() == 3);
  REQUIRE(lst.getEntry(1) == "Challenging");
  REQUIRE(lst.getEntry(2) == "ECE302");
  REQUIRE(lst.getEntry(3) == "Pitt");
  REQUIRE(lst.getPosition("ECE302") == 2);
  REQUIRE_THROWS_AS(lst.getPosition("date"), std::invalid_argument);
  lst.remove("ECE302");
  REQUIRE(lst.getLength() == 2);
  REQUIRE_THROWS_AS(lst.getPosition("ECE302"), std::invalid_argument);
}