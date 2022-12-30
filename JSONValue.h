#pragma once
#include "utility.h"





class JSONValue;
using JSONObject = std::map<std::string,JSONValue*>;
using JSONArray = std::vector<JSONValue*>;


class JSONValue
{
private:

enum ValueType
{
    NULL_VALUE = -1,
    OBJECT,
    ARRAY,
    STRING,
    NUMBER,
    BOOL,
};

ValueType type;

JSONObject* object;
JSONArray* array; 
std::string str;
float num;
bool bool_val;



public:
JSONValue() {
    object = nullptr;
    array = nullptr;
    str = "";
    num = 0.00;
    bool_val = false;
}


JSONValue& operator=(const JSONValue& other)
{
    if(this != &other)
    {
        //delete 

        type = other.type;
        object = other.object;
        array = other.array;
        str = other.str;
        num = other.num;
        bool_val = other.bool_val;

    }
    return *this;
}


JSONValue(ValueType t): type(t) {}

ValueType getType() {return type;}
JSONObject* getObject() {return object;}
JSONArray* getArray() {return array;}

void setArray(JSONArray* arr)
{

  type = ValueType::ARRAY;
    array = arr;
}

void setObject(JSONObject* obj)
{
    type = ValueType::OBJECT;
    this->object = obj;
}
void setStr(const std::string& str)
{
    type = ValueType::STRING;
    this->str = str;
}
void SetNumber(const float& number)
{
    type = ValueType::NUMBER;
    this->num = number;
}
void setBool(const bool& val)
{
    type = ValueType::BOOL;
    this->bool_val = val;
}

void setNull()
{
    type = ValueType::NULL_VALUE;
}



void print(int indentation)
{
std::string spacing( indentation ,'\t');


  switch(type)
  {
    case ValueType::NUMBER : 
    {
        std::cout<< num;
        break;
    }

    case ValueType::BOOL : 
    {
        bool_val == true ? std::cout<<"true" : std::cout<<"false";
        break;
    }
    case ValueType::STRING : 
    {
        std::cout<< str;
        break;
    }
    case ValueType::NULL_VALUE : 
    {
       std::cout<<"null";
       break;
    }
    case ValueType::OBJECT : 
    {

        // iterate through map, cout { , cout key,,cout : and call print for each jsonValue
        std::cout<< spacing <<"{\n";
        for (auto i = object->begin(); i != object->end(); i++)
        {
            std::cout<<spacing<<i->first<<" : "; // prints the key
            i->second->print( indentation ); // gets the jsonvalue from the map
            std::cout<<',';
        }
        std::cout<< spacing <<"},\n";

        break;
    }
    case ValueType::ARRAY : 
    {
        std::cout<< spacing <<"[\n";
        //iterate through array and call print for each jsonValue
        for (int i = 0; i < array->size(); i++)
        {
            (*array)[i]->print( indentation + 1);
            std::cout<<"\n";
                    }
        std::cout<< spacing <<']';

        break;
    }
  }
}

//print json tree recursively

 };



