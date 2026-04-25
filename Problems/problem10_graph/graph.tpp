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

  // find the indices of start and end in the vertices vector
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

  // if the graph is not empty, do not add two brand new vertices
  // because that would make the graph disconnected
  if (!vertices.empty() && startIndex == -1 && endIndex == -1)
  {
    return false;
  }

  // if both vertices already exist and the edge already exists, don't add it
  if (startIndex != -1 && endIndex != -1 && adjacencyMatrix[startIndex][endIndex] == true)
  {
    return false;
  }

  // add start if it is not already in the graph
  if (startIndex == -1)
  {
    vertices.push_back(start);
    startIndex = vertices.size() - 1;

    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
      adjacencyMatrix[i].push_back(false);
    }

    adjacencyMatrix.push_back(std::vector<bool>(vertices.size(), false));
  }

  // add end if it is not already in the graph
  if (endIndex == -1)
  {
    vertices.push_back(end);
    endIndex = vertices.size() - 1;

    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
      adjacencyMatrix[i].push_back(false);
    }

    adjacencyMatrix.push_back(std::vector<bool>(vertices.size(), false));
  }

  // add the edge both ways because this is an undirected graph
  adjacencyMatrix[startIndex][endIndex] = true;
  adjacencyMatrix[endIndex][startIndex] = true;

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

  // find start and end
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
      startIndex = i;

    if (vertices[i] == end)
      endIndex = i;
  }

  // if either vertex does not exist
  if (startIndex == -1 || endIndex == -1)
  {
    return false;
  }

  // if edge does not exist
  if (adjacencyMatrix[startIndex][endIndex] == false)
  {
    return false;
  }

  // temporarily remove the edge
  adjacencyMatrix[startIndex][endIndex] = false;
  adjacencyMatrix[endIndex][startIndex] = false;

  // check if start and end are isolated
  bool startIsolated = true;
  bool endIsolated = true;

  for (int i = 0; i < adjacencyMatrix.size(); i++)
  {
    if (adjacencyMatrix[startIndex][i] == true)
      startIsolated = false;

    if (adjacencyMatrix[endIndex][i] == true)
      endIsolated = false;
  }

  // if neither vertex is isolated, make sure the graph is still connected
  if (!startIsolated && !endIsolated)
  {
    std::queue<int> q;
    std::set<int> visited;

    q.push(startIndex);
    visited.insert(startIndex);

    while (!q.empty())
    {
      int current = q.front();
      q.pop();

      for (int i = 0; i < adjacencyMatrix.size(); i++)
      {
        if (adjacencyMatrix[current][i] == true && !visited.count(i))
        {
          visited.insert(i);
          q.push(i);
        }
      }
    }

    // if not all vertices were visited, removing the edge disconnected the graph
    if (visited.size() != vertices.size())
    {
      adjacencyMatrix[startIndex][endIndex] = true;
      adjacencyMatrix[endIndex][startIndex] = true;
      return false;
    }
  }

  edgeCount--;

  // remove isolated vertices, bigger index first
  if (startIsolated && endIsolated)
  {
    int first = startIndex;
    int second = endIndex;

    if (first < second)
      std::swap(first, second);

    vertices.erase(vertices.begin() + first);
    adjacencyMatrix.erase(adjacencyMatrix.begin() + first);
    for (int i = 0; i < adjacencyMatrix.size(); i++)
      adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + first);

    vertices.erase(vertices.begin() + second);
    adjacencyMatrix.erase(adjacencyMatrix.begin() + second);
    for (int i = 0; i < adjacencyMatrix.size(); i++)
      adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + second);
  }
  else if (startIsolated)
  {
    vertices.erase(vertices.begin() + startIndex);
    adjacencyMatrix.erase(adjacencyMatrix.begin() + startIndex);
    for (int i = 0; i < adjacencyMatrix.size(); i++)
      adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + startIndex);
  }
  else if (endIsolated)
  {
    vertices.erase(vertices.begin() + endIndex);
    adjacencyMatrix.erase(adjacencyMatrix.begin() + endIndex);
    for (int i = 0; i < adjacencyMatrix.size(); i++)
      adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + endIndex);
  }

  return true;
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  // find the index of the start vertex
  int startIndex = -1;
  // find the index of start in the vertices vector
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
    {
      startIndex = i;
      break;
    }
  }
  // if start vertex does not exist, do nothing
  if (startIndex == -1)
    return;

  std::stack<ItemType> s;
  std::set<ItemType> visited;

  s.push(start);
  
  // standard DFS loop
  while (!s.empty())
  {
    ItemType current = s.top();
    s.pop();

    // skip if already visited
    if (visited.count(current))
      continue;

    visit(current);
    visited.insert(current);

    // find the index of current in the vertices vector
    int currentIndex = -1;
    for (int i = 0; i < vertices.size(); i++)
    {
      if (vertices[i] == current)
      {
        currentIndex = i;
        break;
      }
    }

    if (currentIndex == -1)
      continue;

    // push neighbors onto the stack in reverse order so that they are visited in the correct order
    for (int i = vertices.size() - 1; i >= 0; i--)
    {
      if (adjacencyMatrix[currentIndex][i])
      {
        ItemType neighbor = vertices[i];

        if (!visited.count(neighbor))
        {
          s.push(neighbor);
        }
      }
    }
  }
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  // find the index of the start vertex
  int startIndex = -1;
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i] == start)
    {
      startIndex = i;
      break;
    }
  }
  if (startIndex == -1)
    return;

  std::queue<ItemType> q;
  std::set<ItemType> visited;

  q.push(start);
  visited.insert(start);

    // standard BFS loop
  while (!q.empty())
  {
    ItemType current = q.front();
    q.pop();
    visit(current);

    int currentIndex = -1;
    // find the index of current in the vertices vector
    for (int i = 0; i < vertices.size(); i++)
    {
      if (vertices[i] == current)
      {
        currentIndex = i;
        break;
      }
    }

    // if current vertex does not exist, skip
    if (currentIndex == -1)
      continue;

    std::vector<ItemType> neighbors;
    //  find neighbors of current vertex and add them to the neighbors vector
    for (int j = 0; j < vertices.size(); j++)
    {
      // if there is an edge and the neighbor has not been visited, add it to the neighbors vector
      if (adjacencyMatrix[currentIndex][j] && !visited.count(vertices[j]))
      {
        neighbors.push_back(vertices[j]);
      }
    }

    // ai helped me with this fix
    // std::sort is used to ensure that neighbors are visited in a consistent order
    // this is important for testing, since the order of visiting neighbors can affect the output of the traversal
    std::sort(neighbors.begin(), neighbors.end());

    // add neighbors to the queue and mark them as visited
    for (ItemType &neighbor : neighbors)
    {
      visited.insert(neighbor);
      q.push(neighbor);
    }
  }
}
