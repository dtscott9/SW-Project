// sw_sprint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <json/value.h>
#include "character.h"
using namespace std;
using namespace Json;

void displayCharList(Value& param);
void displayCharInfo(Value& param, int choice);

int main()
{
    /*cout << "Hello World!\n";*/
    Reader reader;
    Value value;
    int menuChoice = -1;
    int charChoice = -1;

    ifstream file("character.json");

    //reader.parse(file, value);
    file >> value;
    //Value newString = value[0]["affiliations"][0];

    //cout <<"Value is: \n" << newString;

    

    while (menuChoice != 0)
    {
        cout << "\nSelect an Option\n1. View Character Gallery\n2. Add Character to Favorites\n3. View Favorites\n4. Delete from Favorites\n0. Quit\n";
        cin >> menuChoice;

        if (menuChoice == 1) {
            displayCharList(value);
            displayCharInfo(value, charChoice);
        }
    }
    
}

void displayCharList(Value& para)
{
    cout << "Please select the number of a character\n";
    for (int i = 0; i < 87; i++)
    {
        cout << para[i]["id"] << " " << para[i]["name"] << "\n";

    }
}

void displayCharInfo(Value& param, int choice) {
    cin >> choice;
    for (int i = 0; i < 87; i++) {
        
        if (choice == param[i]["id"].asInt()) {

            character newCharacter = character(param[i]["name"], param[i]["id"], param[i]["species"], param[i]["gender"], param[i]["homeworld"]);
            newCharacter.displayInfo();
        }
    }
}
