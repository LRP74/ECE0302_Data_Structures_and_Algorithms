#ifndef BITARRAY_HPP
#define BITARRAY_HPP
#include <stdint.h>
#include <string>

#include "bitset.hpp"

class BitArray : public Bitset
{
public:
  BitArray(); // default constructor

  BitArray(intmax_t size); // constructor with intialized size

  BitArray(const std::string &value); // constructor with const reference to a string

  ~BitArray(); // destructor

  BitArray(const BitArray &) = delete;            // not Copy-Constructible
  BitArray &operator=(const BitArray &) = delete; // not Copy-Assignable

  intmax_t size() const; // a method to return the CURRENT size of the BitArray

  bool good() const; // a method that checks if BitArray is valid.

  void set(intmax_t index); // a method to set the nth bit to 1, and if n is not in [0,N-1], then bitarray becomes invalid.

  void reset(intmax_t index); // a method to reset the nth bit to 0, and if n is not in [0,N-1], then bitarray becomes invalid.

  void toggle(intmax_t index); // a method to toggle the nth bit, and if n is not in [0,N-1], then bitarray becomes invalid.

  bool test(intmax_t index); // a method to check if the nth bit is set to 1, and if n is not in [0,N-1], then bitarray becomes invalid.

  std::string asString() const; // a method to return the bitarray as a string of characters '0' and '1'.MSB should be on the left.

private:
  intmax_t sizeOfArray; // current size of the BitArray
  intmax_t index;       // index for bit operations
  bool isValid;         // flag to indicate if the BitArray is valid
  uint8_t *data;        // pointer to dynamic array of bytes to hold bits
};

#endif