#include "graph.hpp"

template <typename ItemType>
Graph<ItemType>::Graph()
{
  edgeCount = 0;
}

template <typename ItemType>
int Graph<ItemType>::getNumVertices() const
{
  // TODO
  // getNumVertices should return the number of keys in your adjacency map.
  return adjacencyList.size();
}

template <typename ItemType>
int Graph<ItemType>::getNumEdges() const
{
  // TODO
  return edgeCount;
}

template <typename ItemType>
bool Graph<ItemType>::add(ItemType start, ItemType end)
{
  // TODO
  if (adjacencyList.find(start) == adjacencyList.end()) {
    // If either vertex does not exist, add it to the graph
    adjacencyList[start]; // This will create an entry for start if it doesn't exist
    adjacencyList[end];   // This will create an entry for end if it doesn't exist
  }
  // Check if the edge already exists or if start and end are the same
  if (start == end || adjacencyList[start].count(end) > 0) {
    return false; // Edge already exists or start and end are the same
  }
  // Add the edge (undirected)
  adjacencyList[start].insert(end);
  adjacencyList[end].insert(start);
  
  return true; // Placeholder
}

template <typename ItemType>
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{
  // TODO
    // Check if the edge exists or if start and end are the same
  if (start == end || adjacencyList.find(start) == adjacencyList.end()) {
    return false; // Edge does not exist or start and end are the same
  }
  // Remove the edge (undirected)
  adjacencyList[start].erase(end);
  adjacencyList[end].erase(start);
  edgeCount--; // Decrement edge count
  // Remove vertices if they have no other edges
  if (adjacencyList[start].empty()) {
    adjacencyList.erase(start);
  }
  if (adjacencyList[end].empty()) {
    adjacencyList.erase(end);
  }
  
  return true; // Placeholder
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  // TODO, use a stack and similar code structure to breadthFirstTraversal
  std::stack<ItemType> s;
  std::set<ItemType> visited; // set is a container that stores unique items in sorted order, and provides fast lookup
  ItemType currentNode = s.top();

  s.push(start);  //push onto the stack where you are starting known as "source node"
  visited.insert(start);
  while (!s.empty())  //while there is something on the stack, that means there is something we want to pop off
  {    
    s.pop(); // start by popping the start
    // push onto the stack its connections (neighbors) that have not been visited yet, and mark them as visited
    visit(currentNode);
    for (ItemType neighbor : adjacencyList[currentNode]) 
    {
      if (!visited.count(neighbor)) // count is a method in std::set that returns 1 if the item is in the set, and 0 otherwise
      {
        visited.insert(neighbor);
        s.push(neighbor); // push the neighbor onto the stack

  }

}
  }
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  std::queue<ItemType> q;
  std::set<ItemType> visited; // set is a container that stores unique items in sorted order, and provides fast lookup

  q.push(start);  
  visited.insert(start);
  while (!q.empty())
  {
    ItemType current = q.front();
    q.pop();
    visit(current);
    for (ItemType neighbor : adjacencyList[current]) // TODO: get the neighbors of current
    {
      if (!visited.count(neighbor)) // count is a method in std::set that returns 1 if the item is in the set, and 0 otherwise
      {
        visited.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
}