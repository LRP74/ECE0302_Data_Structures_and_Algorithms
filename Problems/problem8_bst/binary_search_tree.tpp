#include "binary_search_tree.hpp"
#include <algorithm>
#include <stack>
#include <stdexcept>

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = nullptr;
} // end default constructor

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(const BinarySearchTree &rhs)
{
    root = copyTree(rhs.root);
} // end copy constructor

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType> &BinarySearchTree<KeyType, ItemType>::operator=(BinarySearchTree rhs)
{
    std::swap(root, rhs.root);
    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy(); // delegate to destroy function to deallocate
} // end destructor

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == nullptr);
} // end isEmpty

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(const KeyType &key, ItemType &item)
{
    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *curr_parent = nullptr;
    bool found = search(key, curr, curr_parent);
    item = found ? curr->data : ItemType(); // if key is found, curr points to the node with the key
    return found;
} // end retrieve

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    // TODO: Iteratively delete all nodes in the tree using a stack.
    // Hint: Use a stack to traverse the tree. For each node, push its children onto the stack, delete the node,
    // and repeat until the stack is empty. Set root to nullptr at the end to avoid dangling pointers.
    if (root == nullptr)    //check if the tree is empty
    {
        return;
    }
    
    std::stack<Node<KeyType, ItemType> *> treeStack; // create a stack that holds a pointers of Node type
    treeStack.push(root);
    Node<KeyType, ItemType>* poppedPtr;   //temporary pointer to grab the top of the stack

    while (treeStack.empty() == false)
    {
        // pop a node
        poppedPtr = treeStack.top();
        treeStack.pop();
        // push its left child if it exists
        if (poppedPtr->left != nullptr)
        {
            treeStack.push(poppedPtr->left);
        }
        
        // push its right child if it exists
        if (poppedPtr->right != nullptr)
        {
            treeStack.push(poppedPtr->right);
        }
        // delete the popped node
        delete poppedPtr;
    }
    root = nullptr;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(const KeyType &key, const ItemType &item)
{
    // TODO: Insert a new node into the BST if the key does not already exist.
    // Hint: If the tree is empty, create it as root node.
    // Otherwise, use the search function to check for duplicates and find the correct parent
    // If the key is unique, allocate a new node, and link it as the left or right child of the parent.
    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *curr_parent = nullptr;
    //bool found = search(key, curr, curr_parent);   
    if (isEmpty() == true)
    {
        root = new Node<KeyType, ItemType>;
        root->key = key;
        root->data = item;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    else if (search(key, curr, curr_parent) == false) // item not found
    {
        Node<KeyType, ItemType> *newNode = new Node<KeyType, ItemType>; // make a new node
        newNode->key = key;
        newNode->data = item;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if (key < curr_parent->key)
        {
            curr_parent->left = newNode;
            return true;
        }
        else
        {
            curr_parent->right = newNode;
            return true;
        }
    }
    
    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    // TODO: Remove a node with the given key from the BST, handling all cases.
    // Hint: If the tree is empty, return false.
    // Use the search function to find the node and its parent. If not found, return false.
    // For deletion, handle these cases:  (1) node is a leaf, (2) node has only a right child,
    // (3) node has only a left child, (4) node has two children (replace with inorder successor).
    // Update parent pointers and free memory as needed. Return true if deleted, false otherwise.

    if (isEmpty() == true){return false;}   // tree is empty return false
    
    Node<KeyType, ItemType>* curr = nullptr;    //locastion of the found key, if nullptr after search then it doesn't exist
    Node<KeyType, ItemType> *curr_parent = nullptr; //location of the node right above the location of the curr or found key

    if (search(key, curr, curr_parent) == true) //key found
    {
        // case 1, no children just a leaf
        if ((curr->left == nullptr) && (curr->right == nullptr)) // there are no children so is an individual leaf
        {
            if (curr == root)
            {
                root = nullptr;
            }
            else if (curr->key < curr_parent->key)
            {
                curr_parent->left = nullptr;
            } // if the found key is less than the parent key then its a left child
            else
            {
                curr_parent->right = nullptr;
            }
            delete curr; // free the memory of the leaf
            return true;
        }

        // case 2, only one left or right child
        if (((curr->left != nullptr) && (curr->right == nullptr)) || ((curr->left == nullptr) && (curr->right != nullptr)))
        {
            if (curr == root)
            {
                if (root->left == nullptr)
                {
                    root = curr->right;
                } // root has a right child
                else
                {
                    root = curr->left;
                }
            }
            else if (curr->key < curr_parent->key) // curr is left child of parent
            {
                if (curr->left != nullptr)
                    curr_parent->left = curr->left;
                else
                    curr_parent->left = curr->right;
            }
            else // curr is right child of parent
            {
                if (curr->left != nullptr)
                    curr_parent->right = curr->left;
                else
                    curr_parent->right = curr->right;
            }
            delete curr;
            return true;
        }
        // case 3, two children
        if ((curr->left != nullptr) && (curr->right != nullptr))
        {
            //inorder sucessor function needs these pointers
            Node<KeyType, ItemType>* inorder = nullptr;   
            Node<KeyType, ItemType>* inorder_parent = nullptr; 

            inorder_successor(root, curr, inorder, inorder_parent);

            //'swap' the data like how the book describes. case 3 is swap the node you want to delete with the inorder successor
            curr->key = inorder->key;
            curr->data = inorder->data;

            if (inorder_parent->left == inorder)
                inorder_parent->left = inorder->right;
            else
                inorder_parent->right = inorder->right;

            delete inorder;
            return true;
        }
    }

    return false;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int arr_size)
{
    // TODO: Implement tree sort using the BST.
    // Hint: Insert all array elements into the BST, throwing an exception if a duplicate is found.
    // Then perform an in-order traversal to collect sorted values and overwrite the input array with them.
    // In-order traversal can be conducted starting from the leftmost node and repeatedly finding the inorder successor.
    // Alternatively, you can find the leftmost node, remove it from the tree, and repeatly find the new leftmost node.
    destroy();

    for (int i = 0; i < arr_size; i++)
    {
        bool insertPassed = insert(arr[i], arr[i]);
        if (insertPassed == false)
        {
            destroy();
            throw std::invalid_argument("failed to insert");
        }
    }

    if (root == nullptr) return;

    Node<KeyType, ItemType>* curr = root;
    while (curr->left != nullptr)
        curr = curr->left;

    for (int i = 0; i < arr_size && curr != nullptr; i++)
    {
        arr[i] = curr->key;
        Node<KeyType, ItemType>* inorder = nullptr;
        Node<KeyType, ItemType>* inorder_parent = nullptr;
        inorder_successor(root, curr, inorder, inorder_parent);
        curr = inorder;
    }
}

// ==================== Private Helper Functions ====================
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder_successor(Node<KeyType, ItemType> *root,
                                                            Node<KeyType, ItemType> *curr,
                                                            Node<KeyType, ItemType> *&inorder,
                                                            Node<KeyType, ItemType> *&inorder_parent)
{
    if (!curr)
    {
        inorder = nullptr;
        inorder_parent = nullptr;
        return;
    }

    // Case 1: Node has right subtree
    // The inorder successor is the leftmost node in the right subtree
    // inorder_parent is tracked in this case
    if (curr->right != nullptr)
    {
        inorder_parent = curr;
        inorder = curr->right;                                 // start with right child
        while (inorder != nullptr && inorder->left != nullptr) // go left until you can't
        {
            inorder_parent = inorder;
            inorder = inorder->left;
        }
        return;
    }

    // Case 2: No right subtree
    // Find the lowest ancestor where curr lies in its left subtree
    // Note: inorder_parent is NOT set in this case
    inorder = nullptr;
    inorder_parent = nullptr;
    Node<KeyType, ItemType> *ancestor = root;
    while (ancestor && ancestor != curr)
    {
        if (curr->key < ancestor->key)
        {
            inorder = ancestor; // potential successor, keep going left to find a closer one
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }
    // inorder now points to the inorder successor (or nullptr if curr is already the largest node)
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::search(KeyType key,
                                                 Node<KeyType, ItemType> *&curr,
                                                 Node<KeyType, ItemType> *&curr_parent)
{
    curr = root;
    curr_parent = nullptr;
    while (curr != nullptr)
    {
        if (key == curr->key) // key is found
            return true;
        curr_parent = curr;
        if (key < curr->key)
            curr = curr->left; // search left subtree
        else
            curr = curr->right; // search right subtree
    }
    return false;
}

template <typename KeyType, typename ItemType>
typename BinarySearchTree<KeyType, ItemType>::template Node<KeyType, ItemType> *
BinarySearchTree<KeyType, ItemType>::copyTree(Node<KeyType, ItemType> *source)
{
    if (!source)
        return nullptr;
    Node<KeyType, ItemType> *newNode = new Node<KeyType, ItemType>;
    newNode->key = source->key;
    newNode->data = source->data;
    newNode->left = copyTree(source->left);
    newNode->right = copyTree(source->right);
    return newNode;
}