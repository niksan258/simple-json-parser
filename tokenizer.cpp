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
  // while(!input.eof())
  // {
  //    if(isWhite(input.peek()))
  //    {
  //    char c = input.get();
  //    }
  //    input.seekg(2,std::ios::cur);
  //    if(input.tellg() == -1)
  //    {
  //     break;
  //    }
     
  // }

  // input.clear();
  // input.seekg(0,std::ios::beg);
    while(isWhite(input.peek()))
    {
        char c = input.get();
    }
 // input.clear();
}

Token Tokenizer::getToken()
{
  //clearWhiteSpaces();
  // if(!hasTokens())
  // {
  //   std::cout<<"!!";
  //   return Token{NULL_TOKEN,""};
  // }

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
    case 'f' : 
    for (size_t i = 0; i < 4; i++)
    {
      c = input.get();
    }
    return Token(BOOL,"false"); 
    break; 


    case 't' :
    for (size_t i = 0; i < 3; i++)
    {
      c = input.get();
    }      
     return Token(BOOL,"true");
     break;


    case 'n' :
    for (size_t i = 0; i < 3; i++)
    {
      c = input.get();
    }    
    return Token(NULL_TOKEN); break;
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
    while(isNumber(input.peek()) || c=='.')
    {
         input.get(c);
        token.val+=c;
    }
   }

  return token;
}                          

