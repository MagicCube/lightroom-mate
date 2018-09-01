#pragma once

#include <Arduino.h>

using namespace std;

// Represents a readonly list.
template <typename T> class ReadonlyList {
public:
  // Creates a new instance of the List class.
  ReadonlyList() {
  }
  ReadonlyList(initializer_list<T> l) : _vector(l) {
  }

  // Iterator for begin.
  typename vector<T>::iterator begin() {
    return _vector.begin();
  }

  // Iterator for end.
  typename vector<T>::iterator end() {
    return _vector.end();
  }

  // Gets the number of items in the list.
  int size() {
    return _vector.size();
  }

  // Returns whether the list is empty.
  bool isEmpty() {
    return _vector.empty();
  }

  // Searches for the specified item and returns the zero-based index of the first occurrence within
  // the list. Returns -1 if not found.
  int indexOf(T item) {
    auto lower = lower_bound(_vector.begin(), _vector.end(), item);
    if (lower != _vector.end()) {
      auto index = lower - _vector.begin();
      return index;
    }
    return -1;
  }

  // Returns true if the given item is in the list.
  bool includes(T item) {
    return indexOf(item) != -1;
  }

protected:
  vector<T> _vector;
};
