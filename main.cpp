//
// Created by sherw on 11/26/2024.
//

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <regex>
#include "MinHeap.h"

using namespace std;

/*
vector<string> splitString(string s) {
    vector<string> result;
    string token = "";

    for (char c : s ) {
        if (c == ',') {
            result.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }
    result.push_back(token);
    return result;
}
// read in from file.
void readFileMaps(map<string, string> trackNames, map<string, string> artistNames, map<string, string> genre) {
    ifstream file;
    file.open("../charts.csv");

    if (!file.is_open()) {
        cout << "ERROR: file cannot be opened!" << endl;
        return;
    }

    // tracknames is <name, song ID>
    // artistnames is <singular artist name, song ID>
    // genre is <genre, song ID>

    string line;
    getline(file, line);
    vector<string> test = splitString(line);

    for (string i : test) {
        cout << i << " ";
    }
    cout << endl;

    file.close();
}
}*/
//i used a different method for splitting the CSV so that way it works for multiple commas in the brackets
//please utilize this with the other stuff unless you have a better method
vector<string> splitCSVLine(const string& line){
    vector<string> fields;
    string field;
    bool inQuotes = false;
    for(size_t i = 0; i < line.size(); i++){
        char currentChar = line[i];
        if(currentChar == '"'){
            inQuotes = !inQuotes;
        }
        if(!inQuotes && currentChar == ',') {
            fields.push_back(field);
            field.clear();
        }else{
            field += currentChar;
        }
    }
    fields.push_back(field);
    return fields;
}

int main(){
    MinHeap minHeap;
    ifstream file("../charts.csv");
    if(!file.is_open()){
        cerr << "Could not open the file!" << endl;
        return 1;
    }
    string line;
    string header;
    getline(file, header);
    while(getline(file, line)){
        //trims leading or trailing whitespaces if necessary
        line = regex_replace(line, regex("^\\s+|\\s+$"), "");
        //splits the line into fields
        vector<string> fields = splitCSVLine(line);
        //process the fields
        //CSV isnt set yet for the minheap, use the fields as their values if you can do it, feel free to change datatypes in song struct
        if(fields.size() == 10){
            cout << "Date: " << fields[0] << endl;
            cout << "Country: " << fields[1] << endl;
            cout << "Position: " << fields[2] << endl;
            cout << "Streams: " << fields[3] << endl;
            cout << "Track ID: " << fields[4] << endl;
            cout << "Artists: " << fields[5] << endl;
            cout << "Genres: " << fields[6] << endl;
            cout << "Duration: " << fields[7] << endl;
            cout << "Explicit: " << fields[8] << endl;
            cout << "Name: " << fields[9] << endl;
            cout << "Next Song: " << endl;
        }else{
            cerr << "Invalid line: " << line << endl;
        }
    }
    file.close();
    return 0;
}