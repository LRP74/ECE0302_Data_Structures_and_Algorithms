#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "list.hpp"
#include "quicksort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // move forward
  lst.moveEntry(1, 3);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 11);

  // move backward
  lst.moveEntry(5, 1);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 11);
  REQUIRE(lst.getEntry(2) == 4);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 100);
  REQUIRE(lst.getEntry(5) == 25);
}

TEST_CASE("Sort: Integer sorting", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  quick_sort(lst, 1, lst.getLength()); // note the change here!

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);
}

TEST_CASE("Sort: Test move entry throw", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // try to move forward
  REQUIRE_THROWS(lst.moveEntry(1, 6));
  REQUIRE_THROWS(lst.moveEntry(0, 5));

  lst.insert(5, 11);
  REQUIRE_NOTHROW(lst.moveEntry(1, 6));

  // try to move backward
  REQUIRE_THROWS(lst.moveEntry(7, 1));
  REQUIRE_THROWS(lst.moveEntry(6, -1));
}

/* Your test cases */
TEST_CASE("Test out of range" , "[sorting]")
{
  List<int> myList;
  
  myList.insert(1, 100);
  myList.insert(2, 4);
  myList.insert(3, 10);
  myList.insert(4, 25);
  myList.insert(5, 11);

  REQUIRE_THROWS(myList.moveEntry(0 , 3));
  REQUIRE_THROWS(myList.moveEntry(2 , 23));
}

//partition correct test for string
TEST_CASE("Partition correct test for string", "[sorting]")
{
  List<std::string> lst;

  lst.insert(1, "banana");
  lst.insert(2, "apple");
  lst.insert(3, "grape");
  lst.insert(4, "orange");
  lst.insert(5, "kiwi");

  int pivotIndex = partition(lst, 1, lst.getLength());

  // Check that the pivot is in the correct position
  std::string pivot = lst.getEntry(pivotIndex);
  REQUIRE(pivot == "kiwi");

  // Check that elements to the left of the pivot are less than or equal to the pivot
  for (int i = 1; i < pivotIndex; i++)
  {
    REQUIRE(lst.getEntry(i) <= pivot);
  }

  // Check that elements to the right of the pivot are greater than or equal to the pivot
  for (int i = pivotIndex + 1; i <= lst.getLength(); i++)
  {
    REQUIRE(lst.getEntry(i) >= pivot);
  }
}

//partition correct test for char
TEST_CASE("Partition correct test for char", "[sorting]")
{
  List<char> lst;

  lst.insert(1, 'd');
  lst.insert(2, 'a');
  lst.insert(3, 'c');
  lst.insert(4, 'e');
  lst.insert(5, 'b');

  int pivotIndex = partition(lst, 1, lst.getLength());

  // Check that the pivot is in the correct position
  char pivot = lst.getEntry(pivotIndex);
  REQUIRE(pivot == 'b');

  // Check that elements to the left of the pivot are less than or equal to the pivot
  for (int i = 1; i < pivotIndex; i++)
  {
    REQUIRE(lst.getEntry(i) <= pivot);
  }

  // Check that elements to the right of the pivot are greater than or equal to the pivot
  for (int i = pivotIndex + 1; i <= lst.getLength(); i++)
  {
    REQUIRE(lst.getEntry(i) >= pivot);
  }
}

//partition correct test for double
TEST_CASE("Partition correct test for double", "[sorting]")
{
  List<double> lst;

  lst.insert(1, 3.14);
  lst.insert(2, 2.71);
  lst.insert(3, 1.41);
  lst.insert(4, 0.577);
  lst.insert(5, 1.618);

  int pivotIndex = partition(lst, 1, lst.getLength());

  // Check that the pivot is in the correct position
  double pivot = lst.getEntry(pivotIndex);
  REQUIRE(pivot == Approx(1.618));

  // Check that elements to the left of the pivot are less than or equal to the pivot
  for (int i = 1; i < pivotIndex; i++)
  {
    REQUIRE(lst.getEntry(i) <= pivot);
  }

  // Check that elements to the right of the pivot are greater than or equal to the pivot
  for (int i = pivotIndex + 1; i <= lst.getLength(); i++)
  {
    REQUIRE(lst.getEntry(i) >= pivot);
  }
}

//partition exception test
TEST_CASE("Partition exception test", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  REQUIRE_THROWS(partition(lst, 0, lst.getLength()));
  REQUIRE_THROWS(partition(lst, 1, lst.getLength() + 1));
  REQUIRE_THROWS(partition(lst, 3, 2));
}

//quick_sort on:sorted list
TEST_CASE("Quick_sort on sorted list", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 1);
  lst.insert(2, 2);
  lst.insert(3, 3);
  lst.insert(4, 4);
  lst.insert(5, 5);

  quick_sort(lst, 1, lst.getLength());

  REQUIRE(lst.getEntry(1) == 1);
  REQUIRE(lst.getEntry(2) == 2);
  REQUIRE(lst.getEntry(3) == 3);
  REQUIRE(lst.getEntry(4) == 4);
  REQUIRE(lst.getEntry(5) == 5);
}

//quick_sort on:reverse list
TEST_CASE("Quick_sort on reverse list", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 5);
  lst.insert(2, 4);
  lst.insert(3, 3);
  lst.insert(4, 2);
  lst.insert(5, 1);

  quick_sort(lst, 1, lst.getLength());

  REQUIRE(lst.getEntry(1) == 1);
  REQUIRE(lst.getEntry(2) == 2);
  REQUIRE(lst.getEntry(3) == 3);
  REQUIRE(lst.getEntry(4) == 4);
  REQUIRE(lst.getEntry(5) == 5);
}

//quick_sort on:duplicates
TEST_CASE("Quick_sort on duplicates", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 3);
  lst.insert(2, 1);
  lst.insert(3, 2);
  lst.insert(4, 3);
  lst.insert(5, 1);

  quick_sort(lst, 1, lst.getLength());

  REQUIRE(lst.getEntry(1) == 1);
  REQUIRE(lst.getEntry(2) == 1);
  REQUIRE(lst.getEntry(3) == 2);
  REQUIRE(lst.getEntry(4) == 3);
  REQUIRE(lst.getEntry(5) == 3);
}

//quick_sort on:single element
TEST_CASE("Quick_sort on single element", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 42);

  quick_sort(lst, 1, lst.getLength());

  REQUIRE(lst.getEntry(1) == 42);
}

//quick_sort on:empty list
TEST_CASE("Quick_sort on empty list", "[sorting]")
{
  List<int> lst;

  quick_sort(lst, 1, lst.getLength());

  REQUIRE(lst.getLength() == 0);
}

//quick_sort exception test
TEST_CASE("Quick_sort exception test", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  REQUIRE_THROWS(quick_sort(lst, 0, lst.getLength()));
  REQUIRE_THROWS(quick_sort(lst, 1, lst.getLength() + 1));
  REQUIRE_THROWS(quick_sort(lst, 3, 2));
}

//moveEntry same-index test
TEST_CASE("MoveEntry same-index test", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  lst.moveEntry(3, 3); // moving entry to the same index should not change the list

  REQUIRE(lst.getEntry(1) == 100);
  REQUIRE(lst.getEntry(2) == 4);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 11);
}
