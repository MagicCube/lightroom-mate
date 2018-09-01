#pragma once

#include <Arduino.h>

#include "ReadonlyList.h"

using namespace std;

// Represents a mutable list of items.
template <typename T> class List : public ReadonlyList<T> {
public:
  // Creates a new instance of the List class.
  List() : ReadonlyList<T>() {
  }
  List(initializer_list<T> l) : ReadonlyList<T>(l) {
  }

  // Overloading [] operator to access elements in array style
  T &operator[](int index) {
    return this->_vector[index];
  }

  // Add the specific item to the list.
  void add(T item) {
    this->_vector.push_back(item);
  }

  // Remove the specific item from the list.
  void remove(T item) {
    int index = this->indexOf(item);
    if (index != -1) {
      removeAt(index);
    }
  }

  // Remove the item with specific index from the list.
  void removeAt(int index) {
    this->_vector.erase(this->_vector.begin() + index);
  }

  // Removes all elements from the list.
  void clear() {
    this->_vector.clear();
  }
};
