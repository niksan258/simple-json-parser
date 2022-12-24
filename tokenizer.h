#pragma once
#include "utility.h"

#include <iostream>
#include <cstring>
#include <fstream>

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
        case CURLY_OPEN:
        {
            return "Curly open";
        }
        case CURLY_CLOSE:
        {
            return "Curly close";
        }
        case COLON:
        {
            return "COLON";
        }
        case NUMBER:
        {
            return "Number: "+val;
        }
        case STRING:
        {
            return "String: "+val;
        }

        case SQUARE_OPEN:
        {
            return "Array open";
        }
        case SQUARE_CLOSE:
        {
            return "Array close";
        }
        case COMMA:
        {
            return "Comma";
        }
        case BOOL:
        {
            return "Boolean: " + val;
        }

        case NULL_TOKEN:
        {
            return "Null Token";
        }
               
        
    }
    }
};


class Tokenizer
{
private:
std::fstream input;

public:
void clearWhiteSpaces();
Tokenizer(std::string fileName);
bool hasTokens() {return !input.eof();} 
Token getToken();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

};


