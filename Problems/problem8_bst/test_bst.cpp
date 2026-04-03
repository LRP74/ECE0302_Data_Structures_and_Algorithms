#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "binary_search_tree.hpp"

using key = int;
using TreeType = BinarySearchTree<key, int>;

/* Provided test cases */
TEST_CASE("BST: Test Insert", "[insert]")
{
    TreeType bst1;
    REQUIRE(bst1.isEmpty());

    bst1.insert(10, 10);
    REQUIRE_FALSE(bst1.isEmpty());
}

TEST_CASE("BST: Test Duplicate Insert", "[duplicate insert]")
{
    TreeType bst1;
    REQUIRE(bst1.insert(12, 12));
    REQUIRE_FALSE(bst1.insert(12, 12));
}

TEST_CASE("BST: Test Remove With No Children", "[remove]")
{
    TreeType bst1;
    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));

    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));

    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));

    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("BST: Test Destroy after Copy Assign", "[copy assign]")
{
    TreeType bst1;
    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    TreeType bst2;
    bst2 = bst1;

    bst1.destroy();
    REQUIRE(bst1.isEmpty());
    REQUIRE_FALSE(bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(51, item));
}
/* Write your own test cases here */

TEST_CASE("BST: Test Remove With one child", "[remove]")
{
    TreeType bst1;
    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(3, 3);
    int item;
    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(3, item));
    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(3, item));
    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(3, item));
    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(3, item));
    bst1.remove(3);
    REQUIRE_FALSE(bst1.retrieve(3, item));
    REQUIRE(bst1.isEmpty());
       
}
TEST_CASE("BST: Test remove with one child other branch", "[remove]")
{
    TreeType bst1;
    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(7, 7);
    int item;
    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(7);
    REQUIRE_FALSE(bst1.retrieve(7, item));
    REQUIRE(bst1.isEmpty());
       
}

TEST_CASE("BST: Test Remove With two children", "[remove]")
{
    TreeType bst1;
    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(3, 3);
    bst1.insert(7, 7);
    int item;
    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(3, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(3, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(3, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(3, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(3);
    REQUIRE_FALSE(bst1.retrieve(3, item));
    REQUIRE(bst1.retrieve(7, item));
    bst1.remove(7);
    REQUIRE_FALSE(bst1.retrieve(7, item));
    REQUIRE(bst1.isEmpty());
}

TEST_CASE("BST: Test tree sort", "[tree sort]")
{
    TreeType bst1;
    int arr[5] = {10, 5, 15, 3, 7};
    bst1.treeSort(arr, 5);
    REQUIRE(arr[0] == 3);
    REQUIRE(arr[1] == 5);
    REQUIRE(arr[2] == 7);
    REQUIRE(arr[3] == 10);
    REQUIRE(arr[4] == 15);
}