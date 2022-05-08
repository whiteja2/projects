// Author: Jacob White
// Date: 1/13/22
// Assignment: Program 1
// Description: An InfiniteInt class that is a linked list capable of holding an integer
// larger than the maximum size of an integer by splitting each digit into one node of the
// linked list. The class also contains several methods including constructors and destructors,
// assignment operator overloading, binary math operator overloading, and stream i/o overloading.

#include <iostream>
using namespace std;
#include "InfiniteInt.h"
#include <climits>
#include <cmath>
#include <string>

// Zero argument constructor creates an InfiniteInt of value 0:
InfiniteInt::InfiniteInt()
{
   head_ = new Node();
   tail_ = head_;
   head_->value = 0;
   head_->next_ = nullptr;
   head_->prev_ = nullptr;
   signFlag_ = 0;
}

// Creates a deep copy of the given InfiniteInt object:
void InfiniteInt::copy(const InfiniteInt& iI)
{
   // set sign flag
   if (iI.signFlag_ == 0) {
      signFlag_ = 0;
   } else {
      signFlag_ = 1;
   }
   // copy the head
   head_ = new Node();
   head_->value = iI.head_->value;
   head_->prev_ = nullptr;
   Node* nodeptr1 = head_;
   Node* nodeptr2 = iI.head_->next_;
   // copy all nodes
   while (nodeptr2 != nullptr) {
      nodeptr1->next_ = new Node();
      nodeptr1->next_->prev_ = nodeptr1;
      nodeptr1 = nodeptr1->next_;
      nodeptr1->value = nodeptr2->value;
      nodeptr2 = nodeptr2->next_;
   }
   // set tail
   nodeptr1->next_ = nullptr;
   tail_ = nodeptr1;
}

// Deep copy constructor copies one InfiniteInt to another:
InfiniteInt::InfiniteInt(const InfiniteInt& iI)
{
   copy(iI);
}

// Deletes the contents of the InfiniteInt:
void InfiniteInt::clear()
{
   // set tail to nullptr
   if (tail_ != nullptr) {
      tail_ = nullptr;
   }
   // traverse nodes, deleting each node
   while (head_ != nullptr) {
      Node* nodeptr = head_;
      head_ = head_->next_;
      delete nodeptr;
   }
}

// Destructor clears the contents of the InfiniteInt:
InfiniteInt::~InfiniteInt()
{
   clear();
}

// Creates and initializes an InfiniteInt object from an int:
InfiniteInt::InfiniteInt(int num)
{
   // set sign flag
   if (num < 0) {
      signFlag_ = 1;
      num = abs(num);
   } else {
      signFlag_ = 0;
   }
   // create tail node
   tail_ = new Node();
   // store digit from num
   int digit = num % 10;
   tail_->value = digit;
   tail_->next_ = nullptr;
   Node* nodeptr = tail_;
   // remove digit from num
   num = (num - digit) / 10;
   // create all nodes containing digits of num
   while (num >= 1) {
      // create new node
      nodeptr->prev_ = new Node();
      nodeptr->prev_->next_ = nodeptr;
      nodeptr = nodeptr->prev_;
      // store digit from num
      digit = num % 10;
      nodeptr->value = digit;
      // remove digit from num
      num = (num - digit) / 10;
   }
   nodeptr->prev_ = nullptr;
   head_ = nodeptr;
}

// Overload assignment operator to work with InfiniteInt's:
InfiniteInt& InfiniteInt::operator=(const InfiniteInt& rhs)
{
   // check if InfiniteInt's are already equal
   if (this == &rhs) {
      return *this;
   }
   // clear InfiniteInt being assigned
   clear();
   // copy right hand side to InfiniteInt
   copy(rhs);
   return *this;
}

// Traverses InfiniteInt and returns number of nodes traversed:
int InfiniteInt::numDigits(void) const 
{
   int count = 0;
   Node* nodeptr = head_;
   // traverse nodes
   while (nodeptr != nullptr) {
      // increase count of nodes
      count++;
      nodeptr = nodeptr->next_;
   }
   return count;
}

// Overloads equality operator to compare two InfiniteInt's:
bool InfiniteInt::operator==(const InfiniteInt& rhs)
{
   // check for different signs and different number of digits
   if (signFlag_ != rhs.signFlag_) {
      return false;
   } if (numDigits() != rhs.numDigits()) {
      return false;
   } else {
      // traverse InfiniteInt's
      Node* nodeptr1 = head_;
      Node* nodeptr2 = rhs.head_;
      while (nodeptr1 != nullptr) {
         // check if value ever differs
         if (nodeptr1->value != nodeptr2->value) {
            return false;
         } else {
            nodeptr1 = nodeptr1->next_;
            nodeptr2 = nodeptr2->next_;
         }
      }
      return true;
   }
}

