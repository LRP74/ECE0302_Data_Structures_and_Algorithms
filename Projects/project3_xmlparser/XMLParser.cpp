/** @file XMLParser.cpp */

#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include "XMLParser.hpp"


XMLParser::XMLParser()
{
	isParsed = false;
}


bool XMLParser::tokenizeInputString(const std::string &inputString)
{
    // clear previous tokenization results and reset isParsed state
    tokenizedInputVector.clear();
    isParsed = false;

    bool inTag = false;       // tracks if we are currently inside < >
    std::string testString = ""; 

    for (int i = 0; i < inputString.length(); i++)
    {
		//**********************************************************************************//
		//							Checking < cases
		//**********************************************************************************//

        if (inputString[i] == '<')
        {
            // if inTag is already true, we have nested < like <<...> which is invalid
            if (inTag) return false;

            // anything accumulated in testString before this < is content
            // but only save it if it contains non-whitespace characters
            if (!testString.empty())
            {
                size_t firstNonSpace = testString.find_first_not_of(" \t\n\r");
                if (firstNonSpace != std::string::npos)
                {
                    std::string trimmed = testString.substr(firstNonSpace);
                    tokenizedInputVector.push_back({CONTENT, trimmed});
                }
            }
            testString = ""; 
            inTag = true;    // now inside tag
        }

		//**********************************************************************************//
		//							Checking > cases
		//**********************************************************************************//

        else if (inputString[i] == '>')
        {
            // if inTag is false then we have a > with no opening < which is invalid
            if (!inTag) return false;
            inTag = false;

            // empty tag name like <> is invalid
            if (testString.empty()) return false;

            // check if it is a declaration and starts and ends with ?
            if (testString[0] == '?' && testString.back() == '?')
            {
                // strip the leading and trailing ? and store as DECLARATION
                tokenizedInputVector.push_back({DECLARATION, testString.substr(1, testString.length() - 2)});
            }
            else
            {
                // check full testString for trailing / BEFORE stripping at space
                // this handles cases like <empty src="f"/> where space comes before /
                bool isEmptyTag = (testString.back() == '/');

                // extract tag name by taking everything before the first space
                // this strips attributes like src="f" from the tag name
                std::string tagName = testString.substr(0, testString.find(' '));

                if (tagName.empty()) return false;

                // catch tags like </tag.../> that are both end and empty
                if (isEmptyTag && tagName[0] == '/') return false;

                if (tagName[0] == '/')
                {
                    // END_TAG — strip the leading / and validate the name
                    // example </test> tagName becomes "test"
                    tagName = tagName.substr(1);
                    if (!isValidTagName(tagName)) return false;
                    tokenizedInputVector.push_back({END_TAG, tagName});
                }
                else if (isEmptyTag)
                {
                    // EMPTY_TAG — strip the trailing / and validate the name
                    // example <empty/> tagName becomes "empty"
                    if (tagName.back() == '/')
                        tagName = tagName.substr(0, tagName.length() - 1);
                    if (!isValidTagName(tagName)) return false;
                    tokenizedInputVector.push_back({EMPTY_TAG, tagName});
                }
                else
                {
                    // START_TAG — validate the name and store
                    // example <test> or <Note src="gmail"> tagName is "test" or "Note"
                    if (!isValidTagName(tagName)) return false;
                    tokenizedInputVector.push_back({START_TAG, tagName});
                }
            }
            testString = "";
        }
        else
        {
            // any other character just gets put into testString
            testString += inputString[i];
        }
    }

    // if inTag is still true, we had an unclosed < with no matching >
    if (inTag) return false;

    // if nothing was tokenized, the input had no valid tags
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
	if (testString.empty() == true) return false;
	if (isalpha(testString[0]) == 0 && testString[0] != '_') return false;

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
    // can't parse if nothing was tokenized
    if (tokenizedInputVector.empty()) return false;

    // tracks whether we have seen the root element yet
    // used to catch multiple root elements like <a></a><b></b> which is invalid
    bool rootFound = false;

    for (int i = 0; i < tokenizedInputVector.size(); i++)
    {
        if (tokenizedInputVector[i].tokenType == START_TAG)
        {
            // if stack is empty and we already found a root, this is a second root so invalid
            if (parseStack.isEmpty() && rootFound) return false;

            // push the tag name onto the stack so it is now "open". waiting for a matching end tag
            // also add to the bag so we can look it up later with contains/frequency
            parseStack.push(tokenizedInputVector[i].tokenString);
            elementNameBag.add(tokenizedInputVector[i].tokenString);
            rootFound = true;
            continue;
        }
        else if (tokenizedInputVector[i].tokenType == END_TAG)
        {
            // if stack is empty there is no open tag to close so invalid
            if (parseStack.isEmpty()) return false;

            // the end tag must match the most recently opened tag (top of stack)
            // example <a><b></b></a> is valid, <a><b></a></b> is not
            if (parseStack.peek() != tokenizedInputVector[i].tokenString) return false;

            // matched so pop the open tag off the stack
            parseStack.pop();
            continue;
        }
        else if (tokenizedInputVector[i].tokenType == EMPTY_TAG)
        {
            // if stack is empty and root was already found this is a second root so invalid
            // empty tags count as a root element if they appear at the top level
            if (parseStack.isEmpty() && rootFound) return false;

            // empty tags open and close themselves so no push/pop needed
            // just add to the bag so we can look it up later
            elementNameBag.add(tokenizedInputVector[i].tokenString);
            rootFound = true;
            continue;
        }
        else if (tokenizedInputVector[i].tokenType == DECLARATION)
        {
            // declarations like <?xml version="1.0"?> are only valid before the root element
            // if the stack is not empty, we are already inside an element so invalid
            if (!parseStack.isEmpty()) return false;
            continue;
        }
        else if (tokenizedInputVector[i].tokenType == CONTENT)
        {
            // content outside of any open tag is invalid
            // if stack is empty there is no enclosing element so invalid
            if (parseStack.isEmpty()) return false;
            continue;
        }
    }

    // if stack is not empty, some tags were never closed so invalid
    if (!parseStack.isEmpty()) return false;

    // everything passed
    isParsed = true;
    return true;
}

void XMLParser::clear()
{
	elementNameBag.clear();
	parseStack.clear();
	tokenizedInputVector.clear();
	isParsed = false;
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