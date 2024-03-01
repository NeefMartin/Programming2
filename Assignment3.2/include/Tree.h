// Fig. 19.22: Tree.h
// Tree class-template definition.
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "TreeNode.h"

// Tree class-template definition
template<typename NODETYPE> class Tree {
public:
   // insert node in Tree
   void insertNode(const NODETYPE& value) {
      insertNodeHelper(&rootPtr, value); 
   } 

   // begin preorder traversal of Tree
   void preOrderTraversal() const {
      preOrderHelper(rootPtr); 
   } 

   // begin inorder traversal of Tree
   void inOrderTraversal() const {
      inOrderHelper(rootPtr); 
   } 

   // begin postorder traversal of Tree
   void postOrderTraversal() const {
      postOrderHelper(rootPtr); 
   }

   // search function
   void search(const NODETYPE& searchkey) {
      searchHelper(rootPtr,searchkey);
   }

   // print tree
   void outputTree() const {
      outputTreeHelper(rootPtr);
   }


private:
   TreeNode<NODETYPE>* rootPtr{nullptr};

   // utility function called by insertNode; receives a pointer
   // to a pointer so that the function can modify pointer's value
   void insertNodeHelper(
      TreeNode<NODETYPE>** ptr, const NODETYPE& value) {
      // subtree is empty; create new TreeNode containing value
      if (*ptr == nullptr) {
         *ptr = new TreeNode<NODETYPE>(value);
      }
      else { // subtree is not empty
             // data to insert is less than data in current node
         if (value < (*ptr)->data) {
            insertNodeHelper(&((*ptr)->leftPtr), value);
         }
         else {
            // data to insert is greater than data in current node
            if (value > (*ptr)->data) { 
               insertNodeHelper(&((*ptr)->rightPtr), value);
            }
            else { // duplicate data value ignored
               std::cout << value << " dup" << std::endl;
            }
         }
      } 
   } 

   // utility function to perform preorder traversal of Tree
   void preOrderHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) {
         std::cout << ptr->data << ' '; // process node               
         preOrderHelper(ptr->leftPtr); // traverse left subtree  
         preOrderHelper(ptr->rightPtr); // traverse right subtree
      } 
   } 

   // utility function to perform inorder traversal of Tree
   void inOrderHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) {
         inOrderHelper(ptr->leftPtr); // traverse left subtree  
         std::cout << ptr->data << ' '; // process node              
         inOrderHelper(ptr->rightPtr); // traverse right subtree
      } 
   } 

   // utility function to perform postorder traversal of Tree
   void postOrderHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) { 
         postOrderHelper(ptr->leftPtr); // traverse left subtree  
         postOrderHelper(ptr->rightPtr); // traverse right subtree
         std::cout << ptr->data << ' '; // process node                
      } 
   }

   // utility function to perform search within tree
   void searchHelper(TreeNode<NODETYPE>* ptr, const NODETYPE& searchkey) const {
      if (ptr == nullptr) {
         std::cout << "Searchkey not found in tree\n"; //Searchkey not in tree
         return;
      }
      if (ptr->data == searchkey) {
         std::cout << "Adress of " << searchkey << " is " << ptr << '\n'; //pointer points to searchkey
      } 
      else if (ptr->data > searchkey) {
         searchHelper((ptr->leftPtr),searchkey); //pointer points to value higher than searchkey
      }
      else if (ptr->data < searchkey) {
         searchHelper((ptr->rightPtr),searchkey); //pointer points to value higher than searckey
      }
   }

   //utility function to perform printing of tree with proper indentation
   void outputTreeHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) {
         static int level = 0; //initiation of level counter used to determinde amount of spaces
         level++; //per execution of the formula add 1 to counter
         outputTreeHelper(ptr->rightPtr); // traverse right subtree

         //print spaces
         for (int i = 0; i<(level*3); ++i) {
            std::cout << ' ';
         }
         std::cout << ptr->data << '\n'; // process node
         outputTreeHelper(ptr->leftPtr); // traverse left subtree         
         level--; //when moving backwards, reduce 1 from counter
      } 
   }
}; 

#endif


/**************************************************************************
 * (C) Copyright 1992-2017 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
