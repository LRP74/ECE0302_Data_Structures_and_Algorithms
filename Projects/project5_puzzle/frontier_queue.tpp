#include "frontier_queue.hpp"

// Min-heap index helpers:
//   parent of i      : (i - 1) / 2
//   left  child of i : 2 * i + 1
//   right child of i : 2 * i + 2
template <typename T>
int frontier_queue<T>::getParent(int index)
{
  return (index - 1) / 2;
}

template <typename T>
int frontier_queue<T>::getLeftChild(int index)
{
  return (2 * index) + 1;
}

template <typename T>
int frontier_queue<T>::getRightChild(int index)
{
  return (2 * index) + 2;
}

template <typename T>
State<T> frontier_queue<T>::pop()
{
  State<T> root = queue[0];

  queue[0] = queue.back();
  queue.pop_back();

  int index = 0;

  while (true)
  {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int smallest = index;

    if (left < queue.size() &&
        queue[left].getFCost() < queue[smallest].getFCost())
    {
      smallest = left;
    }

    if (right < queue.size() &&
        queue[right].getFCost() < queue[smallest].getFCost())
    {
      smallest = right;
    }

    if (smallest != index)
    {
      std::swap(queue[index], queue[smallest]);
      index = smallest;
    }
    else
    {
      break;
    }
  }

  return root;
}

template <typename T>
void frontier_queue<T>::push(const T &state, int cost, int heur)
{
  State<T> newState(state, cost, heur);

  queue.push_back(newState);
  int index = queue.size() - 1;

  // watched this video for help https://www.youtube.com/watch?v=UTrr0B4ny9s
  // shape handled by vector and order is handled by the while loop below
  while (index !=0 && queue[index].getFCost() < queue[getParent(index)].getFCost())
  {
    std::swap(queue[index],queue[getParent(index)]);
    index = getParent(index);
  }
  
}

template <typename T>
bool frontier_queue<T>::empty()
{
  if (queue.size() == 0)
  {
    return true;
  }
  
  return false;
}

template <typename T>
bool frontier_queue<T>::contains(const T &state)
{
  for (int i = 0; i < queue.size(); i++)
  {
    if (state == queue[i].getValue())
    {
      return true;
    }
    
  }
  
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &state, int cost)
{
  for (int i = 0; i < queue.size(); i++)
  {
    if (state == queue[i].getValue())
    {
      if (cost < queue[i].getPathCost())
      {
        queue.fcost
      }
      
    }
    
  }
  
}

template <typename T>
int frontier_queue<T>::getCurrentPathCost(const T &state)
{
  // TODO
  return 0;
}