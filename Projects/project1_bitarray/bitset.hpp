#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h> // support for intmax_t
#include <string>

class Bitset
{
public:
  virtual ~Bitset() {}; // virtual destructor, no need to comment

  /**
   * @purpose:a method to return the CURRENT size of the BitArray
   *
   *@pre: The BitArray is valid.
   *
   *@post: Returns the current size of the BitArray.
   */
  virtual intmax_t size() const = 0;

  /**
   * @purpose:a method that checks if BitArray is valid.
   *
   *@pre: The BitArray has been initialized.
   *
   *@post: Returns the validity of the BitArray.
   */
  virtual bool good() const = 0;

  /**
   * @purpose: a method to set the nth bit to 1
   *
   *@pre: The BitArray is valid.
   *
   *@post: Sets the nth bit to 1.
   */
  virtual void set(intmax_t index) = 0;

  /**
   * @purpose:a method to set the nth bit to 0
   *
   *@pre: The BitArray is valid.
   *
   *@post: Sets the nth bit to 0.
   */
  virtual void reset(intmax_t index) = 0;

  /**
   * @purpose:a method to toggle the nth bit
   *
   *@pre: The BitArray is valid.
   *
   *@post: Toggles the nth bit.
   */
  virtual void toggle(intmax_t index) = 0;

  /**
   * @purpose: a method to check if the nth bit is set to 1
   *
   *@pre: The BitArray is valid.
   *
   *@post: Returns true if the nth bit is set to 1, false otherwise.
   */
  virtual bool test(intmax_t index) = 0;

  /**
   * @purpose: a method to return the BitArray as a string of characters '0' and '1'
   *
   *@pre: The BitArray is valid.
   *
   *@post: Returns the BitArray as a string of characters '0' and '1'.
   */
  virtual std::string asString() const = 0;
};

#endif
