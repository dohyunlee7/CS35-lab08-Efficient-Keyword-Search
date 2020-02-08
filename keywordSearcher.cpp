/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "keywordSearcher.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

KeywordSearcher::KeywordSearcher() {
    //this->table = new HashTable<string, HashTable<int, int>*>();
}

KeywordSearcher::~KeywordSearcher() {
    // TODO: KeywordSearcher::~KeywordSearcher
    vector<pair<string, HashTable<int, int>*>> total = this->table.getItems();
    for(int i = 0; i < total.size(); i ++){
      delete total[i].second;
    }
}

void KeywordSearcher::addToTable(string word, int pageNum){
  if(this->table.contains(word) == false){
    HashTable<int,int>* innerHash = new HashTable<int, int>();
    innerHash->insert(pageNum, 1);
    this->table.insert(word, innerHash);
  }
  else{
    HashTable<int, int>* innerHash = this->table.get(word);
    if(innerHash->contains(pageNum) == true){
      innerHash->update(pageNum, innerHash->get(pageNum) + 1);
    }
    else{
      innerHash->insert(pageNum, 1);
    }
  }
}

void KeywordSearcher::loadWords(string filename) {
    //need a variable to store elements of the line (string)
    //open the file

    //while is not done (.eof)
      //if the line is a page num, insert the page number
        //add 1 to page number count
        //add 1 to the line #
      //if the line isn't a page #, insert the words to a list
      //add one to the line #
    //at the end, add the page nums and words to a list
    ifstream theFile(filename);
    string word;
    int pageNum;

    theFile >> word;

    while(!theFile.eof()){
        if(word == "$$@@$$PAGE:"){
          theFile >> word;
          pageNum = stoi(word);
          theFile >> word;
        }
        else{
          addToTable(word, pageNum);
          theFile >> word;
        }
    }
    theFile.close();
}

vector<pair<int, int>> KeywordSearcher::search(string word) {
    PriorityQueue<int, pair<int, int>>* theQueue = new STLMaxPriorityQueue<int, pair<int, int>>();
    if(this->table.contains(word) == false){
      vector<pair<int, int>> emptyVec;
      delete theQueue;
      return emptyVec;
    }
    HashTable<int, int>* innerHash = this->table.get(word);
    vector<pair<int, int>> occurrences = innerHash->getItems();
    for(int i = 0; i < occurrences.size(); i ++){
      theQueue->insert((occurrences[i].second), pair<int, int>(occurrences[i].first, occurrences[i].second));
    }
        //create vector
    vector<pair<int, int>> returnVector;
    int myCount = 0;
    while(theQueue->getSize() > 0 && myCount < 10){
        //add peek to returnVector
      returnVector.push_back(theQueue->remove());
        //remove that value from theQueue
      myCount += 1;
    }
    delete theQueue;
    return returnVector;
}
