#pragma once
/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/
#include <string>
#include <vector>
#include "hashTable.h"
#include "adts/stlMaxPriorityQueue.h"

/**
 * This class represents a tool which can be used to perform a keyword search on
 * a document.  The user of this class instantiates it, updates it with words
 * from a document, and can then use it to identify the pages on which specific
 * words appear most frequently.
 */
class KeywordSearcher {
  public:
    /**
     * Creates a new keyword searcher with no data.
     */
    KeywordSearcher();

    /**
     * Destructs a KeywordSearcher and releases the memory it is using.
     */
    ~KeywordSearcher();

    /**
     * Loads the words from a given file into this searcher.
     * @param filename The name of the text file to use.
     */
    void loadWords(std::string filename);

    /**
     * Searches this object to find the pages on which a particular word most
     * frequently appeared.
     * @param word The word to find.
     * @return A vector of pairs between page numbers and occurrences.  The top
     *         ten pages are returned, ordered from most to least occurrences.
     *         All pairs have a positive (non-zero) number of occurrences; if a
     *         word appears on fewer than ten pages, the returned vector
     *         contains fewer than ten elements.
     */
    std::vector<std::pair<int, int>> search(std::string word);

  private:
    // TODO: put your fields and helper declarations here!
    HashTable<string, HashTable<int, int>*> table;
    void addToTable(string word, int pageNum);
};
