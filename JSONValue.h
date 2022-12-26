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
JSONValue() {}
JSONValue(ValueType t): type(t) {}

void setArray(JSONArray* arr)
{
    type = ValueType::ARRAY;
    this->array = arr;
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




};



