#include "bitarray.hpp"

BitArray::BitArray()
{
    sizeOfArray = 8;    //set default size to 8 bits
    isValid = true;      //initialize as valid
    data = new uint8_t[sizeOfArray]();  //make new heap memory of sizeOfArray and initialize to 0
}

BitArray::BitArray(intmax_t size)
{
    sizeOfArray = size;
    if (size < 0)
    {
        isValid = false;
        sizeOfArray = 0;
        data = nullptr;
        return;
    }  
    isValid = true;     
    data = new uint8_t[sizeOfArray]();  //make new heap memory of sizeOfArray and initialize to 0
}

BitArray::BitArray(const std::string &value)
{
    sizeOfArray = value.length();
    if (sizeOfArray <= 0)
    {
        isValid = false;
        data = nullptr;
        return;
    }
    else
    {
        isValid = true;
        data = new uint8_t[sizeOfArray]();
    }
    
    for (int i = 0; i < sizeOfArray; i++)
    {
        if (value[i] != '0' && value[i] != '1')
        {
            isValid = false;
            break;
        } 
        if (value[i] == '1')
        {
            data[i] = 1;
        }
        else
        {
            data[i] = 0;
        }
    }
    
}

BitArray::~BitArray()
{
    delete[] data;
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
    if (index < 0 || index >= sizeOfArray)
    {
        isValid = false;
        return;
    }
    else
    {
        data[index] = 1;
    }

}

void BitArray::reset(intmax_t index)
{
    if (index < 0 || index >= sizeOfArray)
    {
        isValid = false;
        return;
    }
    else
    {
        data[index] = 0;
    }
}

void BitArray::toggle(intmax_t index)
{
    if (index < 0 || index >= sizeOfArray)
    {
        isValid = false;
        return;
    }
    else if (data[index] ==1)
    {
        data[index] = 0;
    }
    else
    {
        data[index] = 1;
    }
}

bool BitArray::test(intmax_t index)
{
    if (index < 0 || index >= sizeOfArray)
    {
        isValid = false;
        return false;
    }
    else if (data[index] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string BitArray::asString() const
{
    std::string convertedString;
    for (int i = 0; i < sizeOfArray; i++)
    {
        if (data[i] == 1)
        {
            convertedString += '1';
        }
        else
        {
            convertedString += '0';
        }
    }
    return convertedString;
}
