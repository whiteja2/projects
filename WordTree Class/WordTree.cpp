// Author: Jacob White
// Date: 3/4/22
// Assignment: Program 4
// Description: This file contains the implementation for the WordTree class declared in
// the WordTree.h file. Each public method is a helper function for a private recursive
// function. Implemented methods include a destructor, a function to add words, a function
// to count the number of stored unique words, and an output operator.

#include <iostream>
using namespace std;
#include "WordTree.h"
#include <string>

// public destructor that calls the private, recursive destruct() function to delete the WordTree.
WordTree::~WordTree()
{
   // check if empty
   if (root_ == nullptr) {
      return;
   }
   // call recursive function
   destruct(root_);
   root_ = nullptr;
   return;
}

// private, recursive function to delete a WordTree object. Uses postorder traversal to visit
// the leaves of the tree first, that way each node is deleted. Takes a WordNode pointer to
// traverse.
void WordTree::destruct(WordNode* nodeptr)
{
   // left
   if (nodeptr->left_ != nullptr) {
      destruct(nodeptr->left_);
   }
   // right
   if (nodeptr->right_ != nullptr) {
      destruct(nodeptr->right_);
   }
   // root: delete node
   delete nodeptr;
   return;
}

// public helper function for the private, recursive addR() function. Takes a string and adds
// it as a word to the WordTree object.
void WordTree::add(string word)
{
   // check if WordTree object is empty
   if (root_ == nullptr) {
      root_ = new WordNode;
      root_->word_ = word;
      return;
   }
   // call recursive function
   addR(root_, word);
   return;
}

// private, recursive function to add a word to the WordTree object. Checks if the word is
// already stored within the WordTree. If so, increases that word's count. If not, iterates
// until finding the correct location to add a node. Takes a WordNode pointer to traverse and
// the string to be added.
void WordTree::addR(WordNode* nodeptr, string word)
{
   // check if current node contains the word
   if (word == nodeptr->word_) {
      nodeptr->count_++;
      return;
   }
   // check if added word is less than stored word
   if (word < nodeptr->word_) {
      // check if we've hit a dead end
      if (nodeptr->left_ == nullptr) {
         // add node
         nodeptr->left_ = new WordNode;
         nodeptr->left_->word_ = word;
         return;
      }
      // if not a dead end, continue to the left
      addR(nodeptr->left_, word);
   }
   // if added word is greater than stored word
   else {
      // check if we've hit a dead end
      if (nodeptr->right_ == nullptr) {
         // add node
         nodeptr->right_ = new WordNode;
         nodeptr->right_->word_ = word;
         return;
      }
      // if not a dead end, continue to the right
      addR(nodeptr->right_, word);
   }
}

// overloaded output operator to act as a public helper function for the output() function.
// Takes the ostream reference as well as a const reference to a WordTree object.
ostream& operator<<(ostream& stream, const WordTree& tree)
{
   // check if tree is empty
   if (tree.root_ == nullptr) {
      cout << "No words in WordTree object." << endl;
      return stream;
   }
   // call tree's output() function
   tree.output(tree.root_);
   return stream;
}

// private, recursive function to output the WordTree object. Uses inorder traversal to organize
// the words alphabetically. Takes a WordNode pointer to traverse.
void WordTree::output(WordNode* nodeptr) const
{
   // left
   if (nodeptr->left_ != nullptr) {
      output(nodeptr->left_);
   }
   // root: output node's word and count
   cout << nodeptr->word_ << ": " << nodeptr->count_ << endl;
   // right
   if (nodeptr->right_ != nullptr) {
      output(nodeptr->right_);
   }
   return;
}

// public helper function for the private, recursive numWordsR() function. Returns an integer
// representing the number of unique words stored within the WordTree.
int WordTree::numWords() const
{
   int count = 0;
   // check if tree is empty
   if (root_ == nullptr) {
      return count;
   }
   // call recursive function
   return numWordsR(root_, count);
}

// private, recursive function to count all of the unique words stored within the WordTree.
// Takes a WordNode pointer to traverse and an integer to count the words. Uses preorder traversal.
// Returns an integer representing the count of unique words.
int WordTree::numWordsR(WordNode* nodeptr, int count) const
{
   // root: increase count
   count++;
   // left
   if (nodeptr->left_ != nullptr) {
      count = numWordsR(nodeptr->left_, count);
   }
   // right
   if (nodeptr->right_ != nullptr) {
      count = numWordsR(nodeptr->right_, count);
   }
   return count;
}
