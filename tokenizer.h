#pragma once
#include "utility.h"

class Tokenizer
{
private:
std::fstream input;

public:
void clearWhiteSpaces();
Tokenizer(std::string fileName);
bool hasTokens() {return (input.peek() != -1);}  // -1 is end of file
Token getToken();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

};


