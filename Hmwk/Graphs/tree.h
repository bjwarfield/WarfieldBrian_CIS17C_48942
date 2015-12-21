#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <iomanip>

using namespace std;
enum traversal{INORDER, PREORDER, POSTORDER};
template <class T>
class Tree
{
private:

    enum branchDir{LEFT, RIGHT};

    typedef struct node{
        T       data{};
        int     height;
        node*   left;
        node*   right;
    }* nodePtr;

    nodePtr root;
    void    addLeaf(const T &data, nodePtr &ptr);
    void    balanceNode(nodePtr &ptr);
    nodePtr createLeaf(const T &data);
    T       findMin(nodePtr &ptr);
    nodePtr getNode(T data);
    int     getBalance(nodePtr &ptr);
    int     getHeight(nodePtr &ptr);
    int     getSize(nodePtr &ptr);
    void    inOrderTraverse(nodePtr &ptr);
    int     getMax(int a, int b);
    void    preOrderTraverse(nodePtr &ptr);
    void    postOrderTraverse(nodePtr &ptr);
    void    removeNode(const T &data, nodePtr &parent);
    void    removeRootMatch();
    void    removeMatch(nodePtr &parent, nodePtr &match, branchDir dir);
    nodePtr returnNode(T data, nodePtr &ptr);
    void    removeSubTree(nodePtr &ptr);
    nodePtr rotateLeft(nodePtr &z);
    nodePtr rotateRight(nodePtr &z);
    void    setHeight(nodePtr &ptr);

public:

    Tree();
    ~Tree();
    void    add(const T &data);
    int     height();
    T       min();
    T       max();
    void    printChildren(T data);
    void    printNodes(traversal order = INORDER);
    void    remove(const T &data);
    T       rootData();
    int     size();
    bool    isEmpty(){return root == NULL;}

};

/**
 *default constructor. Created null noot node
 */
template<class T>
Tree<T>::Tree()
{
    root = NULL;
}

/**
 *destructor. deletes all nodes in tree
 */
template<class T>
Tree<T>::~Tree()
{
    removeSubTree(root);
}

/**
 * traverses tree in inOrder, printing node information along the way
 * @param ptr pointer to node to traverse
 */
template<class T>
void Tree<T>::inOrderTraverse(nodePtr &ptr)
{
    if(root!= NULL){
        if(ptr->left != NULL){
            inOrderTraverse(ptr->left);
        }

//        cout<< Ptr->data << " ";
        cout << "Parent Node:" << setw(4) << ptr->data  << "     Height: " << ptr->height << endl;

        ptr->left == NULL?
            cout << "Left Child: " << setw(4)<< "NULL\n":
            cout << "Left Child: " << setw(4)<< ptr->left->data << "     Height: " << ptr->left->height << endl;

        ptr->right == NULL?
            cout << "Right Child:" << setw(4)<< "NULL\n":
            cout << "Right Child:" << setw(4)<< ptr->right->data << "     Height: " << ptr->right->height << endl;
        cout<<"\n";

        if(ptr->right != NULL){
            inOrderTraverse(ptr->right);
        }
    }else{
        cout << "Tree has no data\n";
    }
}


/**
 * Helper function, returns highest of two integers
 * @param a integer 1
 * @param b integer 2
 */
template<class T>
int Tree<T>::getMax(int a, int b)
{
    return a > b ? a : b;
}

/**
 * traverses tree in preOrder, printing node information along the way
 * @param ptr pointer to node to traverse
 */
template<class T>
void Tree<T>::preOrderTraverse(nodePtr &ptr)
{
    if(root!= NULL){
        cout << "Parent Node:" << setw(4) << ptr->data  << "     Height: " << ptr->height << endl;

        ptr->left == NULL?
            cout << "Left Child: " << setw(4)<< "NULL\n":
            cout << "Left Child: " << setw(4)<< ptr->left->data << "     Height: " << ptr->left->height << endl;

        ptr->right == NULL?
            cout << "Right Child:" << setw(4)<< "NULL\n":
            cout << "Right Child:" << setw(4)<< ptr->right->data << "     Height: " << ptr->right->height << endl;
        cout<<"\n";

        if(ptr->left != NULL){
            preOrderTraverse(ptr->left);
        }
        if(ptr->right != NULL){
            preOrderTraverse(ptr->right);
        }
    }else{
        cout << "Tree has no data\n";
    }
}

