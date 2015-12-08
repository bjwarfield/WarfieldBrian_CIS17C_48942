#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tree.h"
using namespace std;

void traverseNodes(int rootData);
int main()
{
    srand(time(0));

    Tree<int> bsTree;

    //add 6 randon ints
    for (int i = 0; i < 6; ++i) {
        bsTree.add(rand()%100+1);
    }

    cout<<"***********************\n"
          "InOrder Traverse "<<bsTree.size()<<" nodes\n\n";
    bsTree.printNodes(INORDER);

    cout << "---------------------\n"
            "adding nodes 45, 50, 55 + 5 random nodes\n"
            "---------------------\n\n";

    bsTree.add(50);
    bsTree.add(55);
    bsTree.add(45);
    for (int i = 0; i < 5; ++i) {
        bsTree.add(rand()%100+1);
    }
    cout<<"***********************\n"
          "PreOrder Traverse "<<bsTree.size()<<" nodes\n\n";
    bsTree.printNodes(PREORDER);

    cout << "---------------------\n"
            "removing nodes\n"
            "---------------------\n\n";
    bsTree.remove(50);
    bsTree.remove(55);
    bsTree.remove(45);

    cout<<"***********************\n"
          "PostOrder Traverse "<<bsTree.size()<<" nodes\n\n";
    bsTree.printNodes(POSTORDER);

    return 0;
}


