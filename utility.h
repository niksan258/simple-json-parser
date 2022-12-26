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
            return "String: "+val;
        } 
        case 7:
        {
            return "Number: "+val;
        }               
        case 8:
        {
            return "Boolean: " + val;
        }    
        default: return "INVALID";
    }
    }
};


