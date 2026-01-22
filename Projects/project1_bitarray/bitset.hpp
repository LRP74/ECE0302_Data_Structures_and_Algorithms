#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h> // support for intmax_t
#include <string>

/// @brief 
class Bitset
{
public:
  virtual ~Bitset() {}; // virtual destructor, no need to comment

  /**
   * @brief: A method to return the CURRENT size of the BitArray
   * @param: none
   * @pre: The BitArray is valid.
   * @post: Returns the current size of the BitArray.
   * @return: The current size of the BitArray.
   */
  virtual intmax_t size() const = 0;

  /**
   * @brief: A method that checks if BitArray is valid.
   * @param: none
   * @pre: The BitArray has been initialized.
   * @post: Returns the validity of the BitArray.
   * @return: true if the BitArray is valid, false otherwise.
   */
  virtual bool good() const = 0;

  /**
   * @brief Sets the bit at the given index to 1. If index is outside [0, size()), the Bitset becomes invalid.
   * @param index Index of the bit to set (0 is leftmost).
   * @pre: The BitArray is valid.
   * @post: Sets the nth bit to 1.
   * @return: nothing
   */
  virtual void set(intmax_t index) = 0;

  /**
   * @brief: Resets the bit at the given index to 0.
   * @param index Index of the bit to reset (0 is leftmost).
   * @pre: The BitArray is valid.
   * @post: Sets the nth bit to 0.
   * @return: nothing
   */
  virtual void reset(intmax_t index) = 0;

  /**
   * @brief: Toggles the bit at the given index.
   * @param index Index of the bit to toggle (0 is leftmost).
   * @pre: The BitArray is valid.
   * @post: Toggles the nth bit.
   * @return: nothing
   */
  virtual void toggle(intmax_t index) = 0;

  /**
   * @brief: Tests if the bit at the given index is set to 1.
   * @param index Index of the bit to test (0 is leftmost).
   * @pre: The BitArray is valid.
   * @post: Returns true if the nth bit is set to 1, false otherwise.
   * @return: true if the nth bit is set to 1, false otherwise.
  */
  virtual bool test(intmax_t index) = 0;

  /**
   * @brief: Returns the BitArray as a string representation. The most significant bit (MSB) is on the left.
   * @param: none
   * @pre: The BitArray is valid.
   * @post: Returns the BitArray as a string of characters '0' and '1'.
   * @return: A string representation of the BitArray.
   */
  virtual std::string asString() const = 0;
};

#endif
