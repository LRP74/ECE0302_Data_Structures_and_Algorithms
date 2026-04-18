#include <cmath>
#include <stdexcept>
#include "ArrayMaxHeap.hpp"

// -----------------------------------------------------------------------
// Private helpers
// -----------------------------------------------------------------------

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   // Start at the last parent and rebuild up to the root
   for (int index = itemCount / 2 - 1; index >= 0; index--)
      heapRebuild(index);
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::shiftUp(int index)
{
   if (index > itemCount)
   {
      return;  // this means you are trying to insert beyond the bounds. like trying to put 9 in a 6 count array
   }
   if (index == 0)
   {
      return;  // this is the base case
   }
   if (items[index] > items[getParentIndex(index)])
   {
      std::swap(items[getParentIndex(index)], items[index]);
   }
   shiftUp(getParentIndex(index)); // recursive function and stop when you are at the top, index == 0
   return;
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::shiftDown(int index)
{
   if (index > itemCount)
   {
      return;  // this means you are trying to insert beyond the bounds. like trying to put 9 in a 6 count array
   }
   int largestIndex = index;  // largest index seen so far
   // if getleftchild returns a number greater then item count then skip
   if (getLeftChildIndex(index) < itemCount && items[index] < items[getLeftChildIndex(index)]) 
   {
      largestIndex = getLeftChildIndex(index);
   }
   // if getleftchild returns a number greater then item count then skip
   if (getRightChildIndex(index) < itemCount && items[largestIndex] < items[getRightChildIndex(index)]) 
   {
      largestIndex = getRightChildIndex(index);
   }
   
   if (largestIndex != index)
   {
      std::swap(items[index], items[largestIndex]);
      shiftDown(largestIndex);   // recurse to the child we swapped
   }
   return;
}

// -----------------------------------------------------------------------
// Public methods
// -----------------------------------------------------------------------

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0)
{
}

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize)
    : itemCount(arraySize)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = i + 1; j < n; j++)
      {
         if (anArray[i] == anArray[j])
         {
            throw std::invalid_argument("found duplicate");
         }
      }
   }
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   heapCreate();
}

template <typename ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
   clear();
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const noexcept
{
   return itemCount == 0;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const noexcept
{
   return ceil(log2(itemCount + 1));
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const noexcept
{
   return itemCount;
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::clear() noexcept
{
   itemCount = 0;
}

// -----------------------------------------------------------------------
// TODO (private and public methods)
// -----------------------------------------------------------------------

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   //build max heap creates max heap from unsorted array
   if (!isLeaf(subTreeNodeIndex))
   {
      // TODO
      // 1. Find the larger child
      // 2. If the node < larger child, swap them
      // 3. Recurse on the swapped child's index
      shiftDown(subTreeNodeIndex);
   }
}

template <typename ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   // TODO
   // Throw std::out_of_range if heap is empty
   if (isEmpty() == true)
   {
      throw std::out_of_range("heap is empty");
   }
   
   return items[0]; // return root
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType &newData)
{
   // TODO
   // 1. Return false if full or newData is a duplicate
   // 2. Place newData at the end
   // 3. Bubble up: swap with parent until heap property is restored
   if (itemCount >= DEFAULT_CAPACITY)
   {
      return false;  // return if full
   }
   for (int i = 0; i < itemCount; i++)
   {
      if (items[i] == newData)
      {
         return false;  // return if duplicate
      }
      
   }
   
   items[itemCount] = newData;  // place at next open spot
   itemCount++;
   shiftUp(itemCount - 1);      // sift up from where we just inserted
   
   return true; 
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   // TODO
   // 1. Return false if empty
   // 2. Remove the root by replacing it with the last item
   // 3. Bubble down by calling heapRebuild to restore heap property
   if (isEmpty() == true)
   {
      return false;
   }
   
   std::swap(items[0], items[itemCount - 1]);
   itemCount--;
   shiftDown(0);
   return true; // placeholder
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapSort(ItemType anArray[], int n)
{
   //heapify?
   // TODO
   // 1. Start with entire array as heap region, sorted region empty
   // 2. Build max heap (bottom-up)
   // 3. Repeat until heap is empty:
   //    Swap root (max) with last element in heap
   //    Move that element to sorted region (end of array)
   //    Shrink heap region by 1
   //    Heapify root to restore heap
   // 4. End state: Heap region empty, Sorted region = entire array (ascending order)
   // 5. Reverse array to get descending order
   if (n > DEFAULT_CAPACITY)
   {
      throw std::invalid_argument("anArray is too big");
   }

   for (int i = 0; i < n; i++)
   {
      for (int j = i + 1; j < n; j++)
      {
         if (anArray[i] == anArray[j])
         {
            throw std::invalid_argument("found duplicate");
         }
         
      }
      
   }
   

   for (int i = 0; i < n; i++)
   {
      items[i] = anArray[i];
   }
   itemCount = n;
   heapCreate();

   while (itemCount > 1)
   {
      std::swap(items[0], items[itemCount - 1]); //swap first item in array, root, with last item in the array
      itemCount--;
      heapRebuild(0);
   }
   
   itemCount = 0;
   for (int i = 0; i < n; i++)
   {
    anArray[i] = items[i];
   }

   int j = n - 1;
   int i = 0;
   while (i < j)
   {
      std::swap(anArray[i],anArray[j]);
      j--;
      i++;
   }
   
   
}