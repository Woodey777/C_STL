#pragma once
#include <iostream>

#include "Exceptions.h"
#include "Iterator.h"

using namespace ::std;

template <class _DataType>
class Vector {
 private:
  _DataType* vec;
  _DataType* vecEnd;
  _DataType* memoryEnd;

 public:
  using iterator = VectorIterator<_DataType>;

  Vector() : vec(nullptr), vecEnd(nullptr), memoryEnd(nullptr) {}

  Vector(int q) { vec = new _DataType[q]; }

  Vector(unsigned len, const _DataType& n = _DataType()) {
    vec = new _DataType[len];
    vecEnd = vec + len;
    memoryEnd = vec + len;
    for (_DataType* i = vec; i < vecEnd; i++) {
      *i = n;
    }
  }

  template <class _Iter>
  Vector(_Iter beg, _Iter end)
      : vec(nullptr), vecEnd(nullptr), memoryEnd(nullptr) {
    for (auto i = beg; i != end; ++i) {
      pushBack(*i);
    }
  }

  Vector(const initializer_list<_DataType>& els) {
    vec = new _DataType[els.size()];
    vecEnd = vec + els.size();
    memoryEnd = vec + els.size();
    _DataType* ptr = vec;
    for (const auto& n : els) {
      *(ptr++) = n;
    }
  }

  Vector(const Vector& el) {
    vec = new _DataType[el.memoryEnd - el.vec];
    vecEnd = vec + el.vecEnd - el.vec;
    memoryEnd = vec + el.memoryEnd - el.vec;
    _DataType ptr = vec;
    for (_DataType elptr = el.vec; elptr < el.vecEnd; elptr++) {
      *(ptr++) = *elptr;
    }
  }

  Vector(Vector&& el) noexcept {
    vec = el.vec;
    vecEnd = el.vecEnd;
    memoryEnd = el.memoryEnd;

    el.vec = nullptr;
    el.vecEnd = nullptr;
    el.memoryEnd = nullptr;
  }

  ~Vector() { delete[] vec; }

  Vector& operator=(const Vector& el) {
    if (this == &el) {
      return *this;
    }
    if ((memoryEnd - vec) != (el.memoryEnd - el.vec)) {
      delete[] vec;
      vec = new _DataType[el.memoryEnd - el.vec];
    }
    vecEnd = vec + (el.vecEnd - el.vec);
    memoryEnd = vec + (el.memoryEnd - el.vec);
    _DataType* beg(el.vec);
    _DataType* end(el.vecEnd);
    _DataType* fill(vec);
    for (; beg < end; beg++) {
      *(fill++) = *beg;
    }
    return *this;
  }

  Vector& operator=(Vector&& el) noexcept {
    if (this == &el) {
      return (*this);
    }
    delete[] vec;
    vec = el.vec;
    vecEnd = el.vecEnd;
    memoryEnd = el.memoryEnd;
    el.vec = nullptr;
    el.vecEnd = nullptr;
    el.memoryEnd = nullptr;
    return *this;
  }

  _DataType& operator[](int i) { return vec[i]; }

  const _DataType& operator[](int i) const { return vec[i]; }

  _DataType& at(int i) {
    if ((i >= (vecEnd - vec)) || (i < 0)) {
      throw OutOfRange(i);
    }
    return vec[i];
  }

  const _DataType& at(int i) const {
    if ((i >= (vecEnd - vec)) || (i < 0)) {
      throw OutOfRange(i);
    }
    return vec[i];
  }

  iterator begin() { return iterator(vec); }

  iterator end() { return iterator(vecEnd); }

  template <class allocate_Type>
  void allocate(allocate_Type& ptr1, allocate_Type& ptr2, bool key) {
    if (key) {
      for (; ptr2 < vecEnd; ptr2++) {
        *(ptr1++) = *ptr2;
      }
    } else {
      for (; ptr1 < vecEnd; ptr1++) {
        *ptr1 = *(ptr2++);
      }
    }
  }

  void pushBack(const _DataType& elem) {
    if (memoryEnd == vecEnd) {
      long capacity = (memoryEnd - vec) * 2;
      if (capacity == 0) {
        capacity = 1;
      }
      long size = vecEnd - vec;
      _DataType* arr = new _DataType[capacity];
      memcpy(arr, vec, sizeof(_DataType) * size);
      vec = arr;
      vecEnd = arr + size;
      memoryEnd = arr + capacity;
      *vecEnd = elem;
      vecEnd++;
    } else {
      *vecEnd = elem;
      vecEnd++;
    }
  }

  void popBack() { *(--vecEnd) = _DataType(); }

  iterator insert(iterator pos, const _DataType& el) {
    long size = vecEnd - vec;
    if (vecEnd == memoryEnd) {
      if (size == 0) size = 1;
      _DataType* arr = new _DataType[(size)*2];
      memcpy(arr, vec, sizeof(_DataType) * (pos - vec - 1));
      *(arr + (pos - vec - 1)) = el;
      memcpy(arr + (pos - vec), vec + (pos - vec - 1),
             sizeof(_DataType) * (size - (pos - vec - 1)));
      pos = arr + (pos - vec - 1);
      delete[] vec;
      vec = arr;
      vecEnd = vec + size + 1;
      memoryEnd = vec + (size * 2);
    } else {
      for (_DataType* ptr = (vecEnd - 1); pos < ptr; ptr--) {
        swap(*ptr, *(ptr + 1));
      }
      *pos = el;
    }
    return pos;
  }

  template <typename _Iter>
  iterator insert(iterator pos, _Iter beg, _Iter end) {
    iterator iBeg(vec);
    iterator iEnd(memoryEnd);
    Vector tmpBefore(iBeg, pos);
    Vector tmpAfter(pos, iEnd);
    int dif = pos - iBeg;
    for (; beg != end; ++beg) {
      tmpBefore.pushBack(*beg);
    }
    iBeg = tmpAfter.begin();
    iEnd = tmpAfter.end();
    for (; iBeg != iEnd; ++iBeg) {
      tmpBefore.pushBack(*iBeg);
    }
    *this = tmpBefore;
    pos = iterator(vec) + dif;
    return pos;
  }

  iterator erase(iterator pos) {
    iterator iVec = vec;
    Vector vecB(iVec, pos);
    iterator iEnd = vecEnd;
    iterator End = vecB.end();
    int dif = pos - vec;
    vec->insert(End, pos + 1, iEnd);
    *this = vecB;
    pos = vec + dif;
    return pos;
  }

  void reserve(int num) {
    int size = vecEnd - vec;
    _DataType* arr = new _DataType[size];
    _DataType* ptr1 = arr;
    _DataType* ptr2 = vec;
    allocate(ptr1, ptr2, true);
    delete[] vec;
    vec = new _DataType[num];
    vecEnd = vec + size;
    memoryEnd = vec + num;
    ptr1 = vec;
    ptr2 = arr;
    allocate(ptr1, ptr2, false);
    delete[] arr;
  }

  void resize(int newSize) {
    if (newSize > (memoryEnd - vec)) {
      (*this).reserve(newSize);
      vecEnd = vec + newSize;
    } else {
      vecEnd = vec + newSize;
    }
  }

  bool empty() const { return (vecEnd == vec); }

  int size() const { return (vecEnd - vec); }

  int capacity() const { return (memoryEnd - vec); }

  void clear() {
    _DataType* tmp = vecEnd;
    for (; tmp > vec; tmp--) {
      *tmp = _DataType();
    }
  }
};
