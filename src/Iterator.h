#pragma once
#ifndef Iterator_h
#define Iterator_h
#include <iostream>

#include "Container.h"

template <class _DataType>
class Vector;

template <typename _DataType>
class VectorIterator {
  _DataType* cur;

 public:
  VectorIterator() : cur(nullptr) {}

  VectorIterator(_DataType* el, unsigned i = 0) { cur = el + i; }

  VectorIterator(const VectorIterator& it) { cur = it.cur; }

  VectorIterator& operator++() {
    cur++;
    return *this;
  }

  VectorIterator operator++(int p) {
    VectorIterator ret = *this;
    cur++;
    return ret;
  }

  VectorIterator& operator--() {
    cur--;
    return *this;
  }

  VectorIterator operator--(int p) {
    VectorIterator ret = *this;
    cur--;
    return ret;
  }

  _DataType& operator*() { return *cur; }

  VectorIterator& operator=(const VectorIterator& el) {
    if (this != &el) {
      cur = el.cur;
    }
    return *this;
  }

  VectorIterator& operator=(_DataType* ptr) {
    if (cur != ptr) {
      cur = ptr;
    }
    return *this;
  }

  VectorIterator operator+(unsigned i) {
    VectorIterator res = *this;
    res.cur += i;
    return res;
  }

  VectorIterator operator-(unsigned i) {
    VectorIterator res = *this;
    res.cur -= i;
    return res;
  }

  long operator-(const VectorIterator& el) {
    long a = cur - el.cur;
    return a;
  }

  bool operator==(const VectorIterator& el) { return cur == el.cur; }

  bool operator!=(const VectorIterator& el) { return cur != el.cur; }

  bool operator<(const VectorIterator& el) { return cur < el.cur; }

  bool operator<(const _DataType* ptr) { return cur < ptr; }

  bool operator<=(const VectorIterator& el) { return cur <= el.cur; }

  bool operator>(const VectorIterator& el) { return cur > el.cur; }

  bool operator>=(const VectorIterator& el) { return cur >= el.cur; }

  VectorIterator& operator+=(int i) {
    cur += i;
    return *this;
  }

  VectorIterator& operator-=(int i) {
    cur -= i;
    return *this;
  }

  template <typename _Iter>
  explicit operator _Iter*() const {
    return cur;
  }

  _DataType* operator->() { return cur; }

  bool isNull() { return cur == nullptr; }
};

#endif
