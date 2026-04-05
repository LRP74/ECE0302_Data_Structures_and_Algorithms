#include "queue.hpp"

template <typename T>
bool Queue<T>::isEmpty() const
{
  return internal_list.isEmpty();
}

template <typename T>
void Queue<T>::enqueue(const T &item)
{
  internal_list.insert(internal_list.getLength() + 1, item);
}

template <typename T>
void Queue<T>::dequeue()
{
  if (internal_list.isEmpty())
  {
    throw std::out_of_range("queue is empty");
  }
  
  internal_list.remove(1);
}

template <typename T>
T Queue<T>::peekFront() const
{
  if (internal_list.isEmpty())
  {
    throw std::out_of_range("queue is empty");
  }
  
  return internal_list.getEntry(1);
}