#include "limited_size_bag.hpp"

template <typename T>
LimitedSizeBag<T>::LimitedSizeBag()
{
  itemCount = 0;
}

template <typename T>
bool LimitedSizeBag<T>::add(const T &item)
{
  if (itemCount == maxsize)
  {
    return false;
  }
  else
  {
    items[itemCount] = item;
    itemCount++;
  }
  return true;
}

template <typename T>
bool LimitedSizeBag<T>::remove(const T &item)
{
  for (int i = 0; i < itemCount; i++)
  {
    if (items[i] == item)
    {
      items[i] = items[itemCount -1];
      itemCount--;
      return true;
    }
  }
  
  return false;
}

template <typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return (itemCount == 0);
}

template <typename T>
int LimitedSizeBag<T>::getCurrentSize() const
{
  return itemCount;
}

template <typename T>
bool LimitedSizeBag<T>::contains(const T &item) const
{
  for (int i = 0; i < itemCount; i++)
  {
    if (items[i] == item)
    {
      return true;
    }
  }
  
  return false;
}

template <typename T>
void LimitedSizeBag<T>::clear()
{
  itemCount = 0;
}

template <typename T>
int LimitedSizeBag<T>::getFrequencyOf(const T &item) const
{
  int frequencyCount = 0;
  for (int i = 0; i < itemCount; i++)
  {
    if (items[i] == item)
    {
      frequencyCount++;
    }
    
  }
  
  return frequencyCount;
}

template <typename T>
bool LimitedSizeBag<T>::operator==(const AbstractBag<T> &other) const
{
  int thisItemCount = 0;
  int otherItemCount = 0;
  if (this->getCurrentSize() != other.getCurrentSize())
  {
    return false;
  }
  for (int i = 0; i < itemCount; i++)
  {
    thisItemCount = this->getFrequencyOf(items[i]);
    otherItemCount = other.getFrequencyOf(items[i]);

    if (thisItemCount != otherItemCount)
    {
      return false;
    }
    
  }
  
  
  return true;
}