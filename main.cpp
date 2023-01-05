#include "tokenizer.h"
#include "tokenizer.cpp"
#include "Parser.cpp"
#include "Parser.h"


int main()
{
   // Tokenizer t("test.json");
    Parser p("test.json");



    // JSONValue* v1 = new JSONValue;
    // JSONValue* v2 = new JSONValue;
    // JSONValue* v3 = new JSONValue;
    // JSONValue* v4 = new JSONValue;
    // v2->setStr("test 1");
    // v3->setStr("test 2");
    // v4->setStr("test 3");

    // JSONArray* t = new JSONArray;
    // (*t).push_back(v2);
    // (*t).push_back(v3);
    // (*t).push_back(v4);




    // v1->setArray(t);

    // v1->print();

    

    p.parse();

  //  std::vector<JSONValue*> result;

    p.replaceJSON("pokemon/candy_count","[true,false]");

    p.getroot()->print(std::cout,0);
 //   p.createObject("","6868");

  //   JSONValue* result = new JSONValue();
   //  p.replace("pokemon/",0)->print(0);
     
 //  p.getroot()->print(std::cout,0);
 p.save("output.json");


    //  p.replace("pokemon","{}")->print(0);

      //quiz/maths/q1/options/3





    // result = p.find("weaknesses");


    //     std::cout<<"[\n";
    // for (size_t i = 0; i < result.size(); i++)
    // {   
    //     result[i]->print(0);
    //             std::cout<<',';
    //     std::cout<<std::endl;

    // }
    //         std::cout<<"]";
    


//    p.getroot()->print(0);


  
  

   //TODO
   //IMPLEMENT FIND
   //traverses whole file and stores vector of pointers to the json objects
   // have one more function to print json object pointer


    // while(t.hasTokens())
    // {
    //     std::cout<<t.getToken().toString()<<" "<<'\n';
    // }


    //TODO seperate parser in 2 files
    
}