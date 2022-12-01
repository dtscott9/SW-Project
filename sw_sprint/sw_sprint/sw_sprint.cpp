// sw_sprint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define CURL_STATICLIB
#include <curl/curl.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <json/json.h>
#include <json/value.h>
#include <list>
#include <algorithm>
#include <numeric>
#include "character.h"
using namespace std;
using namespace Json;
using namespace cv;


//Character and favorites list elements
list<character> favorites;
void displayCharList(Value& param);
void displayCharInfo(Value& param, int choice, int menu);
void loopThroughList();

//These next two functions are used to convert to img url to a viewable image for opencv
size_t write_data(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::ostringstream* stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}

Mat curlImg(const char *imgUrl)
{
    CURL* curl;
    CURLcode res;
    std::ostringstream stream;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, imgUrl); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
    res = curl_easy_perform(curl); 
    std::string output = stream.str(); 
    curl_easy_cleanup(curl); 
    std::vector<char> data = std::vector<char>(output.begin(), output.end()); 
    cv::Mat data_mat = cv::Mat(data); 
    cv::Mat image = cv::imdecode(data_mat, 1); 
    return image;
}

//Function that is used to display the image found in the json
void displayImage(int i, Value& param) {

    string path = param[i]["image"].asString();
    const char* pathArray = path.c_str();
    
    cv::Mat img = curlImg(pathArray);
    namedWindow("Character Image", WINDOW_NORMAL);
    resizeWindow("Character Image", 500, 500);
    cv::imshow("Character Image", img);
    cv::moveWindow("Character Image", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main()
{
    //JSON variables
    Reader reader;
    Value value;

    //vars related to menu choice
    int menuChoice = -1;
    int charChoice = -1;

    //These next two lines hadle the parsing of the json data
    ifstream file("character.json");
    file >> value;
    
    //This is where the startup menu begins
    while (menuChoice != 0)
    {
        cout << "\nSelect an Option\n1. View Character Gallery\n2. View Favorites\n3. Delete from Favorites\n0. Quit\n";
        cin >> menuChoice;

        if (menuChoice == 1) {
            displayCharList(value);
            displayCharInfo(value, charChoice, menuChoice);
           

        }

        else if (menuChoice == 2) {
            loopThroughList();
        }

        else if (menuChoice == 3) {
            cout << "\nEnter the ID of the character you'd like to delete: \n";
            loopThroughList();
            cin >> charChoice;

            auto new_end = remove_if(favorites.begin(), favorites.end(), [charChoice](auto& favorite) {
                return favorite.getId() == charChoice;
                });
            favorites.erase(new_end, favorites.end());

        }
    }
    
}

void loopThroughList() {
    for_each(favorites.begin(), favorites.end(), [](auto& favorite) {
        favorite.displayInfo();
        });
}

void displayCharList(Value& para)
{
    cout << "Please select the number of a character\n";
    for (int i = 0; i < 87; i++)
    {
        cout << para[i]["id"] << " " << para[i]["name"] << "\n";

    }
}

void displayCharInfo(Value& param, int choice, int menu) {
    cin >> choice;
    for (int i = 0; i < 87; i++) {
        
        if (choice == param[i]["id"].asInt()) {

            character newCharacter = character(param[i]["name"], param[i]["id"], param[i]["species"], param[i]["gender"], param[i]["homeworld"]);
            newCharacter.displayInfo();

            if (menu < 2)
            {
                cout << "\nAffiliations: " << param[i]["affiliations"] << "\nMasters: " << param[i]["masters"] << "\nApprentices: " << param[i]["apprentices"] << "\n";
                displayImage(i, param);
                
            }

            cout << "\nWould you like to add this character to your favorites list? Y/N \n";
            string userChoice;
            cin >> userChoice;
            if (userChoice == "Y" || userChoice == "y") {
                favorites.push_back(newCharacter);
                cout << "\nAdded successfully";
            }
        }
    }
}
