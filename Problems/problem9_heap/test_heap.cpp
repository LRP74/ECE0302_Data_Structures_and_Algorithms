#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ArrayMaxHeap.hpp"

/* Provided test cases */
TEST_CASE("Heap: test construct from array", "[construct]")
{
   int array[] = {80, 70, 60, 50, 40, 30, 20, 10};
   ArrayMaxHeap<int> heap(array, 8);
   REQUIRE(heap.getNumberOfNodes() == 8);
   REQUIRE(heap.getHeight() == 4);
   REQUIRE(heap.isEmpty() == false);
   heap.clear();
   REQUIRE(heap.getNumberOfNodes() == 0);
   REQUIRE(heap.getHeight() == 0);
   REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("Heap: test heap sort", "[sort]")
{
   int array[] = {15, 5, 20, 10, 30};
   ArrayMaxHeap<int> heap(array, 5);
   heap.heapSort(array, 5);
   REQUIRE(array[0] == 30);
   REQUIRE(array[1] == 20);
   REQUIRE(array[2] == 15);
   REQUIRE(array[3] == 10);
   REQUIRE(array[4] == 5);
}

/* Additional test cases */
// peekTop tests
// 1. create a heap with a few elements, peek should return the largest
TEST_CASE("1. create a heap with a few elements, peek should return the largest", "[peekTop]")
{
   int array[] = {15, 5, 20, 10, 30};
   ArrayMaxHeap<int> heap(array, 5);
   REQUIRE(heap.peekTop() == 30);
}
// 2. create an empty heap, peek should throw std::out_of_range
TEST_CASE("create an empty heap, peek should throw std::out_of_range", "[peekTop]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE_THROWS_AS(heap.peekTop(), std::out_of_range);
}

// add tests
// 3. add one element to an empty heap, peek should return that element
TEST_CASE("add one element to an empty heap, peek should return that element", "[add]")
{
   ArrayMaxHeap<int> heap;
   heap.add(42);
   REQUIRE(heap.peekTop() == 42);
}
// 4. add multiple elements out of order, peek should always return the largest
TEST_CASE("add multiple elements out of order, peek should always return the largest", "[add]")
{
   ArrayMaxHeap<int> heap;
   heap.add(10);
   REQUIRE(heap.peekTop() == 10);
   heap.add(20);
   REQUIRE(heap.peekTop() == 20);
   heap.add(5);
   REQUIRE(heap.peekTop() == 20);
   heap.add(30);
   REQUIRE(heap.peekTop() == 30);
}
// 5. fill heap to capacity (63 elements), adding one more should return false
TEST_CASE("fill heap to capacity (63 elements), adding one more should return false", "[add]")
{
   ArrayMaxHeap<int> heap;
   for (int i = 0; i < 63; i++)
   {
      REQUIRE(heap.add(i) == true);
   }
   REQUIRE(heap.add(64) == false); // should return false when trying to add 64th element
}
// 6. add a duplicate value, should return false
TEST_CASE("add a duplicate value, should return false", "[add]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.add(42) == true);
   REQUIRE(heap.add(42) == false); // should return false when trying to add duplicate
}

// remove tests
// 7. remove from empty heap should return false
TEST_CASE("remove from empty heap should return false", "[remove]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.remove() == false);
}
// 8. remove from heap with multiple elements, peek after should return new max
TEST_CASE("remove from heap with multiple elements, peek after should return new max", "[remove]")
{
   ArrayMaxHeap<int> heap;
   heap.add(10);
   heap.add(20);
   heap.add(5);
   heap.add(30);
   REQUIRE(heap.peekTop() == 30);
   REQUIRE(heap.remove() == true); // remove 30
   REQUIRE(heap.peekTop() == 20); // new max should be 20
}
// 9. keep removing until empty, each peek should return correct max, last remove leaves heap empty
TEST_CASE("keep removing until empty, each peek should return correct max, last remove leaves heap empty", "[remove]")
{
   ArrayMaxHeap<int> heap;
   heap.add(10);
   heap.add(20);
   heap.add(5);
   heap.add(30);
   REQUIRE(heap.peekTop() == 30);
   REQUIRE(heap.remove() == true); // remove 30
   REQUIRE(heap.peekTop() == 20);
   REQUIRE(heap.remove() == true); // remove 20
   REQUIRE(heap.peekTop() == 10);
   REQUIRE(heap.remove() == true); // remove 10
   REQUIRE(heap.peekTop() == 5);
   REQUIRE(heap.remove() == true); // remove 5
   REQUIRE(heap.isEmpty() == true); // heap should now be empty
}

// heapSort tests
// 10. sort an unsorted array, verify first element is largest and last is smallest
TEST_CASE("sort an unsorted array, verify first element is largest and last is smallest", "[heapSort]")
{
   int array[] = {15, 5, 20, 10, 30};
   ArrayMaxHeap<int> heap;
   heap.heapSort(array, 5);
   REQUIRE(array[0] == 30); // largest should be first
   REQUIRE(array[4] == 5);  // smallest should be last
}

// 11. array with duplicates should throw std::invalid_argument
TEST_CASE("array with duplicates should throw std::invalid_argument", "[heapSort]")
{
   int array[] = {15, 5, 20, 10, 15}; // duplicate 15
   ArrayMaxHeap<int> heap;
   REQUIRE_THROWS_AS(heap.heapSort(array, 5), std::invalid_argument);
}
// 12. array larger than 63 elements should throw std::invalid_argument
TEST_CASE("array larger than 63 elements should throw std::invalid_argument", "[heapSort]")
{
   int array[64]; // 64 elements, exceeds capacity
   for (int i = 0; i < 64; i++)
   {
      array[i] = i;
   }
   ArrayMaxHeap<int> heap;
   REQUIRE_THROWS_AS(heap.heapSort(array, 64), std::invalid_argument);
}