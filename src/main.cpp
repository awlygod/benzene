//#include "lexer.h"

// These are the header files
#include<iostream>
#include<stdio.h>
#include<String>
#include<vector>
#include<unordered_map>
// Here basically we r defining the token types like various types of tokens the lexer can identify
 typedef enum
{
    TOKEN_INSERT,
    TOKEN_INTO,
    TOKEN_STRING, // This would be for the name of the db and stuff
    TOKEN_VALUE,
    TOKEN_DELETE,
    TOKEN_SEARCH,
    TOKEN_IN,
    TOKEN_INTEGER,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_COMMA

 } TOKEN_SET;

// Here we are defining the structure of the token
 struct TOKEN {
  TOKEN_SET TOKEN_TYPE; // Type of the token 
  std::string VALUE; // The actual string from the input (e.g, "INSERT", "table_name")
 };

 std::string tokenTypeToString(TOKEN_SET REQUIRED_TOKEN) {
  switch (REQUIRED_TOKEN)
  {
  case TOKEN_INSERT        : return "TOKEN_INSERT";
  case TOKEN_INTO          : return "TOKEN_INTO";
  case TOKEN_STRING        : return "TOKEN_STRING";
  case TOKEN_VALUE         : return "TOKEN_VALUE";
  case TOKEN_DELETE        : return "TOKEN_DELETE";
  case TOKEN_IN            : return "TOKEN_IN";
  case TOKEN_SEARCH        : return "TOKEN_SEARCH";
  case TOKEN_INTEGER       : return "TOKEN_INTEGER";
  case TOKEN_LEFT_PAREN    : return "TOKEN_LEFT_PAREN";
  case TOKEN_RIGHT_PAREN   : return "TOKEN_RIGHT_PAREN";   
  case TOKEN_COMMA         : return "TOKEN_COMMA";
  }
    return " [!] ERROR: UNIDENTIFIED TOKEN : " + REQUIRED_TOKEN;
 }
std::unordered_map< std::string, TOKEN_SET> KEYWORD_MAP = {
  {"insert",      TOKEN_INSERT},
  {"into",        TOKEN_INTO},
  {"string",      TOKEN_STRING},
  {"value",       TOKEN_VALUE },
  {"delete",      TOKEN_DELETE},
  {"in",          TOKEN_IN},
  {"search",      TOKEN_SEARCH},
  {"integer",     TOKEN_INTEGER},
  {"left_paren",  TOKEN_LEFT_PAREN},
  {"right_paren", TOKEN_RIGHT_PAREN},

  

};
// Lexer class basically processes the input string, identifies tokens, and stores them in a list.
class Lexer {

 private:
 int cursor; // Current position in the input string 
 int length; // Length of the input string
 char current; // The current character being processed 
 std::string LocalInputBuffer; // Stores the input String
 std::vector <TOKEN *> TOKEN_LIST; // Stores the identified tokens

 char advance() { 
  // Moves the cursor to the next character in the input string 
      if(cursor == length - 1)// this means that we are at the end of the input buffer
        {
          current = '\0';
          return current;
        }
      else
        {
          current = LocalInputBuffer[++cursor];
          return current;
        }
 }

 void skipWhiteSpaces() { 
  // Skips the spaces in the input string
  while (current ==' ' && current != '\0')
  {
    advance();
  }
 }

 TOKEN *tokenizeALPHA(){ 
  // Identifies the tokens made of alphabetic characters(like INSERT or table_name)

  TOKEN * newToken = new TOKEN;
  std::string temporaryBuffer = ""; // Collects the characters into temporaryBuffer until a non-alphabetic character is found
  while (isalpha(current) || current == '_')
  {
    temporaryBuffer.push_back(current); // Pushing this into buffer 
    advance();
  }
  newToken->TOKEN_TYPE = TOKEN_STRING; // Identifying this token  as string
  newToken->VALUE = temporaryBuffer;  // Storing the value from temporary buffer
  
  return newToken;
 }

 TOKEN *tokenizeINTEGER() { 
  TOKEN * newToken = new TOKEN;
  std::string temporaryBuffer = "";
  while (isdigit(current)){
    temporaryBuffer.push_back(current);
    advance();
  }
  newToken->TOKEN_TYPE = TOKEN_INTEGER;
  newToken->VALUE = temporaryBuffer;

  return newToken;
 }
 void displayAllToken(){
  // Displays all tokens in TOKEN_LIST with their type and value for debugging purposes

  int counter = 0;
  for(TOKEN * CURRENT_TOKEN : TOKEN_LIST) 
  {
    std::cout << ++counter << ") "<< CURRENT_TOKEN ->VALUE<<" ";
    std::cout<< tokenTypeToString (CURRENT_TOKEN->TOKEN_TYPE) << std::endl;

  }
 }
 TOKEN * tokenizeSPECIAL (TOKEN_SET NEW_TOKEN_TYPE){
  TOKEN * newToken = new TOKEN;
  newToken->TOKEN_TYPE = NEW_TOKEN_TYPE;
  newToken->VALUE = current;

  advance();
  return newToken;

 }
 public: 
 Lexer() {

 } 
 void initialize(std::string InputBuffer) {
  cursor = 0;
  length = InputBuffer.size();
  LocalInputBuffer = InputBuffer;
  current = LocalInputBuffer[cursor];
 }
 void tokenize(){
    
    while(current !='\0') {
      skipWhiteSpaces();
      if (isalpha(current || current == '_'))
      {
        TOKEN_LIST.push_back(tokenizeALPHA());
      }
      else if(isdigit(current)){
        TOKEN_LIST.push_back(tokenizeINTEGER());
      }
      switch (current)
      {
          case '(':
          {
            TOKEN_LIST.push_back(tokenizeSPECIAL(TOKEN_LEFT_PAREN));
          }
          case ')':
          {
            TOKEN_LIST.push_back(tokenizeSPECIAL(TOKEN_RIGHT_PAREN));
          }
          case ',':
          {
            TOKEN_LIST.push_back(tokenizeSPECIAL(TOKEN_COMMA));
          }
          default:
          std::cout << "[!] LEXER ERROR : UNIDENTIFIED CHARACTER: "<< current << std::endl;
          exit(0);
          
      }
      
    } 

    displayAllToken();

 }


};

 class EvaluationWrapper {
    private:
    Lexer * MAIN_LEXER;

    public:
    EvaluationWrapper()
    {
          MAIN_LEXER = new Lexer();
    }

    void handle (std::string InputBuffer) 
    {

    MAIN_LEXER->initialize(InputBuffer);  
    MAIN_LEXER->tokenize();
   
    }
 };


int main () {
    std::string InputBuffer; // we might make a class of its own in future
    EvaluationWrapper * main_io = new EvaluationWrapper();

    while (true)
    {
    std::cout<< "db_benzene : ";
    std::getline(std::cin, InputBuffer);
    main_io->handle(InputBuffer);

    }
    return 0;
} 