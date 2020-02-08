/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
using std::runtime_error;

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
  this->size = 0;
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {

}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
    if (this->size == 0) {
      return true;
    }
    return false;
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {
    for (int i = 0; i < this->size; i++) {
      if (key == this->ourVector[i].first) {
        throw runtime_error("Key already in vector");
      }
    }
    pair<K,V> temp(key, value);
    this->ourVector.push_back(temp);
    this->size ++;
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
    for (int i = 0; i < this->size; i++) {
      if (key == this->ourVector[i].first) {
        pair<K,V> temp(key, value);
        this->ourVector[i] = temp;
        return;
      }
    }
    throw runtime_error("Key not found");
}

template <typename K, typename V> V
LinearDictionary<K, V>::get(K key) {
  for (int i = 0; i < this->size; i++) {
    if (key == this->ourVector[i].first) {
      return ourVector[i].second;
    }
  }
  throw runtime_error("Key not found");
}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {
  for (int i = 0; i < this->size; i++) {
    if (key == this->ourVector[i].first) {
      return true;
    }
  }
  return false;
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {
  for (int i = 0; i < this->size; i++) {
    if (key == this->ourVector[i].first) {
      this->ourVector.erase(ourVector.begin() + i, ourVector.begin() + i + 1);
      this->size --;
      return;
    }
  }
  throw runtime_error("Key already in vector");
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {
  vector<K> vectorKeys;
  if (ourVector.size() == 0) {
    throw runtime_error("No keys available.");
  }
  for (int i = 0; i < this->size; i++) {
      vectorKeys.push_back(ourVector[i].first);
  }
  return vectorKeys;
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {
  return ourVector;

}
