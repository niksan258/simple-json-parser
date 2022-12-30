#pragma once
#include "utility.h"
#include "tokenizer.h"
#include "JSONValue.h"

// Tokenizer k;

class Parser
{
private:
  std::fstream input;
  JSONValue *root{};
  Tokenizer t;
  Token token;

public:
  Parser(std::string fileName) : t(fileName) {}
   
  JSONValue* getroot() {return root;}

  JSONValue* replace(std::string path,std::string key)
  {
    std::vector<std::string> pathTokens
                = tokenizeString(path);

    JSONValue* result = new JSONValue;


    findElemWithPath(root,key,pathTokens,0,result);
    return result;
    //make function that checks map for 
    //current path and if it find continues
  }

  void findElemWithPath(JSONValue* currRoot,std::string name,std::vector<std::string> tokens,int counter,JSONValue*& result)
  {
    if(root->getType() == 0)
    {
      JSONObject* map = currRoot->getObject();
      bool found = false;
      
      for (auto i = map->begin(); i != map->end(); i++)
      {
        if((*i).first == tokens[counter])
        {
          found = true;
          if(counter == tokens.size() - 1)
          {
            result = i->second;
            return;
          }
           findElemWithPath((*i).second,name,tokens,counter + 1,result);
        }
      }

      if(found == false)
      {
        throw std::out_of_range("Invalid path");
      }
      
      
    }

 }

  //replace function with given path and key


// find elements with given key in the json tree
  std::vector<JSONValue*> find(std::string key)
  {
    std::vector<JSONValue*> result;
    find_helper(root,key,result);
    return result;
  }

//find helper function
  void find_helper(JSONValue* root,std::string key,std::vector<JSONValue*>& result)
  {
    if((*root).getType() == 0)

    {
    JSONObject* map = (*root).getObject();
    for (auto i = (*map).begin(); i != (*map).end(); i++)
    {
      if((*i).first == key)
      {
        result.push_back((*i).second);
      } else {
        find_helper((*i).second,key,result);
      }
    }
    }

    if((*root).getType() == 1)
    {
      JSONArray* arr = (*root).getArray();
      for (auto i = (*arr).begin(); i != (*arr).end(); i++)
      {
        find_helper((*i),key,result);
      }
    }


    return;

  }







  void parse()
  {

    JSONValue *parsedValue = new JSONValue();

    while (t.hasTokens())
    {
      token = t.getToken();

      switch (token.type)
      {
        {
        case TOKEN_TYPE::CURLY_OPEN:
          parsedValue = parseObject();
          break;
        }

      case TOKEN_TYPE::STRING:
      {
        parsedValue = parseString();
        break;
      }

      case TOKEN_TYPE::SQUARE_OPEN:
      {
        parsedValue = parseArray();
        break;
      }

      case TOKEN_TYPE::NUMBER:
      {
        parsedValue = parseNum();
        break;
      }

      case TOKEN_TYPE::BOOL:
      {
        parsedValue = parseBool();
        break;
      }

      case TOKEN_TYPE::NULL_VALUE:
      {
        parsedValue = parseNullVal();
        break;
      }
      }

      if (!root)
      {
        root = parsedValue;
      }
    }
  }

  // todo add parsers for object and array

  JSONValue *parseObject()
  {
    JSONValue *node = new JSONValue();
    JSONObject *map = new JSONObject();
    bool complete = false;

    while (!complete)
    {
      // if (!t.hasTokens())
      // {
      //   throw std::out_of_range("Invalid Object!");
      // }

      token = t.getToken(); // gets the key
      std::string key = token.val;
      t.getToken(); // removes the :
      std::cout << "Parsing Key: " << token.toString() << "  |  ";
      token = t.getToken();
      std::cout << "Parsing Value: " << token.toString() << '\n';

      switch (token.type)
      {
      case CURLY_OPEN:
        (*map)[key] = parseObject(); // insert element in map
        /* code */
        break;
      case STRING:
        (*map)[key] = parseString();
        /* code */
        break;
      case SQUARE_OPEN:
        (*map)[key] = parseArray();
        /* code */
        break;
      case NUMBER:
        (*map)[key] = parseNum();
        /* code */
        break;
      case BOOL:
        (*map)[key] = parseBool();
        break;
      case NULL_VALUE:
        (*map)[key] = parseNullVal();

        break;
      default:
        throw std::runtime_error("Object parse failed");
        break;
      }

      token = t.getToken(); // gets , or semicolon
      if (token.type == CURLY_CLOSE)
      {
        complete = true;
      }
    }

    node->setObject(map);
 //   std::cout << map->size();
    return node;
  }

  JSONValue *parseArray()
  {
    JSONValue *node = new JSONValue();
    JSONArray *arr = new JSONArray();
    bool complete = false;

    while (!complete)
    {
      token = t.getToken();
      std::cout << "ARRAY Parsing " << token.toString() << '\n';
      switch (token.type)
      {

      case CURLY_OPEN:
        node = parseObject();
        break;

      case SQUARE_OPEN:
        node = parseArray();
        break;

      case STRING:
        node = parseString();
        break;

      case NUMBER:
        node = parseNum();
        break;

      case BOOL:
        node = parseBool();
        break;

      case NULL_VALUE:
        node = parseNullVal();
        break;

      }

      token = t.getToken();

      if (token.type == SQUARE_CLOSE)
      {
        complete = true;
      }
      (*arr).push_back(node);

    }


  JSONValue* result = new JSONValue;
  result->setArray(arr);


    return result;
  }

  JSONValue *parseNullVal()
  {
    JSONValue *node = new JSONValue();
    node->setNull();
    return node;
  }

  JSONValue *parseBool()
  {
    JSONValue *node = new JSONValue();
    bool result = token.val == "true" ? true : false;
    node->setBool(result);
    return node;
  }

  JSONValue *parseString()
  {
    JSONValue *node = new JSONValue();
    node->setStr(token.val);
    return node;
  }

  JSONValue *parseNum()
  {
    JSONValue *node = new JSONValue();
    float num = std::stof(token.val);
    node->SetNumber(num);
    return node;
  }
};
