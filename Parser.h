#pragma once
#include "utility.h"
#include "tokenizer.h"
#include "JSONValue.h"

// Tokenizer k;

class Parser
{
private:
  std::ifstream input;
  JSONValue *root{};
  Tokenizer t;
  Token token;

public:
  Parser(std::string fileName) : t(fileName) {}

  JSONValue *getroot() { return root; }



  void save(const std::string &fileName)
  {
    std::ofstream output(fileName);
    if (!output.is_open())
    {
      throw std::runtime_error("File for writing couldn't be opened");
    }

    root->print(output, 0);

    output.close();

    std::cout << "File saved.";
  }




  void createObject(std::string path, std::string value)
  {

    std::vector<std::string> pathTokens = tokenizeString(path);

    JSONObject *map = new JSONObject;

    std::ofstream out("tempValue.json");
    out << value;
    out.close();

    Parser valueParser("tempValue.json");
    valueParser.parse();


    std::string objectKey = pathTokens[pathTokens.size() - 1]; // gets last element from path

    if(pathTokens.size() == 1)
    {
    (*root->getObject())[objectKey] = valueParser.getroot();
    } 
    else 
    {
      findElemWithPath(root, pathTokens, 0, map);
      if(map->count(objectKey)==1)  throw std::runtime_error("Object already exists");
      (*map)[objectKey] = valueParser.getroot();
    }

  }



  void replaceJSON(std::string path, std::string value)
  {
    std::vector<std::string> pathTokens = tokenizeString(path);

    JSONObject *map = new JSONObject;


    findElemWithPath(root, pathTokens, 0, map);

    std::ofstream out("tempValue.json");
    out << value;
    out.close();

    Parser valueParser("tempValue.json");
    valueParser.parse();


    std::string objectKey = pathTokens[pathTokens.size() - 1]; // gets last element from path
    if(map->count(objectKey)==0)  throw std::runtime_error("Object not found");
    
    JSONValue* result = map->at(objectKey); // gets wanted element from tha map

    JSONValue *newValue = valueParser.getroot();
    switch (newValue->getType())
    {
    case -1:
      result->setNull();
      break;
    case 0:
      result->setObject(newValue->getObject());
      break;
    case 1:
      result->setArray(newValue->getArray());
      break;
    case 2:
      result->setStr(newValue->getStr());
      break;
    case 3:
      result->SetNumber(newValue->getNumber());
      break;
    case 4:
      result->setBool(newValue->getBool());
      break;
    }
  }



  void findElemWithPath(JSONValue *currRoot, std::vector<std::string> tokens, int counter, JSONObject *&result)
  {
    if (root->getType() == 0) // object
    {
      JSONObject *map = currRoot->getObject();
      bool found = false;

      for (auto i = map->begin(); i != map->end(); i++)
      {
        //if(counter <= tokens.size() -1 )

        if ((*i).first == tokens[counter])
        {
          if(tokens.size() == 1) 
          {
            result = map;
            return;
          }

          found = true;
          if (counter == tokens.size() - 2) // < bcs case with 1 element crashes
          {
            //result = i->second;
            result = (*i).second->getObject();
            return;
          }
          findElemWithPath((*i).second, tokens, counter + 1, result);
        }
      }

      if (found == false)
      {
        throw std::out_of_range("Invalid path");
      }
    }
  }

  // replace function with given path and key

  // find elements with given key in the json tree
  std::vector<JSONValue *> find(std::string key)
  {
    std::vector<JSONValue *> result;
    find_helper(root, key, result);
    return result;
  }

  // find helper function
  void find_helper(JSONValue *root, std::string key, std::vector<JSONValue *> &result)
  {
    if ((*root).getType() == 0)

    {
      JSONObject *map = (*root).getObject();
      for (auto i = (*map).begin(); i != (*map).end(); i++)
      {
        if ((*i).first == key)
        {
          result.push_back((*i).second);
        }
        else
        {
          find_helper((*i).second, key, result);
        }
      }
    }

    if ((*root).getType() == 1)
    {
      JSONArray *arr = (*root).getArray();
      for (auto i = (*arr).begin(); i != (*arr).end(); i++)
      {
        find_helper((*i), key, result);
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
    input.close();
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
        // map->push_back(std::make_pair(key,parseObject()));
        (*map)[key] = parseObject(); // insert element in map
        /* code */
        break;
      case STRING:
        // map->push_back(std::make_pair(key,parseString()))
        (*map)[key] = parseString();
        /* code */
        break;
      case SQUARE_OPEN:
        // map->push_back(std::make_pair(key,parseArray()));
        (*map)[key] = parseArray();
        /* code */
        break;
      case NUMBER:
        // map->push_back(std::make_pair(key,parseNum()));
        (*map)[key] = parseNum();
        /* code */
        break;
      case BOOL:
        // map->push_back(std::make_pair(key,parseBool()));
        (*map)[key] = parseBool();
        break;
      case NULL_VALUE:
        // map->push_back(std::make_pair(key,parseNullVal()));
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

    JSONValue *result = new JSONValue;
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
