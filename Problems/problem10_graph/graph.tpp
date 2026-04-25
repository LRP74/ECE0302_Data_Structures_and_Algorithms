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

  // Find the indices of start and end in the vertices vector
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
    {
      startIndex = i;
    }

    if (vertices[i] == end)
    {
      endIndex = i;
    }
  }

  if (startIndex != -1 && endIndex != -1 && adjacencyMatrix[startIndex][endIndex] != false)
  {
    return false; // edge already exists
  }

  // If start is not already in the graph, add it
  if (startIndex == -1)
  {
    vertices.push_back(start);
    startIndex = vertices.size() - 1;

    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
      adjacencyMatrix[i].push_back(false); // add new column
    }

    adjacencyMatrix.push_back(std::vector<bool>(vertices.size(), false)); // add new row
  }

  // add end if it is not already in the graph
  if (endIndex == -1)
  {
    vertices.push_back(end);
    endIndex = vertices.size() - 1;

    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
      adjacencyMatrix[i].push_back(false); // add new column
    }

    adjacencyMatrix.push_back(std::vector<bool>(vertices.size(), false)); // add new row
  }

  // dont add edge if it already exists
  if (adjacencyMatrix[startIndex][endIndex] != false)
  {
    return false;
  }

  // add the edge
  adjacencyMatrix[startIndex][endIndex] = true;
  adjacencyMatrix[endIndex][startIndex] = true;

  edgeCount++;

  return true;
}

template <typename ItemType>
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{

  bool startIsolated = true;
  bool endIsolated = true;
  if (start == end)
  {
    return false;
  }

  int startIndex = -1;
  int endIndex = -1;

  // Find the indices of start and end in the vertices vector
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
      startIndex = i;

    if (vertices[i] == end)
      endIndex = i;
  }

  // If either start or end is not in the graph, return false
  if (startIndex == -1 || endIndex == -1)
    return false;

  if (adjacencyMatrix[startIndex][endIndex] == false)
    return false;

  // remove the edge
  adjacencyMatrix[startIndex][endIndex] = false;
  adjacencyMatrix[endIndex][startIndex] = false;

  edgeCount--;

  // Check if start still has any edges
  for (int i = 0; i < adjacencyMatrix.size(); i++)
  {
    if (adjacencyMatrix[startIndex][i] != false)
    {
      startIsolated = false;
      break;
    }
  }
  // Check if end still has any edges
  for (int i = 0; i < adjacencyMatrix.size(); i++)
  {
    if (adjacencyMatrix[endIndex][i] != false)
    {
      endIsolated = false;
      break;
    }
  }
  // Remove larger index first so the other index does not shift
  if (startIsolated && endIsolated)
  {
    if (startIndex > endIndex)
    {
      vertices.erase(vertices.begin() + startIndex);
      adjacencyMatrix.erase(adjacencyMatrix.begin() + startIndex);
      for (int i = 0; i < adjacencyMatrix.size(); i++)
      {
        adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + startIndex);
      }

      vertices.erase(vertices.begin() + endIndex);
      adjacencyMatrix.erase(adjacencyMatrix.begin() + endIndex);
      for (int i = 0; i < adjacencyMatrix.size(); i++)
      {
        adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + endIndex);
      }
    }
    else
    {
      vertices.erase(vertices.begin() + endIndex);
      adjacencyMatrix.erase(adjacencyMatrix.begin() + endIndex);
      for (int i = 0; i < adjacencyMatrix.size(); i++)
      {
        adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + endIndex);
      }

      vertices.erase(vertices.begin() + startIndex);
      adjacencyMatrix.erase(adjacencyMatrix.begin() + startIndex);
      for (int i = 0; i < adjacencyMatrix.size(); i++)
      {
        adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + startIndex);
      }
    }
  }
  else if (startIsolated)
  {
    vertices.erase(vertices.begin() + startIndex);
    adjacencyMatrix.erase(adjacencyMatrix.begin() + startIndex);
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
      adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + startIndex);
    }
  }
  else if (endIsolated)
  {
    vertices.erase(vertices.begin() + endIndex);
    adjacencyMatrix.erase(adjacencyMatrix.begin() + endIndex);
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
      adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + endIndex);
    }
  }
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
      if (adjacencyMatrix[currentIndex][i] != false)
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