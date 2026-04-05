#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include "abstract_queue.hpp"
#include <memory>

template <typename T>
class Queue : public AbstractQueue<T>
{
public:
  bool isEmpty() const;

  void enqueue(const T &item);

  void dequeue();

  T peekFront() const;

private:
  // TODO
  // Use ADT list as the internal data structure to implement the queue
  List<T> internal_list;
};

#include "queue.tpp"

#endif