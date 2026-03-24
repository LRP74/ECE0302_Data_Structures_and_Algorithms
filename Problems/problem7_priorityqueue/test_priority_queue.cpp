#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

/* Provided test cases */
TEST_CASE("Priority: Testing Sorted List", "[sorted list]")
{
  SortedList<int> sort;

  REQUIRE(sort.isEmpty());
  REQUIRE(sort.getLength() == 0);

  sort.insert(1);
  REQUIRE_FALSE(sort.isEmpty());
  REQUIRE(sort.getLength() == 1);
  sort.insert(2);
  REQUIRE(sort.getLength() == 2);
  sort.insert(8);
  REQUIRE(sort.getLength() == 3);
  sort.insert(6);
  REQUIRE(sort.getLength() == 4);
  sort.insert(9);
  REQUIRE(sort.getLength() == 5);
  sort.insert(0);
  REQUIRE(sort.getLength() == 6);

  REQUIRE(sort.getEntry(1) == 0);
  REQUIRE(sort.getPosition(0) == 1);
  REQUIRE(sort.getEntry(2) == 1);
  REQUIRE(sort.getPosition(1) == 2);
  REQUIRE(sort.getEntry(3) == 2);
  REQUIRE(sort.getPosition(2) == 3);
  REQUIRE(sort.getEntry(4) == 6);
  REQUIRE(sort.getPosition(6) == 4);
  REQUIRE(sort.getEntry(5) == 8);
  REQUIRE(sort.getPosition(8) == 5);
  REQUIRE(sort.getEntry(6) == 9);
  REQUIRE(sort.getPosition(9) == 6);

  sort.remove(0);
  REQUIRE(sort.getEntry(1) == 1);
  REQUIRE(sort.getLength() == 5);

  sort.remove(1);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 4);

  sort.remove(9);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 3);

  sort.removeAt(2);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 2);

  sort.removeAt(1);
  REQUIRE(sort.getEntry(1) == 8);
  REQUIRE(sort.getLength() == 1);

  sort.removeAt(1);
  REQUIRE(sort.getLength() == 0);
  REQUIRE(sort.isEmpty());
}

TEST_CASE("Priority: Testing Priority Queue Add/isEmpty/peek/remove", "[priority queue]")
{
  PriorityQueue<int> pq;

  REQUIRE(pq.isEmpty());

  pq.add(3);
  REQUIRE_FALSE(pq.isEmpty());

  pq.add(1);
  pq.add(5);
  pq.add(2);
  REQUIRE(pq.peek() == 5);

  pq.remove();
  REQUIRE(pq.peek() == 3);

  pq.remove();
  REQUIRE(pq.peek() == 2);
}

/** Write your own test cases here */

// Test isEmpty returns true on empty queue, false after add
TEST_CASE("Test isEmpty returns true on empty queue, false after add", "[priority queue]")
{
  PriorityQueue<int> pq;

  REQUIRE(pq.isEmpty());
  pq.add(7);
  REQUIRE_FALSE(pq.isEmpty());
  pq.remove();
  REQUIRE(pq.isEmpty());
}

// Test add maintains ascending sorted order in underlying SortedList
TEST_CASE("Test add maintains ascending sorted order in underlying SortedList", "[priority queue]")
{
  PriorityQueue<int> pq;

  pq.add(7);
  pq.add(5);
  pq.add(4);
  pq.add(72);
  pq.add(79);
  pq.add(1);
  pq.add(13);

  REQUIRE(pq.peek() == 79);
  pq.remove();
  REQUIRE(pq.peek() == 72);
  pq.remove();
  REQUIRE(pq.peek() == 13);
  pq.remove();
  REQUIRE(pq.peek() == 7);
  pq.remove();
  REQUIRE(pq.peek() == 5);
  pq.remove();
  REQUIRE(pq.peek() == 4);
  pq.remove();
  REQUIRE(pq.peek() == 1);
}

// Test peek returns highest priority item (largest value)
TEST_CASE("Test peek returns highest priority item (largest value)", "[priority queue]")
{
  PriorityQueue<int> pq;

  pq.add(517);
  pq.add(52);
  pq.add(432);
  pq.add(72);
  pq.add(79);
  pq.add(100);
  pq.add(13);
  REQUIRE(pq.peek() == 517);
}

// Test peek throws std::out_of_range on empty queue
TEST_CASE("Test peek throws std::out_of_range on empty queue", "[priority queue]")
{
  PriorityQueue<int> pq;

  REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
}

// Test remove deletes highest priority item
TEST_CASE("Test remove deletes highest priority item", "[priority queue]")
{
  PriorityQueue<int> pq;

  pq.add(517);
  pq.add(52);
  pq.add(432);
  pq.add(72);
  pq.add(79);
  pq.add(100);
  pq.add(13);
  REQUIRE(pq.peek() == 517);
  pq.remove();  //remove last item
  REQUIRE(pq.peek() == 432);
}


// Test with double data type
TEST_CASE("Test with double data type", "[priority queue]")
{
  PriorityQueue<double> pq;
  pq.add(7.35);
  pq.add(5.222);
  pq.add(4.89);
  pq.add(72.1);
  pq.add(79.005);
  pq.add(1.96);
  pq.add(13.452);

  REQUIRE(pq.peek() == 79.005);
  pq.remove();
  REQUIRE(pq.peek() == 72.1);
  pq.remove();
  REQUIRE(pq.peek() == 13.452);
  pq.remove();
  REQUIRE(pq.peek() == 7.35);
  pq.remove();
  REQUIRE(pq.peek() == 5.222);
  pq.remove();
  REQUIRE(pq.peek() == 4.89);
  pq.remove();
  REQUIRE(pq.peek() == 1.96);
}

// Test with char data type
TEST_CASE("Test with char data type", "[priority queue]")
{
  PriorityQueue<char> pq;

  pq.add('a');
  pq.add('j');
  pq.add('i');
  pq.add('q');
  pq.add('l');
  pq.add('b');
  pq.add('s');

  REQUIRE(pq.peek() == 's');
  pq.remove();
  REQUIRE(pq.peek() == 'q');
  pq.remove();
  REQUIRE(pq.peek() == 'l');
  pq.remove();
  REQUIRE(pq.peek() == 'j');
  pq.remove();
  REQUIRE(pq.peek() == 'i');
  pq.remove();
  REQUIRE(pq.peek() == 'b');
  pq.remove();
  REQUIRE(pq.peek() == 'a');
}

//overload > and == to compare priority queues
struct TestItem
{
  int priority;

  bool operator>(const TestItem& other) const
  {
    return priority > other.priority;
  }

  bool operator==(const TestItem& other) const
  {
    return priority == other.priority;
  }
};


// Test with a custom struct that overloads operator> and operator==
//Test your priority queue with custom data types that you have overloaded operators for comparison.
TEST_CASE("Test with a custom struct that overloads operator> and operator==", "[priority queue]")
{

}