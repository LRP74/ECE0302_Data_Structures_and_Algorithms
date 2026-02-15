#include <string>
#include <iostream>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(std::string s, int last)
{
  char ch = s[last];
  if (isalpha(ch))
  {
    return last; // if char at "last" is an operand, then itself is a valid postfix expression,
                 // so the end ("start" idx from left to right) of the postfix expression is just "last"
  }
  else if (isoperator(ch)) // make sure that ch is an operator, otherwise it is an invalid character and should return -1
  {
    int lastEnd = endPost(s, last - 1); // search for the end ("start" idx from left to right)
                                        // of the first <postfix> before ch in the syntax <postfix> <postfix> ch
    if (lastEnd > -1)
    {
      return endPost(s, lastEnd - 1); // search for the end ("start" idx from left to right)
                                      // of the second <postfix> before ch in the syntax <postfix> <postfix> ch
    }
    return -1;
  }
  return -1;
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.size() - 1);
  return (firstChar == 0);
  // A postfix expression is valid if and only if the entire string
  // forms a single valid postfix expression (i.e., starts at index 0)
}

void convert(const std::string &postfix, std::string &prefix)
{
  // TODO convert postfix to prefix and store the result in prefix

  // Check if the input postfix expression is valid; 
  if (isPost(postfix) == false)
  {
    throw std::invalid_argument("Invalid postfix expression: " + postfix);
  }

  //The given input postfix expression should be purely symbolic (e.g., "ab+", not "13+") (From the project description)
  //Iterate through the characters and check if each character is an operand or an operator; throw exeptions for invalid characters
  for (int i = 0; i < postfix.size(); i++)
  {
    char character = postfix[i];
    if (!isalpha(character) && !isoperator(character))
    {
      throw std::invalid_argument("Invalid character in postfix expression: " + std::string(1, character));
    }
  }


  //recursively convert the postfix expression to prefix
  int lastIndex = postfix.size() - 1;
  char lastChar = postfix[lastIndex];
  // If the last character is an operand, then the prefix expression is just that operand.
  if (isalpha(lastChar))
  {
    prefix = lastChar; // if the last character is an operand, then the prefix expression is just that operand
  }
  // if the last character is an operator, then we need to find the two expressions before it
  // and then recursively convert them to prefix
  // then combine the operator and the two prefix expressions to form the final prefix expression
  else if (isoperator(lastChar))
  {
    int firstStart = endPost(postfix, lastIndex); // get the start index of the first postfix
    int secondStart = endPost(postfix, lastIndex - 1); // get the start index of the second postfix
    std::string firstPostfix = postfix.substr(firstStart, secondStart - firstStart); // get the first postfix
    std::string secondPostfix = postfix.substr(secondStart, lastIndex - secondStart); // get the second postfix
    std::string firstPrefix = ""; // initialize the prefix expression for the first postfix
    std::string secondPrefix = ""; // initialize the prefix expression for the second postfix
    convert(firstPostfix, firstPrefix); // recursively convert the first postfix to prefix
    convert(secondPostfix, secondPrefix); // recursively convert the second postfix to prefix
    prefix = lastChar + firstPrefix + secondPrefix; // combine the operator and the two prefix expressions to form the final prefix expression
  }

}
  