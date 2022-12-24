#include "tokenizer.h"
#include "tokenizer.cpp"


int main()
{
    Tokenizer t("test.json");

    while(t.hasTokens())
    {
        std::cout<<t.getToken().toString()<<" "<<'\n';
    }
    
}