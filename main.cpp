//
// Created by sherw on 11/26/2024.
//

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>


using namespace std;

// splits string by delimiter ",". Returns a vector of each word.
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

int main() {
    cout << "Hello world" << endl;
    map<string, string> trackNames, genres, artistNames;
    readFileMaps(trackNames, artistNames, genres);
}
