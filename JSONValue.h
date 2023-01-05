#pragma once
#include "utility.h"






class JSONValue;
using JSONObject = std::map<std::string,    JSONValue*>;
//using JSONObject = std::map<std::string,JSONValue*>;
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
    bool_val = 0;
}


// JSONValue& operator=(const JSONValue& other)
// {
//     if(this != &other)
//     {
//         this->type = NULL_VALUE;
//         delete this->object;
//         delete this->array;

//         std::cout<<this->num;
    

//         this->type = other.type;
//         object = other.object;
//         array = other.array;
//         str = other.str;
//         this->num = other.num;
//         bool_val = other.bool_val;

//     }
//     return *this;
// }


JSONValue(ValueType t): type(t) {}

ValueType getType() {return type;}
JSONObject* getObject() {return object;}
JSONArray* getArray() {return array;}
std::string getStr() {return str;}
float getNumber() {return num;}
bool getBool() {return bool_val;}

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



void print(std::ostream& output, int indentation)
{
std::string spacing( indentation ,'\t');


  switch(type)
  {
    case ValueType::NUMBER : 
    {
        output << num;  
        break;
    }

    case ValueType::BOOL : 
    {
        bool_val == true ? output<<spacing<<"true" : output<<spacing<<"false";
        break;
    }
    case ValueType::STRING : 
    {
        output<< spacing <<'"'<< str << '"';
        break;
    }
    case ValueType::NULL_VALUE : 
    {
       output<< spacing <<"null";
       break;
    }
    case ValueType::OBJECT : 
    {

       unsigned int counter = 1;
        // iterate through map, cout { , cout key,,cout : and call print for each jsonValue
        output<< spacing <<"{\n";

        for (auto i = object->begin(); i != object->end(); i++)
        {
            output<<spacing<< '"' << i->first<< '"' <<" : "; // prints the key
            i->second->print(output, indentation); // gets the jsonvalue from the map
            
           if(counter > object->size() -1 )
           {
            output<<'\n';
           } else 
           {
            output<<",\n";
           }

           counter++;
        }
        output<< spacing <<"}";

        break;
    }
    case ValueType::ARRAY : 
    {
        unsigned int counter = 1;

        output<< spacing <<"[\n";
        //iterate through array and call print for each jsonValue
        for (int i = 0; i < array->size(); i++)
        {
            (*array)[i]->print(output, indentation + 1);
           if(counter > array->size() -1 )
           {
            output<<'\n';
           } else 
           {
            output<< spacing <<",\n";
           }

           counter++;
                    }
        output<< spacing <<']';

        break;
    }
  }
}


 };




