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
// my test cases 
//

//TEST CASES FOR ARRAY LIST
TEST_CASE("ArrayList: Test Empty List Functions", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty() == true);
  REQUIRE(list.getLength() == 0);
  REQUIRE_FALSE(list.remove(1));
  REQUIRE_THROWS_AS(list.getEntry(1), std::out_of_range);
}

TEST_CASE("ArrayList: Test Insert at Various Positions", "[ArrayList]")
{
  ArrayList<int> list;
  // Insert into empty list
  REQUIRE(list.insert(1, 10) == true);
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 10);
  // Insert at head
  REQUIRE(list.insert(1, 20) == true);
  REQUIRE(list.getLength() == 2);
  REQUIRE(list.getEntry(1) == 20);
  REQUIRE(list.getEntry(2) == 10);
  // Insert at middle
  REQUIRE(list.insert(2, 30) == true);
  REQUIRE(list.getLength() == 3);     
  REQUIRE(list.getEntry(1) == 20);
  REQUIRE(list.getEntry(2) == 30);
  REQUIRE(list.getEntry(3) == 10);
  // Insert at end (append)
  REQUIRE(list.insert(4, 40) == true);
  REQUIRE(list.getLength() == 4);   
  REQUIRE(list.getEntry(1) == 20);
  REQUIRE(list.getEntry(2) == 30);
  REQUIRE(list.getEntry(3) == 10);
  REQUIRE(list.getEntry(4) == 40);
  // Invalid insert positions
  REQUIRE(list.insert(0, 50) == false);
  REQUIRE(list.insert(6, 60) == false);
  REQUIRE(list.getLength() == 4); // List remains unchanged
}

TEST_CASE("ArrayList: Test Remove at Various Positions", "[ArrayList]")
{
  ArrayList<int> list;
  list.insert(1, 10);
  list.insert(2, 20);
  list.insert(3, 30);
  list.insert(4, 40);
  // Remove head
  REQUIRE(list.remove(1) == true);
  REQUIRE(list.getLength() == 3);
  REQUIRE(list.getEntry(1) == 20);  
  REQUIRE(list.getEntry(2) == 30);
  REQUIRE(list.getEntry(3) == 40);
  // Remove middle
  REQUIRE(list.remove(2) == true);
  REQUIRE(list.getLength() == 2);
  REQUIRE(list.getEntry(1) == 20);  
  REQUIRE(list.getEntry(2) == 40);
  // Remove tail
  REQUIRE(list.remove(2) == true);
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 20);
  // Invalid remove positions
  REQUIRE(list.remove(0) == false);
  REQUIRE(list.remove(2) == false);
  REQUIRE(list.getLength() == 1); // List remains unchanged
}

TEST_CASE("ArrayList: Test Clear Functionality", "[ArrayList]")
{
  ArrayList<int> list;
  list.insert(1, 10);
  list.insert(2, 20);
  list.insert(3, 30);
  REQUIRE(list.getLength() == 3);
  list.clear();
  REQUIRE(list.getLength() == 0);
  REQUIRE(list.isEmpty() == true);
  // Reuse after clear
  REQUIRE(list.insert(1, 40) == true);
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 40);
}

TEST_CASE("ArrayList: Test Copy Constructor and Assignment Operator", "[ArrayList]")
{
  ArrayList<int> list1;
  list1.insert(1, 10);
  list1.insert(2, 20);
  list1.insert(3, 30);
  // Copy constructor
  ArrayList<int> list2(list1);
  REQUIRE(list2.getLength() == 3);
  REQUIRE(list2.getEntry(1) == 10);
  REQUIRE(list2.getEntry(2) == 20);
  REQUIRE(list2.getEntry(3) == 30);
  // Modify original
  list1.setEntry(1, 100);
  REQUIRE(list1.getEntry(1) == 100);
  REQUIRE(list2.getEntry(1) == 10); // copy unaffected 
  // Copy assignment
  ArrayList<int> list3;
  list3 = list1;
  REQUIRE(list3.getLength() == 3);
  REQUIRE(list3.getEntry(1) == 100);
  REQUIRE(list3.getEntry(2) == 20);
  REQUIRE(list3.getEntry(3) == 30);
  // Self-assignment
  list3 = list3;
  REQUIRE(list3.getLength() == 3);
  REQUIRE(list3.getEntry(1) == 100);
}


