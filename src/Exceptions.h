#include <exception>
#include <iostream>
#include <string>
#ifndef Exceptions_h
#define Exceptions_h

using namespace ::std;

class OutOfRange : public exception {
  string err;

 public:
  const char* what() const throw() { return err.c_str(); }
  OutOfRange(int i) : err("Index " + to_string(i) + " is out of range") {}
};
#endif