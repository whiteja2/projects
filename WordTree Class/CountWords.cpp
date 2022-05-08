// Author: Jacob White
// Date: 3/4/22
// Assignment: Program 4
// Description: This is the driver file for the WordTree class, composed of only the main()
// function. The main() receives text that is then transformed into unique, lowercase words.
// These words are then added to a WordTree object. Finally, the WordTree is outputted.

#include <iostream>
using namespace std;
#include "WordTree.h"
#include <string>
#include <cctype>

// main() function that doesn't take any command line inputs. Receives user input, iterates letter
// by letter, sets alphabetical letters to their lowercase form, and adds them to a string.
// Looks at the apostrophes added to the string, determining if they are embedded or not, then
// adds the final word. Lastly, outputs the built WordTree and the number of unique words.
int main()
{
   WordTree tree;
   char letter;
   string word;
   string finalWord;
   // receive input character by character
   while (cin.get(letter)) {
      // check if the character is a letter
      if (isalpha(letter)) {
         // set the letter to lowercase, add letter to word
         letter = tolower(letter);
         word = word + letter;
      }
      // check if the character is an apostrophe, add apostrophe to word
      if (letter == '\'') {
         word = word + letter;
      }
      // check if the character is neither a letter nor an apostrophe
      if (!isalpha(letter) && letter != '\'') {
         // iterate through the word
         for (int i = 0; i < word.length(); i++) {
            // check if character is a letter, add to finalWord
            if (isalpha(word[i])) {
               finalWord = finalWord + word[i];
            }
            // check if character is an embedded apostrophe
            if (word[i] == '\'' && i != 0 && i != word.length() - 1) {
               // check if apostrophe is between two letters, add to finalWord
               if (isalpha(word[i-1]) && isalpha(word[i+1])) {
                  finalWord = finalWord + word[i];
               }
            }
         }
         // check if finalWord isn't empty, add to tree and clear strings
         if (finalWord != "") {
            tree.add(finalWord);
            finalWord = "";
            word = "";
         }
      }
   }
   // output tree and number of unique words
   cout << tree << endl;
   cout << "Number of unique words: " << tree.numWords() << endl;
   return 0;
}
