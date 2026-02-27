#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"
#include <cctype>

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
	// start with all the cards in my right hand, current string vector. candidate is empty table

	// check the letter counts and see if it is even possible
	if (cutTest2(candidateStringVector, currentStringVector) == false)
	{
		return;
	}
	// Are there any cards left in my hand?
	if (currentStringVector.empty())
	{
		// No cards left in my hand
		// now check if it's a palindrome
		std::string testSentence;
		// fill up the cards on the table into one continuous sentence
		for (int i = 0; i < candidateStringVector.size(); i++)
		{
			testSentence += candidateStringVector[i];
		}
		// check the odd letter count and is palindrome
		if (cutTest1(candidateStringVector) && isPalindrome(testSentence))
		{
			foundPalidromes.push_back(candidateStringVector);
		}
		return;
	}
	// Try putting card on the table
	for (int i = 0; i < currentStringVector.size(); i++)
	{
		// make copies so you don't mess up the original
		std::vector<std::string> newCandidate = candidateStringVector;
		std::vector<std::string> newRemaining = currentStringVector;

		// take the card i and put it on the copied table
		newCandidate.push_back(currentStringVector[i]);

		// Remove that card from the copied hand; this analogy is starting to not make sense but oh well
		newRemaining.erase(newRemaining.begin() + i);

		// Now do the same thing with fewer cards in my hand
		recursiveFindPalindromes(newCandidate, newRemaining);
	}
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
	wordBankVector.clear();
}

bool FindPalindrome::cutTest1(const std::vector<std::string> &stringVector)
{
	int letterFrequency[26] = {};
	char currentLetter;
	int foundLetterIndex;
	//Checks if a set of words could possibly form a palindrome by counting how many letters have an odd frequency. 
	//If more than one letter has an odd count, no palindrome is possible, so it returns false.
	// need a nested loop to go through the vector list then the inner loop to go through the character of the words at i
	for (int i = 0; i < stringVector.size(); i++)
	{
		for (int j = 0; j < stringVector[i].size(); j++)
		{
			currentLetter = stringVector[i][j];
			foundLetterIndex = tolower(currentLetter) - 'a'; // this will give an index that can be incremented in the letter freq array
			letterFrequency[foundLetterIndex] += 1;
		}
	}

	// iterate throught the letter frequency array and increment them if they are odd
	int oddLetterCount = 0;
	for (int i = 0; i < 26; i++)
	{
		if ((letterFrequency[i] % 2) == 1)
		{
			oddLetterCount++;
		}
	}

	// more than one odd means it can't be a palindrome
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
	//Compares two groups of words and checks if the smaller group's letter frequencies are all present in the 
	//larger group with sufficient counts. 
	//If the smaller side has a letter the larger side doesn't have enough of, no palindrome is possible, so it returns false.
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
			if (letterFrequency_2[i] > letterFrequency_1[i])
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
	// can only be a-z or A-Z, all other characters are invalid
	// when you add make sure the return string keeps the case. ex. KayAk comes back exactly the same.
	// The words that you add to an instance of the class have to be unique.
	// Therefore, you cannot add "Happy" if "happy" has already been added.
	// Note that we ignore case in determining if a word is unique.

	// check if empty
	if (value.empty())
	{
		return false;
	}

	// check if every character is a-z or A-Z, otherwise return false.
	for (int i = 0; i < value.size(); i++)
	{
		if (isalpha(value[i]) == 0)
		{
			return false; // if not a upper or lower case letter than its invalid
		}
	}
	// check for duplicate words
	for (int wordIndex = 0; wordIndex < wordBankVector.size(); wordIndex++)
	{
		// word index is the index of the words in the string vector
		// letter index is the index of the character of that word
		std::string copyOfWordInVector = wordBankVector[wordIndex];
		std::string copyOfValue = value;

		// set both to lower case to compare
		convertToLowerCase(copyOfWordInVector);
		convertToLowerCase(copyOfValue);

		if (copyOfValue == copyOfWordInVector)
		{
			return false; // found duplicate words
		}
	}

	// add word to stringVector
	wordBankVector.push_back(value);
	foundPalidromes.clear();
	std::vector<std::string> emptyVector;
	recursiveFindPalindromes(emptyVector, wordBankVector);
	return true;
}

bool FindPalindrome::add(const std::vector<std::string> &stringVector)
{
	// check for empty vector
	if (stringVector.empty())
	{
		return false;
	}
	// check for empty within the vector
	for (int wordIndex = 0; wordIndex < stringVector.size(); wordIndex++)
	{
		if (stringVector[wordIndex].empty())
		{
			return false;
		}
	}

	// check that all strings only have a-z and A-Z
	for (int wordIndex = 0; wordIndex < stringVector.size(); wordIndex++)
	{
		for (int letterIndex = 0; letterIndex < stringVector[wordIndex].size(); letterIndex++)
		{
			if (isalpha(stringVector[wordIndex][letterIndex]) == 0)
			{
				return false;
			}
		}
	}

	// check for duplicates against existing wordBankVector

	for (int i = 0; i < stringVector.size(); i++)
	{
		std::string newWord = stringVector[i];
		convertToLowerCase(newWord);

		for (int j = 0; j < wordBankVector.size(); j++)
		{
			std::string storedWord = wordBankVector[j];
			convertToLowerCase(storedWord);

			if (newWord == storedWord)
				return false;
		}
	}

	// check for duplicates within the new vector itself
	for (int i = 0; i < stringVector.size(); i++)
	{
		// lower case the first word
		std::string word1 = stringVector[i];
		convertToLowerCase(word1);

		for (int j = i + 1; j < stringVector.size(); j++)
		{
			// lowercase the second word then check
			std::string word2 = stringVector[j];
			// convertToLowerCase(word2);
			word2 = recursiveLowercase(word2, 0);

			if (word1 == word2)
				return false;
		}
	}

	// if everything passes, add all words to stringVector
	for (int i = 0; i < stringVector.size(); i++)
	{
		wordBankVector.push_back(stringVector[i]);
	}

	// run palindrome search once
	foundPalidromes.clear();
	std::vector<std::string> empty_canidateString;
	recursiveFindPalindromes(empty_canidateString, wordBankVector);
	return true;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	return foundPalidromes;
}


// this was a function i made just for fun to play around with recursion more
std::string FindPalindrome::recursiveLowercase(std::string testString, int index)
{
	if (index >= (testString.length()))
		return testString;
	testString[index] = (std::tolower((testString[index])));
	return recursiveLowercase(testString, index + 1);
}

bool FindPalindrome::remove(const std::string &value)
{
    std::string copyOfValue = value;
    convertToLowerCase(copyOfValue);	//make lowercase for easy compare

    for (int i = 0; i < wordBankVector.size(); i++)
    {
        std::string copyOfWord = wordBankVector[i];
        convertToLowerCase(copyOfWord);

        if (copyOfWord == copyOfValue)
        {
            wordBankVector.erase(wordBankVector.begin() + i);

            foundPalidromes.clear();	//clear and resend to wordBankVector
            std::vector<std::string> emptyVector;
            recursiveFindPalindromes(emptyVector, wordBankVector);

            return true;	//return that it is found
        }
    }

    return false;
}