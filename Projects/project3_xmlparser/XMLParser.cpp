/** @file XMLParser.cpp */

#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include "XMLParser.hpp"


XMLParser::XMLParser()
{
	bool isParsed = false;
}

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
    tokenizedInputVector.clear();
	isParsed = false;
    
    bool inTag = false;
    std::string testString = "";

    for (int i = 0; i < inputString.length(); i++)
    {
        if (inputString[i] == '<')
        {
            if (inTag) return false;
            if (!testString.empty())
            {
				//ai helped me fix counting blank contents
				if (!testString.empty())
				{
					size_t firstNonSpace = testString.find_first_not_of(" \t\n\r");
					if (firstNonSpace != std::string::npos)
					{
						std::string trimmed = testString.substr(firstNonSpace);
						tokenizedInputVector.push_back({CONTENT, trimmed});
					}
				}
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
        // DECLARATION
        tokenizedInputVector.push_back({DECLARATION, testString.substr(1, testString.length() - 2)});
    }
    else
    {
        // check full testString for trailing / before space stripping
        bool isEmptyTag = (testString.back() == '/');
        
        // strip at first space to get tag name only
        std::string tagName = testString.substr(0, testString.find(' '));
        
        if (tagName.empty()) return false;
        
        if (tagName[0] == '/')
        {
            // END_TAG
            tagName = tagName.substr(1);
            if (!isValidTagName(tagName)) return false;
            tokenizedInputVector.push_back({END_TAG, tagName});
        }
		else if (isEmptyTag)
		{
			if (tagName[0] == '/') return false;  // can't be both end and empty
			if (tagName.back() == '/')
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
	if (tokenizedInputVector.empty())
		{
			return false;
		}
	
		bool rootFound = false;
	for (int i = 0; i < tokenizedInputVector.size(); i++)
	{	
		if(tokenizedInputVector[i].tokenType == START_TAG)
		{
			if (parseStack.isEmpty() && rootFound) return false; // second root!
			parseStack.push(tokenizedInputVector[i].tokenString);
			elementNameBag.add(tokenizedInputVector[i].tokenString);
			rootFound = true;
			continue;
		}
		else if (tokenizedInputVector[i].tokenType == END_TAG)
		{
			if (parseStack.isEmpty())
			{
				return false;
			}
			if (parseStack.peek() != tokenizedInputVector[i].tokenString)
			{
				return false;
			}
			
			
			parseStack.pop();	
			continue;
		}
		else if (tokenizedInputVector[i].tokenType == EMPTY_TAG)
		{
			elementNameBag.add(tokenizedInputVector[i].tokenString);
			continue;
		}
		else if (tokenizedInputVector[i].tokenType == DECLARATION)
		{
			continue;
		}
		else if (tokenizedInputVector[i].tokenType == CONTENT)
		{
		if (parseStack.isEmpty()) return false;
		continue;
		}
		
	}
	
	if (parseStack.isEmpty() == false)
	{
		return false;
	}
	
	isParsed = true;
	return true;
}

void XMLParser::clear()
{
	elementNameBag.clear();
	parseStack.clear();
	tokenizedInputVector.clear();
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &element) const
{
    if (!isParsed) 
	{
		throw std::logic_error("Input has not been tokenized and parsed");
	}
    return elementNameBag.contains(element);
}

int XMLParser::frequencyElementName(const std::string &element) const
{
	// TODO
	// Throw std::logic_error if either tokenizeInputString()
	// or parseTokenizedInput() returns false
	// If Bag is updated correctly, this should be as simple as one line.
	if (isParsed == false)
	{
		throw std::logic_error("Input has not been tokenized and parsed");
	}
	
	return elementNameBag.getFrequencyOf(element);
}