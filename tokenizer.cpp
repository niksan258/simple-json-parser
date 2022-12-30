#include "tokenizer.h"



Tokenizer::Tokenizer(std::string fileName)
{
    input.open(fileName,std::ios::in);
    if(!input.is_open())
    {
      throw std::runtime_error("File couldn't be opened.");
    }
}

void Tokenizer::clearWhiteSpaces()
{
    while(isWhite(input.peek()))
    {
        char c = input.get();
    }
}

Token Tokenizer::getToken()
{

  if(!hasTokens())
  {
   throw std::out_of_range("No tokens!");
  }

  clearWhiteSpaces();
  char c = input.get();

  
  switch(c)
  {
    case '{' : return Token(CURLY_OPEN); break;
    case '}' : return Token(CURLY_CLOSE); break;
    case '[' : return Token(SQUARE_OPEN); break;
    case ']' : return Token(SQUARE_CLOSE); break;
    case ':' : return Token(COLON); break;
    case ',' : return Token(COMMA); break;

    case 'f' : move_cursor(input,4); 
    return Token(BOOL,"false"); break; 

    case 't' : move_cursor(input,3);
    return Token(BOOL,"true"); break;

    case 'n' : move_cursor(input,3);
    return Token(NULL_VALUE); break;
  } 
   
   
  Token token;
  if(c == '"') // string 
  {

    token.type = TOKEN_TYPE::STRING;
    input.get(c);
    while(c!='"')
    {
        token.val += c;
        input.get(c);
    }

  }

  else if(isNumber(c))
  {
    token.type = TOKEN_TYPE::NUMBER;
    token.val += c;
    while(isNumber(input.peek()) || input.peek() == '.')
    {
         input.get(c);
        token.val+=c;
    }
   }

  return token;
}                          

