/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <vector>

#include "keywordSearcher.h"

using namespace std;

int main(int argc, char** argv) {
    string fileName;
    string userWord;
    fileName = argv[1];
    KeywordSearcher theSearch;
    theSearch.loadWords(fileName);
    cout << "Loading File: " << fileName << endl;
    cout << "File Loaded." << endl;

    cout << "Please Enter a Search Word or Enter ! to Quit" << endl;
    cin >> userWord;

    while(userWord != "!"){
      vector<pair<int, int>> finalVec = theSearch.search(userWord);
      for(int i = 0; i < finalVec.size(); i++) {
        cout << "On Page " << finalVec[i].first << " (" << finalVec[i].second << " Occurrences)" << endl;
      }
      cout << "Please Enter a Search Word or Enter ! to Quit" << endl;
      cin >> userWord;
    }
    cout << "Goodbye!" << endl;

}
