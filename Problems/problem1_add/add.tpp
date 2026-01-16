#include "add.hpp"

template <typename T>
Add<T>::Add() {} // finished

template <typename T>
Add<T>::~Add() {} // finished

template <typename T>
T Add<T>::call(T arg1, T arg2) const
{
  std::cout << "Adding " << arg1 << " and " << arg2 << std::endl; // for debugging
  return arg1 + arg2; // finished
}
