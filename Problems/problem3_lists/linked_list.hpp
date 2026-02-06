#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include "abstract_list.hpp"
#include "Node.hpp"

template <typename T>
class LinkedList : public AbstractList<T>
{
public:
  // default constructor
  LinkedList();

  // copy constructor
  LinkedList(const LinkedList &x);

  // destructor
  ~LinkedList();

  // copy assignment
  LinkedList &operator=(LinkedList x);

  void swap(LinkedList &x);

  // determine if a list is empty
  bool isEmpty() const noexcept;

  // return current length of the list
  int getLength() const noexcept;

  // insert item at position in the list
  bool insert(int position, const T &item);

  // remove item at position in the list
  bool remove(int position);

  // remove all items from the list
  void clear();

  // get a copy of the item at position
  // throw std::out_of_range if position < 1 or position > getLength()
  T getEntry(int position) const;

  // set the value of the item at position
  // throw std::out_of_range if position < 1 or position > getLength()
  void setEntry(int position, const T &newValue);

private:
    Node<T> *getNodeAt(int position) const;
    Node<T> *headPtr; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items

   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
}; // end LinkedList

#include "linked_list.tpp"
#endif