/* Eda Grace J. Paragoso - CCC-CS2A */

/* CCC121 Laboratory Exercise No. 2
Due: December 18, 2022 (Sunday) at 11:55PM */

#include <iostream>
#include <queue>
#include <assert.h>

using namespace std;

/* The structure to be used for representing a binary tree node. This struct
declaration should not be modified in any way. */
template <class T> struct BinNode
{
    T element;
    BinNode<T> *left;
    BinNode<T> *right;
};

// helper functions for allocating binary tree nodes
template <class T> BinNode<T> *makeBinNode(T &element, BinNode<T> *left,
        BinNode<T> *right)
{
    // allocate a node given the values of the element, left, and right
    // fields
    BinNode<T> *result;

    result = new BinNode<T>; // throwing allocation
    assert(result != NULL);	// for backwards compatibility with
    //pre-standard compilers

    // set the field values
    result->element = element;
    result->left = left;
    result->right = right;

    return result;
}

template <class T> BinNode<T> *makeBinNode(T &element)
{
    // allocate a node given only the value of the element field
    return makeBinNode(element, (BinNode<T> *)NULL, (BinNode<T> *)NULL);
}

// function prototypes for the binary tree traversals
// already implemented
// preorder traversal
template <class T> void preorder(BinNode<T>* root);

// to be implemented
// inorder traversal
template <class T> void inorder(BinNode<T>* root);

// postorder traversal
template <class T> void postorder(BinNode<T>* root);

// levelorder traversal
template <class T> void levelorder(BinNode<T> *root);

// class BSTree
// collection using binary search tree designed for fast insertion,
// test and removal operations

template <class T> class BSTree
{
public:
    // default constructor
    BSTree();

    // copy constructor
    BSTree(const BSTree &);

    // destructor
    ~BSTree();

    // remove all values from the collection
    void clear();

    // insert a value into the tree
    void insert(T &value);

    // remove a value from the tree
    T remove(T &value);

    // remove and return the value of the root node
    T removeAny();

    // test if value is in the collection
    int includes(T &value) const;

    // return the count of values
    int size() const;

    // display the values using different traversal methods
    void displayTraversals() const;
protected:
    // pointer to the root node
    BinNode<T> *root;

    // number of nodes in the collection
    int nodecount;

    // method used internally to delete top node
    BinNode<T> *removeTop(BinNode<T> *topNode);

    // method used internally to deallocate entire subtree
    void release(BinNode<T> *root);

    // method used internally to create a copy of the entire subtree
    BinNode<T> *copy(BinNode<T> *root);
};

// default constructor implementation
template <class T> BSTree<T>::BSTree()
{
    // initialize empty tree
    root = NULL;
    nodecount = 0;
}

// copy constructor implementation
template <class T> BSTree<T>::BSTree(const BSTree<T> &v)
{
    // initialize tree by adding all the elements from argument
    root = copy(v.root);
    nodecount = v.nodecount;
}

// destructor implementation
template <class T> BSTree<T>::~BSTree()
{
    // deallocate tree
    clear();
}

// implementation of method that removes all values from the collection
template <class T> void BSTree<T>::clear()
{
    release(root);

    root = NULL;
    nodecount = 0;
}

// implementation of method that removes and returns the value of the
// root node
template <class T> T BSTree<T>::removeAny()
{
    T element;

    // root cannot be null
    assert(root != NULL);

    BinNode<T> * newroot = removeTop(root);

    // save the value of the root node
    element = root->element;

    delete root;
    root = newroot;

    nodecount--;

    return element;
}

// implementation of method that returns the count of values
template <class T> int BSTree<T>::size() const
{
    return nodecount;
}

// implementation of method that displays the values using different
// traversal methods
template <class T> void BSTree<T>::displayTraversals() const
{
    cout << "Preorder traversal: ";
    preorder(root);
    cout << endl;

    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    cout << "Postorder traversal: ";
    postorder(root);
    cout << endl;

    cout << "Levelorder traversal: ";
    levelorder(root);
    cout << endl;
}

