#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

//------------------- HELPER FUNCTIONS -----------------------------------------
// non-class helper functions go here, should be declared as "static"

// helper non-member function to convert string to lower case
static void convertToLowerCase(std::string &value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = std::tolower(value[i]);
	}
} // finished

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private function to determine if a string is a palindrome
bool FindPalindrome::isPalindrome(std::string currentString) const
{
	// make sure that the string is lower case
	convertToLowerCase(currentString);
	// see if the characters are symmetric
	int stringLength = currentString.size();
	for (int i = 0; i < stringLength / 2; i++)
	{
		if (currentString[i] != currentString[stringLength - i - 1])
		{
			return false;
		}
	}
	return true;
} // finished

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(std::vector<std::string> candidateStringVector,
																							std::vector<std::string> currentStringVector)
{
	// TODO
	return;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// TODO
}

FindPalindrome::~FindPalindrome()
{
	// TODO
}

int FindPalindrome::number() const
{
	return foundPalidromes.size();
}

void FindPalindrome::clear()
{
	foundPalidromes.clear();
	stringVector.clear();
}

bool FindPalindrome::cutTest1(const std::vector<std::string> &stringVector)
{
	int letterFrequency[26] = {};
	char currentLetter;
	int foundLetterIndex;
	
	//need a nested loop to go through the vector list then the inner loop to go through the character of the words at i
	for (int i = 0; i < stringVector.size(); i++)
	{
		for (int j = 0; j < stringVector[i].size(); j++)
		{
			currentLetter = stringVector[i][j];
			foundLetterIndex = tolower(currentLetter) - 'a';	//this will give an index that can be incremented in the letter freq array
			letterFrequency[foundLetterIndex] += 1;
		}
	}
	
	//iterate throught the letter frequency array and increment them if they are odd
	int oddLetterCount = 0;
	for (int i = 0; i < 26; i++)
	{
		if ((letterFrequency[i] % 2) == 1)
		{
			oddLetterCount++;
		}
	}

	//more than one odd means it can't be a palindrome
	if (oddLetterCount > 1)
	{
		return false;
	}

	return true;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> &stringVector1,
															const std::vector<std::string> &stringVector2)
{
	// break down strings into character arrays
	// see if values in both letter frequencies match
	int letterFrequency_1[26] = {};
	int letterFrequency_2[26] = {};
	char currentLetter_1;
	char currentLetter_2;
	int foundLetterIndex_1;
	int foundLetterIndex_2;

	for (int i = 0; i < stringVector1.size(); i++)
	{
		for (int j = 0; j < stringVector1[i].size(); j++)
		{
			currentLetter_1 = stringVector1[i][j];
			foundLetterIndex_1 = tolower(currentLetter_1) - 'a';
			letterFrequency_1[foundLetterIndex_1] += 1;
		}
	}
	
	for (int i = 0; i < stringVector2.size(); i++)
	{
		for (int j = 0; j < stringVector2[i].size(); j++)
		{
			currentLetter_2 = stringVector2[i][j];
			foundLetterIndex_2 = tolower(currentLetter_2) - 'a';
			letterFrequency_2[foundLetterIndex_2] += 1;
		}
	}

	int totalCharacters_1 = 0;
	int totalCharacters_2 = 0;

	for (int i = 0; i < 26; i++)
	{
		totalCharacters_1 += letterFrequency_1[i];
		totalCharacters_2 += letterFrequency_2[i];
	}

	for (int i = 0; i < 26; i++)
	{
		// check smaller letter group; the larger char group should have at least that many occurances
		if (totalCharacters_1 <= totalCharacters_2)
		{
			if (letterFrequency_1[i] > letterFrequency_2[i])
			{
				return false;
			}
		}
		else
		{
			if (letterFrequency_2[i] < letterFrequency_1[i] )
			{
				return false;
			}
		}
	}

	return true;
}

bool FindPalindrome::add(const std::string &value)
{
	// TODO
	//can only be a-z or A-Z, all other characters are invalid
	//when you add make sure the return string keeps the case. ex. KayAk comes back exactly the same.
	//The words that you add to an instance of the class have to be unique. 
	//Therefore, you cannot add "Happy" if "happy" has already been added. 
	//Note that we ignore case in determining if a word is unique.
	return false;
}

bool FindPalindrome::add(const std::vector<std::string> &stringVector)
{
	// TODO
	//can only be a-z or A-Z, all other characters are invalid
	//when you add make sure the return string keeps the case. ex. KayAk comes back exactly the same.
	//The words that you add to an instance of the class have to be unique. 
	//Therefore, you cannot add "Happy" if "happy" has already been added. 
	//Note that we ignore case in determining if a word is unique.
	return false;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	// TODO
	return std::vector<std::vector<std::string>>();
}