//TEST CASES FOR LINKED LIST
TEST_CASE("LinkedList: Test Empty List Functions", "[LinkedList]")
{
  LinkedList<int> list;
  REQUIRE(list.isEmpty() == true);
  REQUIRE(list.getLength() == 0); 
  REQUIRE_FALSE(list.remove(1));
  REQUIRE_THROWS_AS(list.getEntry(1), std::out_of_range);
}

TEST_CASE("LinkedList: Test Insert at Various Positions", "[LinkedList]")
{
  LinkedList<int> list;
  // Insert into empty list
  REQUIRE(list.insert(1, 10) == true);
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 10);
  // Insert at head
  REQUIRE(list.insert(1, 20) == true);
  REQUIRE(list.getLength() == 2);
  REQUIRE(list.getEntry(1) == 20);
  REQUIRE(list.getEntry(2) == 10);
  // Insert at middle
  REQUIRE(list.insert(2, 30) == true);
  REQUIRE(list.getLength() == 3);    
  REQUIRE(list.getEntry(1) == 20);
  REQUIRE(list.getEntry(2) == 30);
  REQUIRE(list.getEntry(3) == 10);
  // Insert at end (append)
  REQUIRE(list.insert(4, 40) == true);
  REQUIRE(list.getLength() == 4);   
  REQUIRE(list.getEntry(1) == 20);
  REQUIRE(list.getEntry(2) == 30);
  REQUIRE(list.getEntry(3) == 10);
  REQUIRE(list.getEntry(4) == 40);
  // Invalid insert positions
  REQUIRE(list.insert(0, 50) == false);
  REQUIRE(list.insert(6, 60) == false);
  REQUIRE(list.getLength() == 4); // List remains unchanged
}

TEST_CASE("LinkedList: Test Remove at Various Positions", "[LinkedList]")
{
  LinkedList<int> list;
  list.insert(1, 10);
  list.insert(2, 20);
  list.insert(3, 30);
  list.insert(4, 40);
  // Remove head
  REQUIRE(list.remove(1) == true);
  REQUIRE(list.getLength() == 3);
  REQUIRE(list.getEntry(1) == 20);  
  REQUIRE(list.getEntry(2) == 30);
  REQUIRE(list.getEntry(3) == 40);
  // Remove middle
  REQUIRE(list.remove(2) == true);
  REQUIRE(list.getLength() == 2);
  REQUIRE(list.getEntry(1) == 20);  
  REQUIRE(list.getEntry(2) == 40);
  // Remove tail
  REQUIRE(list.remove(2) == true);
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 20);
  // Invalid remove positions
  REQUIRE(list.remove(0) == false);
  REQUIRE(list.remove(2) == false);
  REQUIRE(list.getLength() == 1); // List remains unchanged
}

TEST_CASE("LinkedList: Test Clear Functionality", "[LinkedList]")
{
  LinkedList<int> list;
  list.insert(1, 10);
  list.insert(2, 20);
  list.insert(3, 30);
  REQUIRE(list.getLength() == 3);
  list.clear();
  REQUIRE(list.getLength() == 0);
  REQUIRE(list.isEmpty() == true);
  // Reuse after clear
  REQUIRE(list.insert(1, 40) == true);
  REQUIRE(list.getLength() == 1);
  REQUIRE(list.getEntry(1) == 40);
}

TEST_CASE("LinkedList: Test Copy Constructor and Assignment Operator", "[LinkedList]")
{
  LinkedList<int> list1;
  list1.insert(1, 10);
  list1.insert(2, 20);
  list1.insert(3, 30);
  // Copy constructor
  LinkedList<int> list2(list1);
  REQUIRE(list2.getLength() == 3);
  REQUIRE(list2.getEntry(1) == 10);
  REQUIRE(list2.getEntry(2) == 20);
  REQUIRE(list2.getEntry(3) == 30);
  // Modify original
  list1.setEntry(1, 100);
  REQUIRE(list1.getEntry(1) == 100);
  REQUIRE(list2.getEntry(1) == 10); // copy unaffected 
  // Copy assignment
  LinkedList<int> list3;
  list3 = list1;
  REQUIRE(list3.getLength() == 3);
  REQUIRE(list3.getEntry(1) == 100);
  REQUIRE(list3.getEntry(2) == 20);
  REQUIRE(list3.getEntry(3) == 30);
  // Self-assignment
  list3 = list3;
  REQUIRE(list3.getLength() == 3);
  REQUIRE(list3.getEntry(1) == 100);
}


