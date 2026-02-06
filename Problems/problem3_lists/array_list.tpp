#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  itemCount = 0;
  items = nullptr;
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  delete[] items;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  // TODO, copy constructor
  items = nullptr;  //prevent memory error
  itemCount = rhs.itemCount;  //set item count to the 'rhs' object for copy
  items = new T[itemCount];   //create new array of size item count
  for (int i = 0; i < itemCount; i++) //deep-copy the items from 'rhs' object to newly create items array
  {
    items[i] = rhs.items[i];
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  // TODO, copy assignment
  swap(rhs);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  // TODO, swap helper function for copy assignment
  std::swap(items, rhs.items);
  std::swap(itemCount, rhs.itemCount);  //after swap is complete the function will delete rhs
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  return itemCount == 0;
}

template <typename T>
int ArrayList<T>::getLength() const noexcept
{
  return itemCount;
}

template <typename T>
bool ArrayList<T>::insert(int position, const T &item)
{
  // it is only valid to insert after 1 and at the end. after the end is invalid and 0 is invalid.
  bool isAbleToInsert = ((position >= 1) && (position <= itemCount +1));
  if (isAbleToInsert)
  {
    T* newItems = new T[itemCount + 1]; // allocate a new array of size oldCount + 1

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
    return true;
  }
  
  return false;
}

template <typename T>
bool ArrayList<T>::remove(int position)
{
  // TODO
    // it is only valid to remove at 1 and at the end. after the end is invalid and 0 is invalid.
  bool isAbleToRemove = ((position >= 1) && (position <= itemCount));
  if (isAbleToRemove)
  {    T* newItems = new T[itemCount - 1]; // allocate a new array of size oldCount - 1
    int removeIndex = position - 1; // convert to 0-based

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
    return true;
  }
  return false;
}

template <typename T>
void ArrayList<T>::clear()
{
  // TODO
  delete[] items; // free old array and update pointer
  items = nullptr;
  itemCount = 0;
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T ArrayList<T>::getEntry(int position) const
{
  // TODO
  if (position < 1 || position > itemCount)
  {
    throw std::out_of_range("Position is out of range");
  }
  return items[position - 1]; // convert to 0-based index
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void ArrayList<T>::setEntry(int position, const T &newValue)
{
  // TODO
  if (position < 1 || position > itemCount)
  {
    throw std::out_of_range("Position is out of range");
  }
  items[position - 1] = newValue; // convert to 0-based index
}