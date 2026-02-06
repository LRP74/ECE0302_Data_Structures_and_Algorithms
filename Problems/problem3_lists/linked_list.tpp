#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
    headPtr = nullptr;
    itemCount = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
   clear(); // Once all stub methods of copy constructor/insert/remove are complete, using clear() to free memory is enough.
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  headPtr = nullptr;
  itemCount = 0;
  Node<T> *current = x.headPtr;
  while (current != nullptr)
  {
    insert(itemCount + 1, current->getItem());
    current = current->getNext();
  }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
   // Once the above copy constructor implementation is complete
   // use copy swap idiom to implement assignment operator
   std::swap(itemCount, x.itemCount);
   std::swap(headPtr, x.headPtr);
   return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  // TODO, swap helper function for copy assignment
  std::swap(itemCount, x.itemCount);
  std::swap(headPtr, x.headPtr);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return (itemCount == 0);
}

template <typename T>
int LinkedList<T>::getLength() const noexcept
{
  return itemCount;
}

template <typename T>
bool LinkedList<T>::insert(int position, const T &item)
{
  // TODO
  if (position < 1 || position > itemCount + 1) return false;  // Add bounds check
  
  Node<T> *newNode = new Node<T>(item);
  Node<T> *current = headPtr;
  if (position == 1)
  {
    newNode->setNext(headPtr);
    headPtr = newNode;
  }
  else
  {
    for (int i = 1; i < position - 1; i++)
    {
      current = current->getNext();
    }
    newNode->setNext(current->getNext());
    current->setNext(newNode);
  }
  itemCount++;
  return true;
}

template <typename T>
bool LinkedList<T>::remove(int position)
{
  // TODO
  if (position < 1 || position > itemCount) return false;  // Add bounds check
  
  Node<T> *current = headPtr;
  if (position == 1)
  {
    headPtr = current->getNext();
    delete current;
  }
  else
  {
    for (int i = 1; i < position - 1; i++)
    {
      current = current->getNext();
    }
    Node<T> *temp = current->getNext();
    current->setNext(temp->getNext());
    delete temp;
  }
  itemCount--;
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
   while (!isEmpty())
      remove(1); // This implementation has a disadvantage of being inefficient, why?
                 // Think about number of operations.      
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T LinkedList<T>::getEntry(int position) const
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      Node<T> *nodePtr = getNodeAt(position); // call the private helper function
      return nodePtr->getItem();
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
  return T();
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void LinkedList<T>::setEntry(int position, const T &newValue)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      Node<T> *nodePtr = getNodeAt(position); // call the private helper function
      nodePtr->setItem(newValue);
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
}

template <typename T>
Node<T> *LinkedList<T>::getNodeAt(int position) const
{
   Node<T> *current = headPtr;
   for (int i = 1; i < position; i++)
   {
      if (current == nullptr) return nullptr;  // Prevent nullptr dereference
      current = current->getNext();
   }
   return current;
}