// implementation of the method used internally to delete top node
template <class T> BinNode<T> *BSTree<T>::removeTop(BinNode<T> *topNode)
{
    // remove top most node from a binary search tree
    BinNode<T> *left = topNode->left;
    BinNode<T> *right = topNode->right;

    // case 1, no left node
    if (left == 0)
        return right;

    // case 2, no right node
    if (right == 0)
        return left;

    // case 3, right node has no left node
    BinNode<T> *n = right->left;
    if (n == 0)
    {
        right->left = left;
        return right;
    }

    // case 4, slide down left tree
    BinNode<T> *parent = right;
    while (n->left != 0)
    {
        parent = n;
        n = n->left;
    }

    // now parent point to n,
    // n has no left child
    // disconnect and move to top
    parent->left = n->right;
    n->left = left;
    n->right = right;

    return n;
}

// implementation of the method used internally to deallocate entire
// subtree
template <class T> void BSTree<T>::release(BinNode<T> *root)
{
    if (!root)
        return;

    // recursively deallocate the subtree
    release(root->left);
    release(root->right);

    delete root;
}

// implementation of the method used internally to create a copy of the
// entire subtree
template <class T> BinNode<T> *BSTree<T>::copy(BinNode<T> *root)
{
    if (!root)
        return NULL;

    // recursively create a copy of the subtree
    BinNode<T> *newLeft = copy(root->left);
    BinNode<T> *newRight = copy(root->right);
    BinNode<T> *newNode = makeBinNode<T>(root->element, newLeft,
                                         newRight);

    return newNode;
}

// the visit function for the traversal methods
template <class T> void visit(BinNode<T>* root)
{
    // visit routine for binary tree node
    // just display the value of the element
    cout << root->element << " ";
}

// implementation of the preorder traversal function
template <class T> void preorder(BinNode<T>* root)
{
    if (root == NULL)
        return; // Empty subtree, do nothing

    // visit the node
    visit(root); // Perform desired action

    preorder(root->left);
    preorder(root->right);
}


/*Implement the following missing methods and functions here. Use
assertions as necessary to ensure the correct operation of this program.
All memory allocations should be checked with assertions and all
discarded memory must be properly deallocated. */

// implementation of method that tests if value is in the collection
template <class T> int BSTree<T>::includes(T &val) const
{
    BinNode<T> *current = root;

    // Keep searching until the value is found or we reach a leaf node
    while(current != NULL) {
        if(val == current->element) {
            // Value was found
            return 1;
        }
        else if(val <= current->element) {
            // Search the left subtree
            current = current->left;
        }
        else {
            // Search the right subtree
            current = current->right;
        }
    }

    // Value was not found
    return 0;
}

// implementation of method that inserts a value into the tree
template <class T> void BSTree<T>::insert(T &val)
{
    // create a new node with the given value
    BinNode<T> *newNode = makeBinNode<T>(val,NULL,NULL);

    // find the correct position in the tree for the new node
    BinNode<T> *current = root;
    BinNode<T> *parent = NULL;

    while(current != NULL) {
        parent = current;
    if (val <= current->element) {
        current = current->left;
    }
        else {
            current = current->right;
        }
    }

    if(parent == NULL) {
        root = newNode;
    }
    else if (val <= parent->element) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    nodecount++;
}

