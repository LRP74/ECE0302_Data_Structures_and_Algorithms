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
  //Remove and return the smallest element (which is always at the root, index 0)
  //Restore the heap property after removing it
  State<T> root = queue[0]; // save the root to return later

  queue[0] = queue.back();  // move the last element to the root bc you can't just delete the root without replacing it with something else
  queue.pop_back(); // remove the last element from the vector

  int index = 0;  // start at the root and bubble down the new root element to restore the min-heap property

  while (true)
  {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int smallest = index;   // assume the current index is the smallest

    // compare the current index with its left and right children to find the smallest among them
    if (left < queue.size() &&
        queue[left].getFCost() < queue[smallest].getFCost())
    {
      smallest = left;
    }
    // compare the current smallest with the right child
    if (right < queue.size() &&
        queue[right].getFCost() < queue[smallest].getFCost())
    {
      smallest = right;
    }
    // if the smallest is not the current index, swap and continue bubbling down
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
  // so for bubble up. as you insert nodes you compare to the parent. if the inserted node 
  // is larger than the parent then swap. 
  // then check if you are at the root node. if not check the parent of the swapped node 
  // and continue until you reach the root node
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
    // if the state is in the frontier and the new cost is lower, update the path cost and f-cost of the state
    if (state == queue[i].getValue())
    {
      // if the state is in the frontier and the new cost is lower, update the path cost and f-cost of the state
      if (cost < queue[i].getPathCost())
      {
        queue[i].updatePathCost(cost);
        // after updating the path cost and f-cost of the state, we need to maintain the min-heap property of the frontier
        while (i > 0 && queue[i].getFCost() < queue[getParent(i)].getFCost())
        {
          std::swap(queue[i], queue[getParent(i)]);
          i = getParent(i);
        }
      }

      return;
    }
  }
}

template <typename T>
int frontier_queue<T>::getCurrentPathCost(const T &state)
{
  // TODO
  for (int i = 0; i < queue.size(); i++)
  {
    if (state == queue[i].getValue())
    {
      return queue[i].getPathCost();
    }
    
  }

  return -1;
}