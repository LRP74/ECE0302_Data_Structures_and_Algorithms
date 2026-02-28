/** @file LinkedStack.hpp */

#ifndef LINKED_STACK_
#define LINKED_STACK_

#include "StackInterface.hpp"
#include "Node.hpp"

/** ADT stack - Linked implementation. */

template <typename ItemType>
class LinkedStack : public StackInterface<ItemType>
{

private:
	Node<ItemType> *topPtr; // Pointer to first node (top) in the chain
public:
	// Constructors and destructor:
	LinkedStack();																									// Default constructor
	LinkedStack(const LinkedStack<ItemType> &aStack);								// Copy constructor
	LinkedStack<ItemType> &operator=(LinkedStack<ItemType> aStack); // Assignment operator
	virtual ~LinkedStack();																					// Destructor

	// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType &newItem);
	bool pop();
	ItemType peek() const;
}; // end LinkedStack

#include "LinkedStack.tpp"

#endif
