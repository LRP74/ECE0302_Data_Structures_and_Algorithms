/** @file Stack.tpp */
// Finish this link-based Stack to pass unit tests 1~3

#include <stdexcept>
#include "Stack.hpp"
#include "Node.hpp"

template <typename ItemType>
Stack<ItemType>::Stack()
{
	headPtr = nullptr;
	currentSize = 0;
}

template <typename ItemType>
Stack<ItemType>::~Stack()
{
	clear();
}

template <typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	if (currentSize == 0)
	{
		return true;
	}
	
	return false;
}

template <typename ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}

template <typename ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
	Node<ItemType>* newNode = new Node<ItemType>(newItem, headPtr);
	headPtr = newNode;
	currentSize++;
	return true;	// i don't need to check anything because c++ will throw exception if a node can't be made
}

template <typename ItemType>
ItemType Stack<ItemType>::peek() const
{
	if (currentSize == 0)
	{
		throw std::logic_error ("stack is empty");
	}
	
	return headPtr->getItem();
}

template <typename ItemType>
bool Stack<ItemType>::pop()
{
	if (currentSize == 0)
	{
		return false;
	}
	Node<ItemType>* tempPointer = headPtr->getNext();
	delete headPtr;
	headPtr = tempPointer;
	currentSize--;
	return true;
}

template <typename ItemType>
void Stack<ItemType>::clear()
{
	Node<ItemType>* currentPtr = headPtr;
	while (headPtr != nullptr)
	{
		currentPtr = headPtr->getNext();
		delete headPtr;
		headPtr = currentPtr;
	}
	currentSize = 0;
}