#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  // TODO, default constructor
  itemCount = 0;
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  // TODO, destructor
  clear();
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  // TODO, copy constructor
  itemCount = rhs.itemCount;
  for (int i = 1; i <= itemCount; i++)
  {
    items[i] = rhs.items[i];
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  // TODO, copy assignment
    // Once the above copy constructor implementation is complete
    // use copy swap idiom to implement assignment operator
    swap(rhs);  
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  // TODO, swap helper function for copy assignment
  std::swap(itemCount, rhs.itemCount);
  for (int i = 1; i <= DEFAULT_CAPACITY; i++)
  {
    std::swap(items[i], rhs.items[i]);
  }
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
   
  bool ableToInsert = (position >= 1) && (position <= itemCount + 1) && (itemCount < DEFAULT_CAPACITY);
   if (ableToInsert)
   {
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1)
      for (int entryPosition = itemCount; entryPosition >= position; entryPosition--)
      {
         items[entryPosition + 1] = items[entryPosition]; // copy entry on the left to right
      }
      items[position] = item; // Insert new entry
      itemCount++;                   // Increase count of entries
   } // end if

   return ableToInsert;
}

template <typename T>
bool ArrayList<T>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      // Remove entry by shifting all entries after the one at
      // position toward the beginning of the array
      // (no shift if position == itemCount)
      for (int entryPosition = position; entryPosition < itemCount; entryPosition++)
      {
         items[entryPosition] = items[entryPosition + 1]; // copy entry on the right to left
      }
      itemCount--; // Decrease count of entries
   } // end if

   return ableToRemove;
}

template <typename T>
void ArrayList<T>::clear()
{
  itemCount = 0;
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T ArrayList<T>::getEntry(int position) const
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      return items[position]; // given items[0] is not used, position is directly the index
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void ArrayList<T>::setEntry(int position, const T &newValue)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      items[position] = newValue;
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
}
