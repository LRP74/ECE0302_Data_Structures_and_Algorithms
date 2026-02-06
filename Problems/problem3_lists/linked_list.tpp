#include "linked_list.hpp"
#include <stdexcept> //used for exceptions

template <typename T>
LinkedList<T>::LinkedList()
{
  // TODO, default constructor
  headPtr = nullptr;  // Initialize head pointer to null
  itemCount = 0;  // Initialize item count to 0
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  // TODO, destructor
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  // TODO, copy constructor
  // create and initialize an empty list, then copy each item from x
  headPtr = nullptr;
  itemCount = 0;
  Node<T>* curPtr = x.headPtr;
  for (int i = 1; i <= x.itemCount; i++)
  {
    insert(i, curPtr->getItem());
    curPtr = curPtr->getNext();
  }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  // TODO, copy assignment
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  // TODO, swap helper function for copy assignment
  // swap the member variables of this and x
  Node<T>* tempHead = headPtr;
  int tempCount = itemCount;
  headPtr = x.headPtr;
  itemCount = x.itemCount;
  x.headPtr = tempHead;
  x.itemCount = tempCount;
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  // TODO
  return (itemCount == 0);
}

template <typename T>
int LinkedList<T>::getLength() const noexcept
{
  // TODO
  return itemCount;
}

template <typename T>
bool LinkedList<T>::insert(int position, const T &item)
{
  // TODO
  bool isAbleToInsert = ((position >=1) && (position <= itemCount +1)); // allow insert at position n+1 (the end)
  // insert at position 1 (the beginning)
  if (isAbleToInsert && (position == 1))
  {
    Node<T>* newNodePtr = new Node<T>();
    newNodePtr->setItem(item);
    newNodePtr->setNext(headPtr); // New node points to chain
    headPtr = newNodePtr;   // New node is now first node      
    itemCount++;
    return true;
  }
  // insert at position > 1
  else if (isAbleToInsert && position > 1)
  {
    Node<T>* prevNodePtr = getNodeAt(position - 1);
    Node<T>* newNodePtr = new Node<T>();
    newNodePtr->setItem(item);
    newNodePtr->setNext(prevNodePtr->getNext());
    prevNodePtr->setNext(newNodePtr);
    itemCount++;
    return true;
  }

  return false;
}

template <typename T>
bool LinkedList<T>::remove(int position)
{
  // TODO
  bool isAbleToRemove = ((position >=1) && (position <= itemCount));
  // remove at position 1 (the beginning)
  if (isAbleToRemove && (position == 1))
  {
    Node<T>* nodeToDeletePtr = headPtr; // node to delete
    headPtr = headPtr->getNext(); // bypass the node to delete
    delete nodeToDeletePtr; // free memory of the node to delete
    itemCount--;  
    return true;
  }
  // remove at position > 1
  else if (isAbleToRemove && position > 1)
  {
    Node<T>* prevNodePtr = getNodeAt(position - 1); // node before the one to delete
    Node<T>* nodeToDeletePtr = prevNodePtr->getNext();  // node to delete
    prevNodePtr->setNext(nodeToDeletePtr->getNext()); // bypass the node to delete
    delete nodeToDeletePtr; // free memory of the node to delete
    itemCount--;
    return true;
  }
  return false;
}

template <typename T>
void LinkedList<T>::clear()
{
  // TODO
  while (!isEmpty())
  {
    remove(1);  // always remove the first node until the list is empty
  }
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T LinkedList<T>::getEntry(int position) const
{
  // TODO
  if ((position >= 1) && (position <= itemCount))
  {
    Node<T>* nodePtr = getNodeAt(position);
    return nodePtr->getItem();
  }
  else
  {
    throw std::out_of_range("invalid position.");
  }
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void LinkedList<T>::setEntry(int position, const T &newValue)
{
  // TODO
  if ((position >= 1) && (position <= itemCount))
  {
    Node<T>* nodePtr = getNodeAt(position); // get pointer to node at the given position
    nodePtr->setItem(newValue);
  }
  else
  {
    throw std::out_of_range("invalid position.");
  }
}

template <typename T>
inline Node<T>* LinkedList<T>::getNodeAt(int position) const
{
  // TODO
  // returns a pointer to the node at the given position
  // assumes position is valid
  if ((position >= 1) && (position <= itemCount))
  {
    Node<T>* curPtr = headPtr;  // start at the first node
    for (int skip = 1; skip < position; skip++) // move to the desired position [had ai help with this section the skip parameter looks weird]
    {
      curPtr = curPtr->getNext();;  // advance to next node
    }
    return curPtr;  // return pointer to node at position
  }
  
  return nullptr;
}