/**
 * traverses tree in postOrder, printing node information along the way
 * @param ptr pointer to node to traverse
 */
template<class T>
void Tree<T>::postOrderTraverse(Tree::nodePtr &ptr)
{
    if(root!= NULL){
        if(ptr->left != NULL){
            postOrderTraverse(ptr->left);
        }
        if(ptr->right != NULL){
            postOrderTraverse(ptr->right);
        }

        cout << "Parent Node:" << setw(4) << ptr->data  << "     Height: " << ptr->height << endl;

        ptr->left == NULL?
            cout << "Left Child: " << setw(4)<< "NULL\n":
            cout << "Left Child: " << setw(4)<< ptr->left->data << "     Height: " << ptr->left->height << endl;

        ptr->right == NULL?
            cout << "Right Child:" << setw(4)<< "NULL\n":
            cout << "Right Child:" << setw(4)<< ptr->right->data << "     Height: " << ptr->right->height << endl;
        cout<<"\n";

    }else{
        cout << "Tree has no data\n";
    }
}

/**
 *return minimum value in tree. throws exception if tree is empty
 * @param ptr pointer to begin traversal
 */
template <class T>
T Tree<T>::findMin(Tree::nodePtr &ptr)
{
    //traverse left branch till null
    if(root != NULL){
        if(ptr->left != NULL){
            return findMin(ptr->left);
        }else{
            return ptr->data;
        }
    }else{
        throw;
    }
}

/**
 *print all nodes in given order
 * @param order enem value {INORDER(default), PREORDER, POSTORDER}
 */
template<class T>
void Tree<T>::printNodes(traversal order)
{
    switch(order){
    case INORDER:
        inOrderTraverse(root);
        break;
    case PREORDER:
        preOrderTraverse(root);
        break;
    case POSTORDER:
        postOrderTraverse(root);
        break;
    }

}

/**
 *helper function. startes recursive addLeaf function with given template value
 * @param data to insert into tree
 */
template<class T>
void Tree<T>::add(const T &data)
{
    addLeaf(data, root);
}

/**
 * return tree height
 * @return height of tree at root
 */
template<class T>
int Tree<T>::height()
{
    return getHeight(root);
}

/**
 *remove node first node containing data value received
 * @param data value to remove
 */
template<class T>
void Tree<T>::remove(const T &data)
{
    removeNode(data, root);
}

/**
 *return data in root node. Throws exception if tree is empty.
 * @return data in root node
 */
template<class T>
T Tree<T>::rootData()
{
    if(root!= NULL){
      return root->data;
    }else{
        throw;
    }
}

/**
 * helper functon. starts getSize function at root
 * @return number of nodes in tree
 */
template<class T>
int Tree<T>::size()
{
    return getSize(root);
}

/**
 *find node in tree and print it and its children. Prints error if not found
 * @param data template class value to search
 */
template<class T>
void Tree<T>::printChildren(T data)
{
    nodePtr ptr = getNode(data);

    if(ptr != NULL){
        cout << "Parent Node:" << setw(4) << ptr->data  << "     Depth: " << ptr->height << endl;

        ptr->left == NULL?
            cout << "Left Child: " << setw(4)<< "NULL\n":
            cout << "Left Child: " << setw(4)<< ptr->left->data << "     Depth: " << ptr->left->height << endl;

        ptr->right == NULL?
            cout << "Right Child:" << setw(4)<< "NULL\n":
            cout << "Right Child:" << setw(4)<< ptr->right->data << "     Depth: " << ptr->right->height << endl;
    }else{
        cout << "Data not found\n";
    }
}

/**
 *returns minimum value in tree
 */
template<class T>
T Tree<T>::min()
{
    return findMin(root);
}

/**
 *returns maximun value in tree
 */
template<class T>
T Tree<T>::max()
{
    return findMax(root);
}

/**
 *created and returns new node with given data member
 * @param T template class value
 * @return pointer to new node leaf
 */
