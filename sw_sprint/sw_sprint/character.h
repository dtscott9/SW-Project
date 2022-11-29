#pragma once
#include<iostream>
#include<string>
#include <json/json.h>
#include <json/value.h>
using namespace Json;
using namespace std;

class character
{
private:
	Value name;
	Value id;
	Value species;
	Value gender;
	Value homeWorld;
public:
	character(Value name, Value id, Value species, Value gender, Value homeWorld);
	void displayInfo();
};

