/** @file XMLParser.cpp */

#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	// TODO
}

// Then finish this function to pass unit tests 4-6
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	// Use '<' and '>' as anchors to scan the string. Remember to clear each time before
	// tokenizing a new string, and refer to the following code structure:

	// for (char c : inputString)
	// {
	// 	if (c == '<') {?? continue;}
	// 	else if (c == '>') {?? continue;}
	// 	else {?? continue;}
	// }
	//Example: <test>stuff</test>

	bool tag = false;
	bool isEndTag = false;
	std::string testString = "";
	TokenStruct temp_token;

	for (int i = 0; i < inputString.length(); i++)
	{
		if (inputString[i] == '<')
		{
			if (tag == true)
			{
				return false;	//means there is two < like <<...>
			}
			if (testString.empty() == false)	//means there is something in the content section
			{
				temp_token.tokenType = CONTENT;
				temp_token.tokenString = testString;
				tokenizedInputVector.push_back(temp_token);
				testString = "";
				continue;
			}
			
			tag = true;
			continue;
		}
		else if (inputString[i] == '>')
		{
			tag = false;
			if (isEndTag == true)
			{
				temp_token.tokenType = END_TAG;
				temp_token.tokenString = testString;
				tokenizedInputVector.push_back(temp_token);
				testString = "";
				continue;
			}
				
			temp_token.tokenType = START_TAG;
			temp_token.tokenString = testString;
			tokenizedInputVector.push_back(temp_token);
			testString = "";
			continue;
		}

		else if (inputString[i] == '/')
		{
			isEndTag = true;
			continue;
		}
		
				
		else if (tag == true)
		{
			testString += inputString[i];
			continue;
		}
		
		else if (tag == false)
		{
			testString += inputString[i];
			continue;
		}
		
		
	}
	

	return true;
}

// Then finish this function to pass unit tests 7-9
bool XMLParser::parseTokenizedInput()
{
	// TODO
	// Iterate through tokenizedInputVector to check its validity
	// and update the stack and bag accordingly, and refer to the following code structure:

	// for (int i = 0; i < tokenizedInputVector.size(); i++)
	// {
	//   if (?? == START_TAG) {?? continue;}
	//   else if (?? == END_TAG) {?? continue;}
	//   else if (?? == EMPTY_TAG) {?? continue;}
	//   ...
	// }

	return false;
}

void XMLParser::clear()
{
	// TODO
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &element) const
{
	// TODO
	return false;
}

int XMLParser::frequencyElementName(const std::string &element) const
{
	// TODO
	// Throw std::logic_error if either tokenizeInputString()
	// or parseTokenizedInput() returns false
	// If Bag is updated correctly, this should be as simple as one line.

	return -1;
}