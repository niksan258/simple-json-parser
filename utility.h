#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>



bool isWhite(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c=='\t';
}

bool isNumber(char c)
{
    return ((c >= '0') && (c <= '9')) || c == '-';
}

void move_cursor(std::fstream& input,int n)
{
   for (size_t i = 0; i < n; i++)
   {
    input.get();
   } 
}

std::vector<std::string> tokenizeString(std::string input)
{

    char* input_chars = new char[input.length() + 1];
    strcpy(input_chars,input.c_str());
    const char* delimiter = "/";

    std::vector<std::string> tokenizedString;
 
    char* token = strtok(input_chars,delimiter);

    while(token != nullptr)
    {
       tokenizedString.push_back(token);
       token = strtok(nullptr,delimiter);
    }

  return tokenizedString;
}

enum TOKEN_TYPE
{
    NULL_TOKEN = -1,
    CURLY_OPEN,
    CURLY_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE,
    COLON,
    COMMA,
    STRING,
    NUMBER,
    BOOL,
    NULL_VALUE,

};

struct Token
{
    TOKEN_TYPE type;
    std::string val;
    Token(): type(NULL_TOKEN),val("") {}
    Token(TOKEN_TYPE t) : type(t),val("") {}
    Token(TOKEN_TYPE t,std::string v) : type(t),val(v) {}

    std::string toString()
    {
        switch (type)
        {
        case -1:
        {
            return "Null Token!";
        }            
        case 0:
        {
            return "Curly open";
        }
        case 1:
        {
            return "Curly close";
        }            
        case 2:
        {
            return "Array open";
        }
        case 3:
        {
            return "Array close";
        }
        case 4:
        {
            return "COLON";
        }        
        case 5:
        {
            return "Comma";
        }
        case 6:
        {
            return val;
        } 
        case 7:
        {
            return "Number: "+val;
        }               
        case 8:
        {
            return "Boolean: " + val;
        }    
        case 9:
        {
             return "Null value";
        }
        default: return "INVALID";
    }
    }
};


