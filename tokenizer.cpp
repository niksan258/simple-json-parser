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
        input.get();
    }
}

Token Tokenizer::getToken()
{
  clearWhiteSpaces();
  if(!hasTokens())
  {
    return Token{NULL_TOKEN,""};
  }

  char c = input.get();
  
  switch(c)
  {
    case '{' : return Token(CURLY_OPEN); break;
    case '}' : return Token(CURLY_CLOSE); break;
    case '[' : return Token(SQUARE_OPEN); break;
    case ']' : return Token(SQUARE_CLOSE); break;
    case ':' : return Token(COLON); break;
    case ',' : return Token(COMMA); break;
    case 'f' : input.seekg(4, std::ios::cur); return Token(BOOL,"false"); break;
    case 't' : input.seekg(4, std::ios::cur); return Token(BOOL,"true");  break;
    case 'n' : input.seekg(3,std::ios::cur); return Token(NULL_TOKEN); break;
  }

  Token token;
  if(c == '"') // string 
  {

    token.type = STRING;
    input.get(c);
    while(c!='"')
    {
        token.val += c;
        input.get(c);
    }

  }

  if(isNumber(c))
  {
    token.type = NUMBER;
    while(isNumber(c) || c=='.')
    {
        token.val+=c;
        input.get(c);
    }
   }

  return token;
}                          

