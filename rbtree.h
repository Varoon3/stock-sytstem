#ifndef _RBTREE_H_
#define _RBTREE_H_
#include <string>
using namespace std;

template <typename T>
class Node
{
  public:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* p;  //Parent 
    bool is_black;
    //Constructor
    Node(T value)
    {
      data = value;
      left = NULL;
      right = NULL;
      p = NULL;
      is_black = false;
    }
};

template <typename T>
class RBTree
{
  private:
    Node<T>* root;
    int size;

    // recursive helper function for deep copy
    Node<T>* CopyTree(Node<T>* sourcenode, Node<T>* parentnode);

    // recursive helper function for tree deletion
    void RemoveAll(Node<T>* node);

    // performs BST insertion and returns pointer to inserted node
    Node<T>* BSTInsert(T item);

    // helper function for in-order traversal
    void InOrder(const Node<T>* node, T* arr, int arrsize, int& index) const;

    // helper function for pre-order traversal
    void PreOrder(const Node<T>* node, T* arr, int arrsize, int& index) const;

    // rotation functions
    void RotateLeft(Node<T>* node);
    void RotateRight(Node<T>* node);

    // get the predecessor of a node
    Node<T>* Predecessor(Node<T>* node) const;

    // Searches for a key value and returns a pointer to the node containing it, or NULL if not found
    Node<T>* Find(T item) const;

    // Tree fix, performed after removal of a black node
    void RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild);

    // Calculates the height of the tree
    // Requires a traversal of the tree, O(n)
    int ComputeHeight(Node<T>* node) const;

    // write your own private function declarations in the following file, if needed
    #include "rbtreeprivate.h"

  public:
    // default constructor
    RBTree();

    // copy constructor, performs deep copy of parameter
    RBTree(const RBTree<T>& rbtree);

    // destructor
    ~RBTree();

    // overloaded assignment operator
    RBTree<T>& operator=(const RBTree<T>& rbtree);

    // Calls BSTInsert and then performs any tree fixing.
    bool Insert(T item);

    // Removal of an item from the tree.
    bool Remove(T item);

    // Returns existence of item in the tree.
    bool Contains(T item) const;

    // Searches for item and returns a pointer to the node contents 
    T* Retrieve(T item);

    // deletes all nodes in the tree
    void RemoveAll();

    // returns an array containing tree contents from in-order traversal
    T* DumpInOrder(int& arrsize) const;

    // returns an array containing tree contents from pre-order traversal
    T* DumpPreOrder(int& arrsize) const;

    // returns the number of items in the tree
    int Size() const;

    // returns the height of the tree, from root to deepest null child
    int Height() const;

    // returns a pointer to the root of the tree
    Node<T>* GetRoot() const
    {
      return this->root;
    }
};

#include "rbtreepartial.cpp"
#include "rbtree.cpp"

#endif