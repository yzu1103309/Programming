#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <cstring>
#include <ctime>

#include "SpellCheck.h"

// input all words from the file Dictionary.txt, and put them to the vector "dictionary"
void readDictionary( vector &dictionary );

// return true if and only if wordToCheck == dictionary[ i ] for some i
bool legal( string wordToCheck, vector dictionary );

int main()
{
   srand( static_cast< int >( time(0) ) );
   vector dictionary;

   readDictionary( dictionary );

   string wordToCheck;
   SpellCheck spellCheck;
   for( int i = 0; i < 20; i++ )
   {
      wordToCheck = dictionary[ rand() + dictionary.size() - 32768]; // skip short words
      wordToCheck.erase( rand() % wordToCheck.size(), 1 );

      if( !legal( wordToCheck, dictionary ) )
      {
         cout << "Word to check: " << wordToCheck.c_str() << endl;
        
         spellCheck.equalLength( wordToCheck, dictionary );
         spellCheck.shorter( wordToCheck, dictionary );
         spellCheck.longer( wordToCheck, dictionary );

         spellCheck.output();
         spellCheck.clear();
      }
   }

   system( "pause" );
}

void readDictionary( vector &dictionary )
{
    ifstream inFile("Dictionary.txt", ios::in);
    
    if (!inFile) {
        cout << "File can not be opened" << endl;
        exit(1);
    }

    std::string temp;
    while (inFile >> temp) {
        string buffer;
        buffer.resize(temp.size());
        for (size_t t = 0; t < temp.size(); t++) {
            buffer[t] = temp[t];
        }
        
        dictionary.push_back(buffer);
    }
    inFile.close();
}

bool legal( string wordToCheck, vector dictionary )
{
   for( size_t i = 0; i < dictionary.size(); i++ )
      if( dictionary[ i ] == wordToCheck )
         return true;
   return false;
}