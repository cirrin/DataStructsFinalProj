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
    file.open("charts.csv");

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
    string prevSong = "";
    MinHeap minHeap;
    string genre = "['pop']";
    vector<Song> filteredSongs;
    ifstream file("charts(fixed).csv");
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
/*            cout << "Date: " << fields[0] << endl;
            cout << "Country: " << fields[1] << endl;
            cout << "Position: " << fields[2] << endl;
            cout << "Streams: " << fields[3] << endl;
            cout << "Track ID: " << fields[4] << endl;
            cout << "Artists: " << fields[5] << endl;
            cout << "Genres: " << fields[6] << endl;
            cout << "Duration: " << fields[7] << endl;
            cout << "Explicit: " << fields[8] << endl;*/
            cout << "Name: " << fields[9] << endl;
            Song *x = new Song; // feel free to change this implementation
            x->date= fields[0];
            x->country = fields[1];
            x->position = stoi(fields[2]);
            x->streams = stoi(fields[2]);
            x->track_id = fields[4];
            x->artists = fields[5];
            x->artist_genres = fields[6];
            x->duration = stoi(fields[7]);
            if (fields[8] == "True"){
                x->explicit_song = true;
            }
            else{
                x->explicit_song = false;
            }
            x->name = fields[9];
            minHeap.insert(*x);
        }else{
            cerr << "Invalid line: " << line << endl;
        }
    }
    cout << minHeap.searchByName("\"Who Want Smoke?? (feat. G Herbo, Lil Durk & 21 Savage)\"").artist_genres << endl;
    cout << minHeap.searchByName("As It Was").artist_genres << endl;
    filteredSongs = minHeap.searchByGenre(genre);
    for (auto i: filteredSongs){
        cout << i.name << " by: " << i.artists << " is explicit? : " << i.explicit_song << " highest position: " <<  i.position << " spotify id "<<  i.track_id << endl;
    }
    file.close();
    return 0;
}