/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "hashFunctions.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
    this->size = 0;
    this->capacity = 10;
    this->dic = new LinearDictionary<K,V>[this->capacity];
    this->maxLoad = 0.75;
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {
    this->size = 0;
    this->capacity = 10;
    this->dic = new LinearDictionary<K,V>[this->capacity];
    this->maxLoad = maxLoadFactor;
}

template <typename K, typename V>
void HashTable<K, V>::ensureCapacity() {
  float currentLoadF = ((float)this->size) / this->capacity;
  //compare with maxLoadFactor
  //it current > max, then multiply current by 2
  if (currentLoadF > maxLoad){
    int oldCapacity = this->capacity;
    this->capacity = this->capacity * 2;
    LinearDictionary<K,V>* oldDictionary = this->dic;
    this->dic = new LinearDictionary<K,V>[this->capacity];
    for(int i = 0; i < oldCapacity; i ++){
      //get items from i'th chain
      vector<pair<K,V>> items = oldDictionary[i].getItems();
      for(int m = 0; m < items.size(); m++) {
        int index1 = hash(items[m].first, this->capacity);
        this->dic[index1].insert(items[m].first, items[m].second);
        //for each item, insert it into the keys index in this->dic
      }
    }
    delete[] oldDictionary;
  }
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
    // TODO: HashTable<K,V>::~HashTable

      delete [] this->dic;
}

template <typename K, typename V> int HashTable<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
    if (this->size == 0) {
      return true;
    }
    return false;
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {
    //float theLoad = this->size/this->capacity;
    int index = hash(key, this->capacity);
    //ensureCapacity();
    this->dic[index].insert(key, value);
    this->size++;
    ensureCapacity();
}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
  int index = hash(key, this->capacity);
  if (this->dic[index].contains(key) == true) {
    this->dic[index].update(key, value);
    return;
  }
  throw runtime_error("Key not found");

}

template <typename K, typename V> V HashTable<K, V>::get(K key) {
    int index = hash(key, this->capacity);
    return this->dic[index].get(key);
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {
    int index = hash(key, this->capacity);
    if (this->dic[index].contains(key) == true){
        return true;
      }
    return false;
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {
    int index = hash(key, this->capacity);
    this->dic[index].remove(key);
    this->size--;
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
    vector<pair<K,V>> getVec;
    vector<K> finalVec;
    for(int i = 0; i < this->capacity; i ++){
      getVec = this->dic[i].getItems();
      for(int m = 0; m < getVec.size(); m ++){
        finalVec.push_back(getVec[m].first);
    }
  }
    return finalVec;
}


template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
  vector<pair<K,V>> getVec;
  vector<pair<K,V>> finalItems;
  for(int i = 0; i < this->capacity; i ++){
    vector<pair<K,V>> getVec = this->dic[i].getItems();
    for(int m = 0; m < getVec.size(); m ++){
      finalItems.push_back(getVec[m]);
    }
  }
  return finalItems;
}

// TODO: put any other definitions here
