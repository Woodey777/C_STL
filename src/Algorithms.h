#pragma once
#include <iostream>

template <typename _Iter, typename _Pred>
_Iter findIf(_Iter beg, _Iter end, _Pred pred) {
  for (; beg < end; beg++) {
    if (pred(*beg)) {
      return beg;
    }
  }
  return end;
}

template <typename _Iter, typename _Op>
_Iter minElement(_Iter beg, _Iter end, _Op op) {
  if (beg == end) return end;
  _Iter res = beg;
  ++beg;
  for (; beg < end; beg++) {
    if (op(*res, *beg)) {
      res = beg;
    }
  }
  return res;
}

template <typename _Iter>
_Iter minElement(_Iter beg, _Iter end) {
  if (beg == end) return end;
  _Iter res = beg;
  ++beg;
  for (; beg < end; beg++) {
    if (*res > *beg) {
      res = beg;
    }
  }
  return res;
}

template <typename _Iter>
_Iter maxElement(_Iter beg, _Iter end) {
  if (beg == end) return end;
  _Iter res = beg;
  ++beg;
  for (; beg < end; beg++) {
    if (*res < *beg) {
      res = beg;
    }
  }
  return res;
}

template <typename _Iter, typename _Op>
_Op forEach(_Iter beg, _Iter end, _Op op) {
  for (; beg < end; beg++) {
    op(*beg);
  }
  return op;
}

template <typename _Iter, typename _Op>
void Sort(_Iter beg, _Iter end, _Op op) {
  for (; beg != end; ++beg) {
    std::iter_swap(beg, minElement(beg, end, op));
  }
}

template <typename _Iter, typename _Pred>
int copyIf(_Iter sourceBeg, _Iter sourceEnd, _Iter destBeg, _Pred pred) {
  int size = 0;
  for (; sourceBeg < sourceEnd; sourceBeg++) {
    if (pred(*sourceBeg)) {
      *destBeg = *sourceBeg;
      destBeg++;
      size++;
    }
  }
  return size;
}