// implementation of method that removes a value from the tree
template <class T> T BSTree<T>::remove(T &val)
{
  // find the node that contains the value
  BinNode<T> *current = root;
  BinNode<T> *parent = NULL;

  while (current != NULL && current->element != val) {
    parent = current;
    if (val <= current->element) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  // use removeTop to delete the node and update nodecount
  BinNode<T> *temp = removeTop(current);
  if (parent == NULL) {
    root = temp;
  } else if (parent->left == current) {
    parent->left = temp;
  } else {
    parent->right = temp;
  }

  T element = current->element;

  delete current;
  nodecount--;
  return element;
}

// implementation of the inorder traversal function
template <class T> void inorder(BinNode<T>* root)
{
     if (root == NULL) {
         return;
     }

    // visit the left subtree
    inorder(root->left);

    // visit the root node
    visit(root);

    // visit the right subtree
    inorder(root->right);
}

// implementation of the postorder traversal function
template <class T> void postorder(BinNode<T>* root)
{
    if (root == NULL) {
        return;
    }

    // visit the left subtree
    postorder(root->left);

    // visit the right subtree
    postorder(root->right);

    visit(root);
}

// implementation of the levelorder traversal function
template <class T> void levelorder(BinNode<T> *root)
{
    if(root == NULL) {
        return;
    }

    // a Queue to store the nodes at each level
    queue<BinNode<T>*> q;
    q.push(root);

    while(!q.empty())
    {
        BinNode<T> *current = q.front();
        q.pop();

        // visit the current node
        visit(current);

        // add the children of the current node to the queue
        if(current->left != NULL) {
            q.push(current->left);
        }

        if(current->right != NULL) {
            q.push(current->right);
        }
    }
}


/*
This is the main function for testing the implementation of the BSTree
class. This function can be freely modified.
*/
int main(void)
{
    int i;
    int arr[] = {1, 5, 2, 7, 4, 3, 5, 8, 9, 2, 10, 11, 3, 7, 9, 8, 4, 6,
                 1, 6
                };
    BinNode<char> nodeArray[9];
    BinNode<char> *Aptr, *Bptr, *Cptr, *Dptr, *Eptr, *Fptr, *Gptr, *Hptr,
            *Iptr;
    BSTree<int> tree, *treeCopy;

    cout << "the tree size is: " << tree.size() << endl;

    for (i = 0; i < 20; ++i)
    {
        cout << "inserting " << arr[i] << "..." << endl;
        tree.insert(arr[i]);
    }

    cout << "the tree size is: " << tree.size() << endl;

    cout << "displaying traversals..." << endl;
    tree.displayTraversals();

    treeCopy = new BSTree<int>(tree);

    for (i = 1; i <= 5; ++i)
    {
        cout << "removing " << i << "..." << endl;
        tree.remove(i);
    }

    cout << "the tree size is: " << tree.size() << endl;

    cout << "displaying traversals..." << endl;
    tree.displayTraversals();

    for (i = 1; i <= 5; ++i)
    {
        if (tree.includes(i))
        {
            cout << i << " is in the tree..." << endl;
        }
        else
        {
            cout << i << " is not in the tree..." << endl;
        }
    }

    cout << "emptying the tree..." << endl;
    tree.clear();
    cout << "the tree size is: " << tree.size() << endl;

    // display the contents of copy
    cout << "displaying traversals of copy..." << endl;
    treeCopy->displayTraversals();

    for (i = 0; i < 5; ++i)
    {
        cout << "removed " << treeCopy->removeAny() << " from copy..."
             << endl;
    }

    cout << "the copy tree size is: " << treeCopy->size() << endl;

    // display the contents of copy
    cout << "displaying traversals of copy..." << endl;
    treeCopy->displayTraversals();

    delete treeCopy;

    cout << "constructing a statically-allocated binary tree..." << endl;

    // construct a statically-allocated binary tree from the textbook
    // set the node pointers
    Aptr = &nodeArray[0];
    Bptr = &nodeArray[1];
    Cptr = &nodeArray[2];
    Dptr = &nodeArray[3];
    Eptr = &nodeArray[4];
    Fptr = &nodeArray[5];
    Gptr = &nodeArray[6];
    Hptr = &nodeArray[7];
    Iptr = &nodeArray[8];

    // set the node values
    Aptr->element = 'A';
    Bptr->element = 'B';
    Cptr->element = 'C';
    Dptr->element = 'D';
    Eptr->element = 'E';
    Fptr->element = 'F';
    Gptr->element = 'G';
    Hptr->element = 'H';
    Iptr->element = 'I';

    // set the child nodes
    Aptr->left = Bptr;
    Aptr->right = Cptr;

    Bptr->left = NULL;
    Bptr->right = Dptr;

    Cptr->left = Eptr;
    Cptr->right = Fptr;

    Dptr->left = NULL;
    Dptr->right = NULL;

    Eptr->left = Gptr;
    Eptr->right = NULL;

    Fptr->left = Hptr;
    Fptr->right = Iptr;

    Gptr->left = NULL;
    Gptr->right = NULL;

    Hptr->left = NULL;
    Hptr->right = NULL;

    Iptr->left = NULL;
    Iptr->right = NULL;

    // display preorder traversal of the tree
    cout << "Preorder traversal: ";
    preorder(Aptr);
    cout << endl;

    // display inorder traversal of the tree
    cout << "Inorder traversal: ";
    inorder(Aptr);
    cout << endl;

    // display postorder traversal of the tree
    cout << "Postorder traversal: ";
    postorder(Aptr);
    cout << endl;

    // display levelorder traversal of the tree
    cout << "Levelorder traversal: ";
    levelorder(Aptr);
    cout << endl;

    return 0;
}
