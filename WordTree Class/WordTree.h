// Author: Jacob White
// Date: 3/4/22
// Assignment: Program 4
// Description: This is the header file for the WordTree class. This class represents a binary
// search tree composed of WordNode objects from the nested struct WordNode. These nodes store
// unique words, a count for duplicates of those words, and left and right pointers. The WordTree
// class itself contains the root pointer and several methods required for a BST.

#pragma once
#include <iostream>
using namespace std;

class WordTree {
   public:
      WordTree(): root_(nullptr){}; // convenience constructor
      ~WordTree();
      void add(string);
      int numWords() const;
      friend ostream& operator<<(ostream&, const WordTree&);
   private:
      struct WordNode { // nested struct
         string word_;
         int count_;
         WordNode* left_;
         WordNode* right_;
         WordNode(): count_(1), left_(nullptr), right_(nullptr){}; // convenience constructor
      };
      WordNode* root_;
      void destruct(WordNode*);
      void addR(WordNode*, string);
      int numWordsR(WordNode*, int) const;
      void output(WordNode*) const;
};