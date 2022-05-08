// Author: Jacob White
// Date: 2/25/22
// Assignment: Program 3
// Description: This file contains a recursive function koch() that will calculate 
// new points related to the given points, then call itself until reaching the base case
// where it will output Postscript commands to draw a Koch snowflake. The main() function will
// receive command line arguments and use them to call koch(). It will also output additional
// Postscript commands required to show the Koch snowflake.

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

// Recursive function that takes an int argument to record the current level and four double
// arguments that represent two points. Calculates additional points required to construct
// a Koch curve, calls itself until reaching the base case, then outputs Postscript commands
// to draw the Koch curve.
void koch(int level, double x1, double y1, double x2, double y2)
{
   // base case
   if (level == 0) {
      // output Postscript commands
      cout << x1 << " " << y1 << " moveto" << endl;
      cout << x2 << " " << y2 << " lineto" << endl;
      return;
   }

   /* MATH OBTAINED FROM https://stackoverflow.com/questions/2861904/how-to-find-coordinates-of-a-2d-equilateral-triangle-in-c */
   // find offset between coordinates
   double dX = x2 - x1;
   double dY = y2 - y1;
   // find offset between vertices of equilateral triangle
   double dXT = ((2*dX)/3 + x1) - (dX/3 + x1);
   double dYT = ((2*dY)/3 + y1) - (dY/3 + y1);
   // sin60 and cos60
   double s60 = sin(60 * M_PI / 180.0);    
   double c60 = cos(60 * M_PI / 180.0);
   // rotate and add to point 1 to find point 3
   double x3 = c60 * dXT - s60 * dYT + (dX/3 + x1);
   double y3 = s60 * dXT + c60 * dYT + (dY/3 + y1);

   // call self using five different points
   koch(level - 1, x1, y1, dX/3 + x1, dY/3 + y1);
   koch(level - 1, dX/3 + x1, dY/3 + y1, x3, y3);
   koch(level - 1, x3, y3, (2*dX)/3 + x1, (2*dY)/3 + y1);
   koch(level - 1, (2*dX)/3 + x1, (2*dY)/3 + y1, x2, y2);
}

// Function receives command line arguments and uses them to call koch(). Outputs additional
// Postscript commands required to see the Koch snowflake.
int main(int argc, char* const argv[])
{
   // check the number of arguments received
   if (!(argc == 6)) {
      cerr << "Error: Command must contain five integers." << endl;
      return -1;
   }

   // convert the command line arguments to integers
   int x1 = stoi(argv[1]);
   int y1 = stoi(argv[2]);
   int x2 = stoi(argv[3]);
   int y2 = stoi(argv[4]);
   int level = stoi(argv[5]);
   
   // check if level is valid
	if (level < 0) {
      cerr << "Error: Level of Koch curve must be greater than or equal to zero." << endl;
      return -1;
   }

   // postscript output to see output in specific readers
   cout << "%!PS-Adobe-2.0" << endl;

   // basic koch curve:
   // koch(level, x1, y1, x2, y2);

   // koch snowflake for extra credit:
   // find offset between coordinates
   double dX = x2 - x1;
   double dY = y2 - y1;
   // sin60 and cos60
   double s60 = sin(60 * M_PI / 180.0);    
   double c60 = cos(60 * M_PI / 180.0);
   // rotate and add to point 1 to find point 3
   double x3 = c60 * dX + s60 * dY + x1;
   double y3 = -s60 * dX + c60 * dY + y1;

   // call koch three times to create snowflake
   koch(level, x1, y1, x2, y2);
   koch(level, x2, y2, x3, y3);
   koch(level, x3, y3, x1, y1);

   // output additional postscript commands for drawing and viewing the Koch snowflake
   cout << "stroke" << endl;
   cout << "showpage" << endl;

   return 0;
}