// Overload less than operator to compare two InfiniteInt's:
bool InfiniteInt::operator<(const InfiniteInt& rhs)
{
   // check sign flags
   if (signFlag_ < rhs.signFlag_) {
      return false;
   } if (signFlag_ > rhs.signFlag_) {
      return true;
   } if (signFlag_ == 1) {
      // check number of digits for negatives
      if (numDigits() > rhs.numDigits()) {
         return true;
      } if (numDigits() < rhs.numDigits()) {
         return false;
      }
   // check number of digits for positives
   } if (numDigits() < rhs.numDigits()) {
      return true;
   } if (numDigits() > rhs.numDigits()) {
      return false;
   }
   // traverse InfiniteInt's
   Node* nodeptr1 = head_;
   Node* nodeptr2 = rhs.head_;
   while (nodeptr1 != nullptr) {
      // check differing values depending on if InfiniteInt's are positive or negative
      if (nodeptr1->value < nodeptr2->value) {
         if (signFlag_ == 1) {
            return false;
         }
         return true;
      } if (nodeptr1->value > nodeptr2->value) {
         if (signFlag_ == 1) {
            return true;
         }
         return false;
      }
      nodeptr1 = nodeptr1->next_;
      nodeptr2 = nodeptr2->next_;
   }
   return false;
}

// Overload output operator to output an InfiniteInt:
ostream& operator<<(ostream& stream, const InfiniteInt& iI)
{
   // check if InfiniteInt is negative
	if (iI.signFlag_ == 1) {
      stream << "-";
   }
   // traverse InfiniteInt
   Node* nodeptr = iI.head_;
	while (nodeptr != nullptr)
	{
      // output value of node
		stream << nodeptr->value;
		nodeptr = nodeptr->next_;
	}
	return stream;
}

// Overload input operator to input into an InfiniteInt:
istream& operator>>(istream& stream, InfiniteInt& iI)
{
   // clear InfiniteInt to store new value
   iI.clear();
   // input into a string
   string inputInt;
   stream >> inputInt;
   int i = 0;
   string digits = "0123456789";
   // check if input is negative
   if (inputInt[0] == '-') {
      iI.signFlag_ = 1;
      i = 1;
   }
   // check if first value is a digit (in string digits)
   if (digits.find(inputInt[i]) != string::npos) {
      iI.head_ = new Node();
      iI.head_->value = (int(inputInt[i]) - 48);
      iI.head_->prev_ = nullptr;
      iI.head_->next_ = nullptr;
      iI.tail_ = iI.head_;
      i++;
   } else {
      // if not, input 0
      iI.signFlag_ = 0;
      iI.head_ = new Node();
      iI.head_->value = 0;
      iI.head_->prev_ = nullptr;
      iI.head_->next_ = nullptr;
      iI.tail_ = iI.head_;
      return stream;
   }
   // traverse through input string, adding digits to nodes
   while (digits.find(inputInt[i]) != string::npos && inputInt.length() > i) {
      iI.tail_->next_ = new Node();
      iI.tail_->next_->value = (int(inputInt[i]) - 48);
      iI.tail_->next_->prev_ = iI.tail_;
      iI.tail_ = iI.tail_->next_;
      iI.tail_->next_ = nullptr;
      i++;
   }
   // remove any leading 0's
   Node* nodeptr = iI.head_;
   while (iI.head_->value == 0 && iI.head_->next_ != nullptr) {
      nodeptr = iI.head_;
      iI.head_ = iI.head_->next_;
      delete nodeptr;
   }
   return stream;
}

// Overload integer conversion operator to convert InfiniteInt's to int's:
InfiniteInt::operator int() const
{
   // check if InfiniteInt is over the max int size
   if (signFlag_ == 0) {
      InfiniteInt overflowLimit{INT_MAX};
      if (overflowLimit < *this) {
         cout << "InfiniteInt object is greater than " << INT_MAX << " so it cannot be converted to an int." << endl;
         throw "Result produces overflow! Returned 0.";
         return 0;
      }
   } else { // check if InfiniteInt is under min int size
      InfiniteInt overflowLimit = InfiniteInt(INT_MIN + 1);
      InfiniteInt convertingInt;
      convertingInt = *this;
      cout << convertingInt << " test convertingInt " << endl;
      if (convertingInt < overflowLimit) {
         cout << "InfiniteInt object is less than " << INT_MIN << " so it cannot be converted to an int." << endl;
         throw "Result produces overflow! Returned 0.";
         return 0;
      }
   }
   // traverse through InfiniteInt
   Node* nodeptr = tail_;
   int num = 0;
   int count = 0;
   while (nodeptr != nullptr) {
      // add digit * 10^number of nodes to num
      num = num + (nodeptr->value * pow(10, count));
      count++;
      nodeptr = nodeptr->prev_;
   }
   // convert int to negative
   if (signFlag_ == 1) {
      num = num * -1;
   }
   return num;
}

