#include "priority_queue.hpp"

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    // TODO
    return sortedListPtr->isEmpty();
}

template <typename T>
void PriorityQueue<T>::add(const T &item)
{
    sortedListPtr->insert(item);
}

template <typename T>
void PriorityQueue<T>::remove()
{
    // TODO, but exception handling should be delegated
    sortedListPtr->removeAt(sortedListPtr->getLength());
}

template <typename T>
T PriorityQueue<T>::peek()
{
    // TODO, but exception handling should be delegated
    return sortedListPtr->getEntry(sortedListPtr->getLength());
}