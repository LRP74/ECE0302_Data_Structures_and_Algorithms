/** @file test_linked_stack.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LinkedStack.hpp"
#include "StackInterface.hpp"
#include <vector>
#include <stack>

TEST_CASE("Testing the Linked-Based Stack with push", "[linked stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   REQUIRE(stackPtr1->isEmpty() == true);

   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      REQUIRE(stackPtr1->push(items1[i]));
   }

   REQUIRE(stackPtr1->isEmpty() == false);
   // REQUIRE(stackPtr1->push(items1[10]) == false); // stack is never full

   delete stackPtr1;
}

TEST_CASE("Testing the Linked-Based Stack with pop", "[linked stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      stackPtr1->push(items1[i]);
   }

   for (int i = 9; i >= 0; i--)
   {
      REQUIRE(stackPtr1->pop()); // Test pop after pushing
   }
   REQUIRE(stackPtr1->isEmpty() == true);
   REQUIRE(stackPtr1->pop() == false); // nothing to pop!
   delete stackPtr1;
}

TEST_CASE("Testing the Linked-Based Stack with peek", "[linked stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      stackPtr1->push(items1[i]);
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after pushing
   }

   for (int i = 9; i >= 0; i--)
   {
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after popping
      stackPtr1->pop();
   }
   REQUIRE(stackPtr1->isEmpty() == true);
   REQUIRE_THROWS_AS(stackPtr1->peek(), std::out_of_range); // nothing to peek!
   delete stackPtr1;
}

TEST_CASE("Testing the Linked-Based Stack with exceptions", "[linked stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   REQUIRE_THROWS_AS(stackPtr1->peek(), std::out_of_range); // nothing to peek!
   REQUIRE_FALSE(stackPtr1->pop());                         // nothing to pop!
   delete stackPtr1;
}

// There are other ways to implement a stack. For example, using a vector or a list.
// 1. dynamically-sized array to hold stack data
// 2. std::vector with push_back and pop_back, and back
// 3. simply std::stack with push, pop, and top

TEST_CASE("Testing other stack implementation 3 and 4", "[stack]")
{
   // Method 2
   std::vector<std::string> stack3;
   stack3.push_back("zero");
   stack3.push_back("one");
   REQUIRE(stack3.back() == "one");
   stack3.pop_back();
   REQUIRE(stack3.back() == "zero");
   stack3.pop_back();
   REQUIRE(stack3.empty() == true);

   // Method 3
   std::stack<std::string> stack4;
   stack4.push("zero");
   stack4.push("one");
   REQUIRE(stack4.top() == "one");
   stack4.pop();
   REQUIRE(stack4.top() == "zero");
   stack4.pop();
   REQUIRE(stack4.empty() == true);
}