// Author: Jacob White
// Date: 1/13/22
// Assignment: Program 1
// Description: The header file for an InfiniteInt class and a Node struct which declares many
// public methods, private member variables, and a few private methods.

#pragma once
#include <iostream>
using namespace std;

struct Node {
   int value;
   Node* next_;
   Node* prev_;
};

class InfiniteInt { // Doubly Linked List
   public:
      InfiniteInt();
      InfiniteInt(const InfiniteInt&);
      ~InfiniteInt();
      explicit InfiniteInt(int num);
      explicit operator int () const;
      InfiniteInt& operator=(const InfiniteInt&);
      int numDigits(void) const;
      friend ostream& operator<<(ostream&, const InfiniteInt&);
      friend istream& operator>>(istream&, InfiniteInt&);
      bool operator==(const InfiniteInt&);
      bool operator<(const InfiniteInt&);
      InfiniteInt operator+(const InfiniteInt&);
      InfiniteInt operator-(const InfiniteInt&);
      InfiniteInt operator*(const InfiniteInt&);
      InfiniteInt operator+(const int num);
      InfiniteInt operator-(const int num);
      InfiniteInt operator*(const int num);
   private:
      Node* head_;
      Node* tail_;
      int signFlag_;
      void copy(const InfiniteInt&);
      void clear();
      InfiniteInt subtract(const InfiniteInt&);
};