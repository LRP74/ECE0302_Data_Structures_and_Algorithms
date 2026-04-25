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

