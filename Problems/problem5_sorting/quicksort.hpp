#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

/** Sorts an array into ascending order. Uses the quick sort method.
 @pre  list[first..last] is an array.
 @post  list[first..last] is sorted.
 @throw std::out_of_range if first < 1 or last > list.getLength(), 1-based indexing is used.
 @param list The given array.
 @param first The start element to consider in list.
 @param last The end element to consider in list. */
template <typename T>
void quick_sort(List<T> &list, int first, int last)
{
    // TODO
    // Must call helper function partition()
    if (first < 1 || last > list.getLength())
    {
        throw std::out_of_range("quick_sort out of range");
    }

    if (last <= first)
    {
        return; // base case
    }

    int pivot = partition(list, first, last);
    quick_sort(list, first, pivot - 1); // left partition
    quick_sort(list, pivot + 1, last);  // right partition
}

/** Partitions the entries in an array about a pivot entry for quicksort.
 @pre  list[first..last] is an array; first <= last.
 @throw std::out_of_range if first > last, or if first < 1 or last > list.getLength()
 @post  list[first..last] is partitioned such that:
        S1 = list[first..pivotIndex-1] <= pivot
             list[pivotIndex]          == pivot
        S2 = list[pivotIndex+1..last]  >= pivot
 @param list The given array.
 @param first The start entry to consider in list.
 @param last The end entry to consider in list.
 @return The index of the pivot. */
template <typename T>
int partition(List<T> &list, int first, int last)
{
    // TODO
    // You can choose the pivot yourself, but no matter what you choose
    // list[first..pivotIndex-1] <= pivot, list[pivotIndex] == pivot, list[pivotIndex + 1..last] >= pivot
    /*
    this takes thre arguements, the array, the begining and the end of the array

    */
   int n = list.getLength();
    if (first > last || first < 1 || last > n)
    {
        throw std::out_of_range("partition out of range");
    }
    

   T pivot  = list.getEntry(last);
   int i = first - 1;

   for (int j = first; j <= last - 1; j++)
   {
    if (list.getEntry(j) <= pivot)
    {
        i++;
            // swap list[i] and list[j]
            T temp = list.getEntry(i);
            list.setEntry(i, list.getEntry(j));
            list.setEntry(j, temp);
    }
   }
    
    i++;
    T temp = list.getEntry(i);
    list.setEntry(i, list.getEntry(last));
    list.setEntry(last, temp);
   
    return i;
}
#endif

/*
set pivot to the end of the array
set j to start of the array
set i to 1 before the start of the array
if j greater than the pivot then j++
if j is less than the pivot the i++
then set i to temp
then set i = j and j = temp
basically, if j is less than pivot, swap i and j

now if pivot will be in the right place if all elements to the left are less than the pivot
and all elements to the right of are greater than the pivot

now create a partition that is all the elements to the left of the pivot but not including
second partition is all the elements to the right of the pivot but not including the pivot

now recursively pass partitions into the quicksort
*/