// Overload addition operator to add two InfiniteInt's together:
InfiniteInt InfiniteInt::operator+(const InfiniteInt& rhs)
{
   // if signflag is 1 and rhs.signflag is 0, copy this, change copy.signflag, return rhs - copy
   if (signFlag_ == 1 && rhs.signFlag_ == 0) {
      InfiniteInt lhsCopy;
      lhsCopy = *this;
      lhsCopy.signFlag_ = 0;
      InfiniteInt rhsCopy;
      rhsCopy = rhs;
      return (rhsCopy - lhsCopy);
   }
   // if signflag is 0 and rhs.signflag is 1, copy rhs, change copy.signflag, return this - copy
   if (signFlag_ == 0 && rhs.signFlag_ == 1) {
      InfiniteInt rhsCopy;
      rhsCopy = rhs;
      rhsCopy.signFlag_ = 0;
      return *this - rhsCopy;
   }
   // else:
   // two positive InfiniteInt's or two negative InfiniteInt's
   InfiniteInt lhsCopy;
   lhsCopy = *this;
   Node* nodeptr1 = lhsCopy.tail_;
   Node* nodeptr2 = rhs.tail_;
   // traverse until reaching the end of either linked list
   while (nodeptr1 != nullptr && nodeptr2 != nullptr) {
      // add value of rhs to lhs
      nodeptr1->value += nodeptr2->value;
      // carry the one
      if (nodeptr1->value >= 10) {
         // if no node to carry the one to, create a new node
         if (nodeptr1->prev_ == nullptr) {
            nodeptr1->prev_ = new Node();
            nodeptr1->prev_->next_ = nodeptr1;
            nodeptr1->prev_->prev_ = nullptr;
            nodeptr1->prev_->value = 1;
            nodeptr1->value -= 10;
            // set head to new node
            lhsCopy.head_ = nodeptr1->prev_;
         } else { // carry the one
            nodeptr1->prev_->value += 1;
            nodeptr1->value -= 10;
         }
      }
      nodeptr1 = nodeptr1->prev_;
      nodeptr2 = nodeptr2->prev_;
   }
   // check if more nodes need adding or if lhs needs to carry more ones
   while (nodeptr1 != nullptr) {
      // check if we need to carry a one
      if (nodeptr1->value >= 10) {
         // if no node to carry the one to, create a new node
         if (nodeptr1->prev_ == nullptr) {
            nodeptr1->prev_ = new Node();
            nodeptr1->prev_->next_ = nodeptr1;
            nodeptr1->prev_->prev_ = nullptr;
            nodeptr1->prev_->value = 1;
            nodeptr1->value -= 10;
            // set head to new node
            lhsCopy.head_ = nodeptr1->prev_;
         } else { // carry the one
            nodeptr1->prev_->value += 1;
            nodeptr1->value -= 10;
         }
      }
      nodeptr1 = nodeptr1->prev_;
   }
   // check if lhs needs to add more nodes
   while (nodeptr2 != nullptr) {
      lhsCopy.head_->prev_ = new Node();
      lhsCopy.head_->prev_->next_ = lhsCopy.head_;
      lhsCopy.head_->prev_->prev_ = nullptr;
      lhsCopy.head_->prev_->value = nodeptr2->value;
      lhsCopy.head_ = lhsCopy.head_->prev_;
      nodeptr2 = nodeptr2->prev_;
   }
   return lhsCopy;
}

// Overload addition operator to do arithmetic with InfiniteInt's and int's:
InfiniteInt InfiniteInt::operator+(const int num)
{
   // convert int to InfiniteInt
   InfiniteInt infiniteNum(num);
   return *this + infiniteNum;
}

