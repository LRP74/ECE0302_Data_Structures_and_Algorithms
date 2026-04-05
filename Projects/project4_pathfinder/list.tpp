#include "list.hpp"

template <typename T>
List<T>::List()
{
  itemCount = 0;
  items = nullptr;
}

template <typename T>
List<T>::~List()
{
  delete[] items;
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO, copy constructor
  items = nullptr;                    // prevent memory error
  itemCount = x.itemCount;          // set item count to the 'rhs' object for copy
  items = new T[itemCount];           // create new array of size item count
  for (int i = 0; i < itemCount; i++) // deep-copy the items from 'rhs' object to newly create items array
  {
    items[i] = x.items[i];
  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO, copy assignment
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO, swap helper function for copy assignment
  std::swap(items, x.items);
  std::swap(itemCount, x.itemCount); // after swap is complete the function will delete rhs
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  if (itemCount == 0)
  {
    return true;
  }
  return false;
}

template <typename T>
int List<T>::getLength() const noexcept
{
  return itemCount;
}

template <typename T>
void List<T>::insert(int position, const T &item)
{
  // TODO, implement the insert function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
  // it is only valid to insert after 1 and at the end. after the end is invalid and 0 is invalid.
  bool isAbleToInsert = ((position >= 1) && (position <= itemCount + 1));
  if (isAbleToInsert)
  {
    T *newItems = new T[itemCount + 1]; // allocate a new array of size oldCount + 1

    int insertIndex = position - 1; // convert to 0-based

    for (int i = 0; i < insertIndex; ++i) // copy items before insertion point
    {
      newItems[i] = items[i];
    }

    newItems[insertIndex] = item; // place new item

    for (int i = insertIndex; i < itemCount; ++i) // copy items after insertion point (shift right by 1)
    {
      newItems[i + 1] = items[i];
    }

    delete[] items; // free old array and update pointer
    items = newItems;

    ++itemCount;
  }
  else
  {
    throw std::out_of_range("Out of range.");
  }
  
}

template <typename T>
void List<T>::remove(int position)
{
  // TODO, implement the remove function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
  // it is only valid to remove at 1 and at the end. after the end is invalid and 0 is invalid.
  bool isAbleToRemove = ((position >= 1) && (position <= itemCount));
  if (isAbleToRemove)
  {
    T *newItems = new T[itemCount - 1]; // create a new array of size item count - 1
    int removeIndex = position - 1;     // convert to 0-based

    for (int i = 0; i < removeIndex; ++i) // copy items before removal point
    {
      newItems[i] = items[i];
    }

    for (int i = removeIndex + 1; i < itemCount; ++i) // copy items after removal point (shift left by 1)
    {
      newItems[i - 1] = items[i];
    }

    delete[] items; // free old array and update pointer
    items = newItems;

    --itemCount;
  }
  else
  {
    throw std::out_of_range("out of range.");
  }
}

template <typename T>
void List<T>::clear()
{
  delete[] items; // free old array and update pointer
  items = nullptr;
  itemCount = 0;
}

template <typename T>
T List<T>::getEntry(int position) const
{
  // TODO
  // Throws std::out_of_range if the position is invalid
  if (position < 1 || position > itemCount)
  {
    throw std::out_of_range("Position is out of range");
  }
  return items[position - 1]; // convert to 0-based index
  return T();
}

template <typename T>
void List<T>::setEntry(int position, const T &newValue)
{
  // TODO
  // Throws std::out_of_range if the position is invalid
  if (position < 1 || position > itemCount)
  {
    throw std::out_of_range("Position is out of range");
  }
  items[position - 1] = newValue; // convert to 0-based index
}