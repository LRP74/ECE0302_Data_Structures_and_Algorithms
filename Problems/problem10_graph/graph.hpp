#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "abstract_graph.hpp"
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <algorithm> // for std::sort

template <typename ItemType>
class Graph : public AbstractGraph<ItemType>
{
private:
    // TODO: Add your private members here
    // Using an adjacency list or adjacency matrix

    // For adjacency matrix, you may use a 2D array, or a vector of vectors etc and an array of vertices to map the indices to vertices
    // For adjacency list, you can use a std::map to map vertices to the set of adjacent vertices
    // Refer to std::vector, std::set, std::map, std::unordered_map etc
    /*
    *** Add private data members to graph.hpp and implement the constructor in graph.tpp

Represent the graph as an adjacency list using a std::map<ItemType, std::set<ItemType>> mapping each vertex to its set of neighbors. Track edge count in a separate integer member.
The default constructor should initialize an empty graph (zero vertices, zero edges). No other initialization is required.
    */
    std::vector<std::vector<bool>> adjacencyMatrix; // a 2D vector of bools to represent the adjacency matrix
    std::vector<ItemType> vertices; // a vector to store the vertices in the graph
    int edgeCount;


public:
    Graph();
    int getNumVertices() const;
    int getNumEdges() const;
    bool add(ItemType start, ItemType end);
    bool remove(ItemType start, ItemType end);
    void depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit);
    void breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit);
};

#include "graph.tpp"

#endif