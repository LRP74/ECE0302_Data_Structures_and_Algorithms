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

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
    tokenizedInputVector.clear();
    
    bool inTag = false;
    std::string testString = "";

    for (int i = 0; i < inputString.length(); i++)
    {
        if (inputString[i] == '<')
        {
            if (inTag) return false;
            if (!testString.empty())
            {
                tokenizedInputVector.push_back({CONTENT, testString});
            }
            testString = "";
            inTag = true;
        }
        else if (inputString[i] == '>')
        {
            if (!inTag) return false;
            inTag = false;
            
            if (testString.empty()) return false;
            
            if (testString[0] == '?' && testString.back() == '?')
            {
                // DECLARATION - use full testString, no space stripping
                tokenizedInputVector.push_back({DECLARATION, testString.substr(1, testString.length() - 2)});
            }
            else
            {
                // strip at first space to get tag name only
                std::string tagName = testString.substr(0, testString.find(' '));
                
                if (tagName.empty()) return false;
                
                if (tagName[0] == '/')
                {
                    // END_TAG - strip the leading /
                    tagName = tagName.substr(1);
                    if (!isValidTagName(tagName)) return false;
                    tokenizedInputVector.push_back({END_TAG, tagName});
                }
                else if (tagName.back() == '/')
                {
                    // EMPTY_TAG - strip the last /
                    tagName = tagName.substr(0, tagName.length() - 1);
                    if (!isValidTagName(tagName)) return false;
                    tokenizedInputVector.push_back({EMPTY_TAG, tagName});
                }
                else
                {
                    // START_TAG
                    if (!isValidTagName(tagName)) return false;
                    tokenizedInputVector.push_back({START_TAG, tagName});
                }
            }
            testString = "";
        }
        else
        {
            testString += inputString[i];
        }
    }
    
    if (inTag) return false;
    if (tokenizedInputVector.empty()) return false;
    return true;
}

bool XMLParser::isValidTagName(const std::string &testString)
{
	/*
	 Return false if string is empty
 	 Check first character — return false if it is NOT a-z, A-Z, or _
	 Loop through remaining characters (index 1 onwards) — return false if any character is NOT a-z, A-Z, 0-9, _, -, or .
 	 Return true if all checks passed
	*/
	if (testString.empty() == true)
	{
		return false;
	}

	if (isalpha(testString[0]) == 0 && testString[0] != '_')
	{
		return false;
	}

	for (int i = 1; i < testString.length(); i++)
	{
		if (isalpha(testString[i]) == 0 && isdigit(testString[i]) == 0 && testString[i] != '_' && testString[i] != '-' && testString[i] != '.')
		{			
			return false;
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