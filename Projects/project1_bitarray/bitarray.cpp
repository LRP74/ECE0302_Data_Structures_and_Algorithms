#include "bitarray.hpp"

BitArray::BitArray()
{
    sizeOfArray = 8;
    isValid = true;
    data = new uint8_t[sizeOfArray]();
}

BitArray::BitArray(intmax_t size)
{
    // TODO
}

BitArray::BitArray(const std::string &value)
{
    // TODO
}

BitArray::~BitArray()
{
    // TODO
}

// TODO: other methods

intmax_t BitArray::size() const
{
    return sizeOfArray;
}

bool BitArray::good() const
{
    return isValid;
}

void BitArray::set(intmax_t index)
{
}

void BitArray::reset(intmax_t index)
{
}

void BitArray::toggle(intmax_t index)
{
}

bool BitArray::test(intmax_t index)
{
    return false;
}

std::string BitArray::asString() const
{
    return std::string();
}