template<class T>
typename Tree<T>::nodePtr Tree<T>::createLeaf(const T &data)
{
    //create new blank node
    nodePtr n = new node;
    n->data = data;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

/**
 *recursively traverse tree and add new leaf in appropriate branch
 * @param data, value to be inserted
 * @param ptr pointer to current node being traversed
 */
template<class T>
void Tree<T>::addLeaf(const T &data, nodePtr &ptr)
{
    //create new root if null
    if(root == NULL){
        ptr = createLeaf(data);
        root = ptr;
    //if less than current
    }else if(data < ptr->data){
        if(ptr->left == NULL){//add to left if null
            ptr->left = createLeaf(data);
        }else{//traverse left if not null
            addLeaf(data, ptr->left);
        }
    //greater than or equal to
    }else{
        if(ptr->right == NULL){//add to right if null
            ptr->right = createLeaf(data);
        }else{//traverse left if not null
            addLeaf(data, ptr->right);
        }
    }
    //set depth values on traversal unwinding
    setHeight(ptr);

    balanceNode(ptr);

}

/**
 * check node for balance. rotate if applicable
 * @param ptr to balance
 */
template <class T>
void Tree<T>::balanceNode(Tree::nodePtr &ptr)
{
    int balance = getBalance(ptr);

    if(balance > 1 ){
        if(getBalance(ptr->left) > 0){//left left
            ptr = rotateRight(ptr);
        }else if(getBalance(ptr->left) < 0){//left right
            ptr->left = rotateLeft(ptr->left);
            ptr = rotateRight(ptr);
        }

    }
    if(balance < -1){
        if(getBalance(ptr->right) < 0){//right right
            ptr = rotateLeft(ptr);
        }else if(getBalance(ptr->right) > 0){//right left
            ptr->right = rotateRight(ptr->right);
            ptr = rotateLeft(ptr);
        }
    }
}

/**
 *recursively traverse (preorder) tree, removing first node found matching data
 * @param data for which to match
 * @param parent pointer to node to traverse
 */
template<class T>
void Tree<T>::removeNode(const T &data, nodePtr &parent)
{
    if(root != NULL){
        if(root->data == data){//if matches root
            removeRootMatch();
        }else{
            if(data < parent->data && parent->left != NULL){//if less than parent
                parent->left->data  == data ?//if left match
                            removeMatch(parent, parent->left, LEFT) ://remove left node
                            removeNode(data, parent->left);//else traverse left

            }else if(data > parent->data && parent->right != NULL){//if greater than parent
                parent->right->data  == data ?//if right match
                            removeMatch(parent, parent->right, RIGHT) ://remove right node
                            removeNode(data, parent->right);//else traverse right
            }else{//node not found
                cout << "Data not found in tree.\n";
                return;
            }
        }

    }else{
        //no data to search
        cout << "Tree contains no data.\n";
        return;
    }
    //adjust depth values
    setHeight(parent);
    //balance node if applicable
    balanceNode(parent);
}

/**
 * Safely delete root node
 */
template<class T>
void Tree<T>::removeRootMatch()
{
    if(root != NULL){
        nodePtr delPtr = root;
        T minInRightSubTree;

        //case 0 - 0 children
        if(root->left == NULL && root->right == NULL){
            root = NULL;
            delete delPtr;
        //case 1 - 1 child
        }else if(root->left == NULL && root->right != NULL){
            root = root->right;
            delPtr->right = NULL;
            delete delPtr;
        }else if(root->left != NULL && root->right == NULL){
            root= root->left;
            delPtr->left = NULL;
            delete delPtr;
        //case 2 - 2 children
        }else{
            minInRightSubTree = findMin(root->right);
            removeNode(minInRightSubTree, root);
            root->data = minInRightSubTree;
        }

    }else{
        cout << "Tree contains no data.\n";
    }
}

/**
 * safely remove matching node and reattach child nodes
 * @param parent parent of matching node
 * @param match node to be removed
 * @param dir LEFT/RIGHT relation of match to parent
 */
template<class T>
void Tree<T>::removeMatch(Tree::nodePtr &parent, Tree::nodePtr &match, Tree::branchDir dir)
{
    if(root != NULL){
        nodePtr delPtr;
//        T matchData = match->data;
        T minInRightTree;
        delPtr = match;

        //case 0: 0 Children
        if(match->left == NULL && match->right == NULL){
            dir == LEFT?
                parent->left = NULL:
                parent->right = NULL;
            delete delPtr;
         //case 1 - 1 child
        }else if(match->left ==NULL && match->right != NULL){
            dir == LEFT?
                      parent->left = match->right:
                      parent->right = match->right;
            match->right = NULL;
            delete delPtr;
        }else if(match->left != NULL && match->right == NULL){
            dir == LEFT?
                      parent->left = match->left:
                      parent->right = match->left;
            match->left = NULL;
            delete delPtr;
        //case 2 - 2 children
        }else{
            //swap in data tp  matching node from min value in right subtree and delete old dubtree leaf
            minInRightTree = findMin(match->right);
            removeNode(minInRightTree, match);
            match->data = minInRightTree;
        }


    }else{
        cout<< "Cannot remove node. Tree is Empty"<<endl;
    }
}

/**
 *  helper class, starts the retrun node recursive function at the root
 * @param data for which to search
 * @return pointer to first node containing data, NULL if data not found
 */
template<class T>
typename Tree<T>::nodePtr Tree<T>::getNode(T data)
{
    return returnNode(data, root);
}

/**
 *return height of current node; 0 if node is NULL
 * @param ptr pointer to node from which to get height
 * @return node height, 0 if node is NULL
 */
template<class T>
int Tree<T>::getHeight(nodePtr &ptr)
{
    return ptr ? ptr->height : 0;
}

/**
 * recursively get count of all nodes in tree
 * @param ptr pointer to node to traverse
 * @return number of leaves in given subtree root
 */
template<class T>
int Tree<T>::getSize(Tree::nodePtr &ptr)
{
    if(ptr){//add 1 to recursive total, traverse both branches
        return getSize(ptr->left) + getSize(ptr->right) +1;
    }else{//null node
        return 0;
    }
}

/**
 *return balance of given node; positive == left unbalanced, negative == right
 * unbalanced, 0 == balanced
 */
template<class T>
int Tree<T>::getBalance(Tree::nodePtr &ptr)
{
    if(ptr){
        return getHeight(ptr->left) - getHeight(ptr->right);
    }else{
        return 0;
    }
}

/**
 * traverse tree in preOrder, returning first node matching given data
 * @param data for which to search
 * @param ptr pointer to current node to traverse
 * @return node matching data or NULL if not found
 */
template<class T>
typename Tree<T>::nodePtr Tree<T>::returnNode(T data, nodePtr &ptr)
{
    if(ptr != NULL){
        if(ptr->data == data){
            return ptr;
        }else{
            if(data < ptr->data){
                return returnNode(data, ptr->left);
            }else{
                return returnNode(data, ptr->right);
            }
        }
    }else{
        return NULL;
    }
}

/**
 * remove node and all subsequent child nodes
 * @param ptr pointer to node to delete
 */
template<class T>
void Tree<T>::removeSubTree(nodePtr &ptr)
{
    //post order treverseal
    if(ptr != NULL){
        if(ptr->left != NULL){
            removeSubTree(ptr->left);
        }
        if(ptr->right != NULL){
            removeSubTree(ptr->right);
        }
        delete ptr;
    }
}

/**
 *  rotate node to the right
 * @param x pointer to node to rotate
 * @return root node of rotated branches
 */
template<class T>
typename Tree<T>::nodePtr Tree<T>::rotateRight(Tree::nodePtr &z)
{
    nodePtr y = z->left;
    nodePtr x = y->right;

    //rotate
    y->right = z;
    z->left = x;
    //fix heights
    setHeight(z);
    setHeight(x);
    setHeight(y);

    return y;
}

/**
 *  rotate node to the left
 * @param x pointer to node to rotate
 * @return root node of rotated branches
 */
template<class T>
typename Tree<T>::nodePtr Tree<T>::rotateLeft(nodePtr &z)
{
    nodePtr y = z->right;
    nodePtr x = y->left;

    //rotate
    y->left = z;
    z->right = x;
    setHeight(z);
    setHeight(x);
    setHeight(y);

    return y;
}

/**
 *set node height member based on the height of left and right children
 * @param ptr node to set
 */
template<class T>
void Tree<T>::setHeight(nodePtr &ptr)
{
    if(ptr){
        ptr->height = getMax(getHeight( ptr->right), getHeight(ptr->left)) + 1;
    }
}


#endif // TREE_H
