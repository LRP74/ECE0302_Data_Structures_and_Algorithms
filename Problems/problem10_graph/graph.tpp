#include "graph.hpp"

template <typename ItemType>
Graph<ItemType>::Graph()
{
  // TODO
  edgeCount = 0; // Initialize edge count to zero
}

template <typename ItemType>
int Graph<ItemType>::getNumVertices() const
{
  // TODO
  return vertices.size(); // Return the number of vertices
}

template <typename ItemType>
int Graph<ItemType>::getNumEdges() const
{
  // TODO
  return edgeCount; // Return the number of edges
}

template <typename ItemType>
bool Graph<ItemType>::add(ItemType start, ItemType end)
{
  if (start == end)
  {
    return false; 
  }

  int startIndex = -1;
  int endIndex = -1;

  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
      startIndex = i;

    if (vertices[i] == end)
      endIndex = i;
  }

  // add start to the vertices vector if it does not exist
  if (startIndex == -1)
  {
    vertices.push_back(start);
    startIndex = vertices.size() - 1;
  }

  // add end to the vertices vector if it does not exist
  if (endIndex == -1)
  {
    vertices.push_back(end);
    endIndex = vertices.size() - 1;
  }

  // dont add again if the edge already exists
  if (adjacencyMatrix[startIndex][endIndex] != 0)
    return false;

  // undirected edge, so set both [start][end] and [end][start] to 1
  adjacencyMatrix[startIndex][endIndex] = 1;
  adjacencyMatrix[endIndex][startIndex] = 1;

  edgeCount++;

  return true;
}

template <typename ItemType>
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{
  if (start == end)
  {
    return false;
  }

  int startIndex = -1;
  int endIndex = -1;

  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
      startIndex = i;

    if (vertices[i] == end)
      endIndex = i;
  }

  if (startIndex == -1 || endIndex == -1)
    return false;

  if (adjacencyMatrix[startIndex][endIndex] == 0)
    return false;

  adjacencyMatrix[startIndex][endIndex] = 0;
  adjacencyMatrix[endIndex][startIndex] = 0;

  edgeCount--;


  return true;
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
std::stack<ItemType> s;
  std::set<ItemType> visited;

  s.push(start);
  visited.insert(start);

  while (!s.empty())
  {
    ItemType current = s.top();
    s.pop();

    visit(current);

    // Find the index of the current vertex
    int currentIndex = -1;
    for (int i = 0; i < vertices.size(); i++)
    {
      if (vertices[i] == current)
      {
        currentIndex = i;
      }
    }

    // If current was not found, skip it
    if (currentIndex == -1)
      continue;

    // Look across the row for neighbors
    for (int i = 0; i < vertices.size(); i++)
    {
      if (adjacencyMatrix[currentIndex][i] != 0)
      {
        ItemType neighbor = vertices[i];

        if (!visited.count(neighbor))
        {
          visited.insert(neighbor);
          s.push(neighbor);
        }
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
    for (ItemType neighbor : std::vector<ItemType>{}) // TODO: get the neighbors of current
    {
      if (!visited.count(neighbor)) // count is a method in std::set that returns 1 if the item is in the set, and 0 otherwise
      {
        visited.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
}