// Subtract and InfiniteInt from a larger InfiniteInt:
InfiniteInt InfiniteInt::subtract(const InfiniteInt& rhs)
{
   // copy InfiniteInt
   InfiniteInt lhsCopy;
   lhsCopy = *this;
   Node* nodeptr1 = lhsCopy.tail_;
   Node* nodeptr2 = rhs.tail_;
   // traverse InfiniteInt's
   while (nodeptr2 != nullptr) {
      // subtract values
      nodeptr1->value = (nodeptr1->value - nodeptr2->value);
      // carry the one if needed
      if (nodeptr1->value < 0) {
         nodeptr1->value += 10;
         nodeptr1->prev_->value -= 1;
      }
      nodeptr1 = nodeptr1->prev_;
      nodeptr2 = nodeptr2->prev_;
   }
   // remove any leading 0's
   while (lhsCopy.head_->value == 0 && lhsCopy.head_->next_ != nullptr) {
      nodeptr1 = lhsCopy.head_;
      lhsCopy.head_ = lhsCopy.head_->next_;
      delete nodeptr1;
   }
   return lhsCopy;
}

// Overload subtraction operator to work with two InfiniteInt's:
InfiniteInt InfiniteInt::operator-(const InfiniteInt& rhs)
{
   // case 1: two positives
   if (signFlag_ == 0 && rhs.signFlag_ == 0) {
      // copy InfiniteInt
      InfiniteInt lhs;
      lhs = *this;
      // organize InfiniteInt's so that the larger InfiniteInt is subtracted from, flip sign if necessary
      if (lhs < rhs) {
         InfiniteInt rhsCopy;
         rhsCopy = rhs;
         lhs = rhsCopy.subtract(lhs);
         lhs.signFlag_ = 1;
         return lhs;
      } else {
         lhs = lhs.subtract(rhs);
         return lhs;
      }
   }
   // case 2: one positive one negative
   if (signFlag_ != rhs.signFlag_) {
      InfiniteInt rhsCopy;
      rhsCopy = rhs;
      // if right is positive, add two negatives
      if (rhsCopy.signFlag_ == 0) {
         rhsCopy.signFlag_ = 1;
      } else { // if right is negative, add two positives
         rhsCopy.signFlag_ = 0;
      }
      return *this + rhsCopy;
   }
   // case 3: two negatives
   // change right to positive and send to addition, addition will send back to subtraction
   InfiniteInt rhsCopy;
   rhsCopy = rhs;
   rhsCopy.signFlag_ = 0;
   return *this + rhsCopy;
}

// Overloaded subtraction operator to subtract integers from InfiniteInt's:
InfiniteInt InfiniteInt::operator-(const int num)
{
   // convert int to InfiniteInt
   InfiniteInt infiniteNum(num);
   return *this - infiniteNum;
}

// Overloaded multiplication operator to work with two InfiniteInt's:
InfiniteInt InfiniteInt::operator*(const InfiniteInt& rhs)
{
   // store total product in InfiniteInt
   Node* nodeptr1 = tail_;
   InfiniteInt multInt;
   // count number of digits in left side
   int numDigits1 = 0;
   // traverse left side
   while (nodeptr1 != nullptr) {
      // count number of digits in right side
      Node* nodeptr2 = rhs.tail_;
      int numDigits2 = 0;
      // traverse right side
      while (nodeptr2 != nullptr) {
         // multiply values
         int tempInt = nodeptr1->value * nodeptr2->value;
         // convert to InfiniteInt
         InfiniteInt tempInfInt(tempInt);
         // add 0's onto end of InfiniteInt for total digits counted
         int totalDigits = numDigits1 + numDigits2;
         for (int i = 0; i < totalDigits; i++) {
            tempInfInt.tail_->next_ = new Node();
            tempInfInt.tail_->next_->value = 0;
            tempInfInt.tail_->next_->prev_ = tempInfInt.tail_;
            tempInfInt.tail_ = tempInfInt.tail_->next_;
            tempInfInt.tail_->next_ = nullptr;
         }
         // add InfiniteInt to total product
         multInt = multInt + tempInfInt;
         nodeptr2 = nodeptr2->prev_;
         numDigits2++;
      }
      nodeptr1 = nodeptr1->prev_;
      numDigits1++;
   }
   // if only one factor is negative, make product negative
   if (signFlag_ != rhs.signFlag_) {
      multInt.signFlag_ = 1;
   }
   // remove leading 0's (in case multiplied by 0)
   while (multInt.head_->value == 0 && multInt.head_->next_ != nullptr) {
      nodeptr1 = multInt.head_;
      multInt.head_ = multInt.head_->next_;
      delete nodeptr1;
   }
   // after removing leading 0's, if value is 0, set to positive
   if (multInt.head_->value == 0) {
      multInt.signFlag_ = 0;
   }
   return multInt;
}

// Overloaded multiplication operator to work with an InfiniteInt and an integer:
InfiniteInt InfiniteInt::operator*(const int num)
{
   // convert integer to InfiniteInt
   InfiniteInt infiniteNum(num);
   return *this * infiniteNum;
}