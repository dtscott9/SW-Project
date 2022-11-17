// sw_sprint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <json/value.h>
using namespace std;
using namespace Json;

int main()
{
    /*cout << "Hello World!\n";*/
    Reader reader;
    Value value;

    ifstream file("character.json");

    reader.parse(file, value);

    const Value newValue = value["name"];

    cout <<"Value is: \n" << value;
    
}
