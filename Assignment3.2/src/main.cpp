//==============================================================
// Filename : main.cpp  
// Authors : Marc de Boer and Leonie Hoekstra
// Group : 1
// License : N.A. or open source license like LGPL
// Description : main file of assignment 3.2
//==============================================================

#include <iostream>
#include <array>
#include "Tree.h"
#include "TreeNode.h"

// forward declaration of class Tree
template<typename NODETYPE> class Tree;

int main() {
    //initiate firstTree object from Tree class
    Tree<int> firstTree;
    //initiate integerlist array 
    int size = 10;
    int integerList[size] = {1,4,3,7,9,10,2,8,6,5};
    //create range-based for-loop to add integers to TreeNodes in the Tree
    for (int item : integerList) {
        firstTree.insertNode(item);
    }

    //create empty integer variable
    int tobesearched;
    //input integer
    std::cout << "Enter integer to search in tree: ";
    std::cin >> tobesearched;
    //run search
    firstTree.search(tobesearched);
    //output tree
    firstTree.outputTree();
    return 0;
}
