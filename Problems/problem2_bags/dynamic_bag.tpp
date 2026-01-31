#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
  itemCount = 0;
  capacity = 10;
  items = new T[capacity];
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
  itemCount = x.itemCount;
  capacity = x.capacity;
  items = new T[capacity];

  for (int i = 0; i < x.itemCount; i++) //perform deep copy
  {
    items[i] = x.items[i];
  }
  
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
  delete [] items;
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  // TODO, use copy swap idiom
  swap(x);
  return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  // std::swap this object's members with x's members
  std::swap(this->items, x.items);
  std::swap(this->itemCount, x.itemCount);
  std::swap(this->capacity, x.capacity);
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  //
  //check if the bag is full, if full resize and update
  //
  if (itemCount == capacity)  
  {
    T* newArray = new T[capacity * 2];
    for (int i = 0; i < itemCount; i++)
    {
      newArray[i] = items[i];
    }
    delete[] items; //deallocate the memory
    items = newArray; //set pointer to the new pointer
    capacity *= 2;  //update capacity
  }
  //
  //check if the bag is not full then add
  //
  items[itemCount] = item;
  itemCount++;
  
  return true;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  //
  // check the array for the item
  //
  int indexOfFoundItem = 0;
  bool foundItem = false;
  for (int i = 0; i < itemCount; i++)
  {
    if (items[i] == item) //if the item is found set the flag that it is found and set where
    {
      indexOfFoundItem = i;
      foundItem = true;
      break;
    }
    
  }
  //
  // if it is found then swap the location of the last item with the found item and reduce the count. since the bag isn't ordered
  //
  if (foundItem == true)
  {
    items[indexOfFoundItem] = items[itemCount -1];
    itemCount--;
    return true;
  }
  else
  {
    return false; //return false if not found
  }
  
}

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  return itemCount == 0;  //cool way to check rather than an if else statement. Claude AI taught me this.  
}

template <typename T>
int DynamicBag<T>::getCurrentSize() const
{
  return itemCount;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
{
  //
  // check the array for the item
  //
  for (int i = 0; i < itemCount; i++)
  {
    if (items[i] == item) //if the item is found set the flag that it is found
    {
      return true;
    }
    
  }
  return false;
}

template <typename T>
void DynamicBag<T>::clear()
{
  itemCount = 0;  //this makes the bag 'empty' all items will then be overwritten
}

template <typename T>
int DynamicBag<T>::getFrequencyOf(const T &item) const
{
  //
  // check the array for the item
  //
  int frequencyOfItem = 0;
  for (int i = 0; i < itemCount; i++)
  {
    if (items[i] == item) //if the item is found set the flag that it is found
    {
      frequencyOfItem++;
    }
    
  }
  return frequencyOfItem;
};

template <typename T>
bool DynamicBag<T>::operator==(const AbstractBag<T> &other) const
{
  int thisBagItemCount = 0;
  int otherBagItemCount = 0;

  if (this->itemCount != other.getCurrentSize())
  {
    return false;
  }

  else
  {
    for (int i = 0; i < itemCount; i++)
    {
      thisBagItemCount = this->getFrequencyOf(items[i]);
      otherBagItemCount = other.getFrequencyOf(items[i]);

      if (thisBagItemCount != otherBagItemCount)
      {
        return false;
      }
      
    }
    return true;
  }
}