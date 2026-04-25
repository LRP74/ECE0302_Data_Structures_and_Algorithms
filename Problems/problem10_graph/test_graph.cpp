#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "graph.hpp"

TEST_CASE("Test Construction", "[construction]")
{
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Test Add", "[add]")
{
  Graph<int> g;
  REQUIRE(g.add(1, 2) == true);
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);
  
  REQUIRE(g.add(1, 3) == true);
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 2);
  
  REQUIRE(g.add(2, 3) == true);
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 3);
  
  // Adding an existing edge should return false and not change the graph
  REQUIRE(g.add(1, 2) == false);
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 3);
  
  // Adding an edge from a vertex to itself should return false and not change the graph
  REQUIRE(g.add(1, 1) == false);
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 3);
}

TEST_CASE("Test Remove", "[remove]")
{
  Graph<int> g;
  g.add(1, 2);
  g.add(1, 3);
  g.add(2, 3);
  
  REQUIRE(g.remove(1, 2) == true);
  REQUIRE(g.getNumVertices() == 3); // vertices should not be removed
  REQUIRE(g.getNumEdges() == 2);
  
  REQUIRE(g.remove(1, 3) == true);
  REQUIRE(g.getNumVertices() == 3); // vertices should not be removed
  REQUIRE(g.getNumEdges() == 1);
  
  REQUIRE(g.remove(2, 3) == true);
  REQUIRE(g.getNumVertices() == 3); // vertices should not be removed
  REQUIRE(g.getNumEdges() == 0);
  
  // Removing a non-existent edge should return false and not change the graph
  REQUIRE(g.remove(1, 2) == false);
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 0);
  
  // Removing an edge from a vertex to itself should return false and not change the graph
  REQUIRE(g.remove(1, 1) == false);
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Test Depth-First Traversal", "[dfs]")
{
  Graph<int> g;
  g.add(1, 2);
  g.add(1, 3);
  g.add(2, 3);
  
  std::vector<int> visited;
  g.depthFirstTraversal(1, [&](int &vertex) { visited.push_back(vertex); });
  
  // the visited vertices should be 1, 2, and 3 in some order
  REQUIRE(visited.size() == 3);
  REQUIRE(std::find(visited.begin(), visited.end(), 1) != visited.end());
  REQUIRE(std::find(visited.begin(), visited.end(), 2) != visited.end());
  REQUIRE(std::find(visited.begin(), visited.end(), 3) != visited.end());
}

