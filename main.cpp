//
// Created by sherw on 11/26/2024.
//

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <regex>
#include "MinHeap.h"
#include "hashmap.h"
#include <iterator>

using namespace std;


//i used a different method for splitting the CSV so that way it works for multiple commas in the brackets
//please utilize this with the other stuff unless you have a better method
vector<string> splitCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;
    for (size_t i = 0; i < line.size(); i++) {
        char currentChar = line[i];
        if (currentChar == '"') {
            inQuotes = !inQuotes;
        }
        if (!inQuotes && currentChar == ',') {
            fields.push_back(field);
            field.clear();
        } else {
            field += currentChar;
        }
    }
    fields.push_back(field);
    return fields;
}
vector<string> variableSplit(string& variable){
    vector<string> variables;
    string var;
    bool inQuotes = false;
    for (size_t i = 0; i < variable.size(); i++) {
        char currentChar = variable[i];
        if (currentChar == '\'') {
            inQuotes = !inQuotes;
        }
        if (!inQuotes && currentChar == ',') {
            variables.push_back(var);
            var.clear();
            i++; // removes space between genres
        }
        else if (currentChar != '[' && currentChar != '\'' && currentChar != '\"' && currentChar != ']') {
            var += currentChar;
        }
    }
    variables.push_back(var);
    return variables;
}

int main(){
    string test = "\"['drill', 'florida rap', 'southern hip hop', 'atl hip hop', 'chicago rap', 'chicago drill', 'trap', 'hip hop', 'rap']\"";
    MinHeap minHeap;
    vector<string> genres;
    string genre = "italian adult pop";
    vector<Song> filteredSongs;
    ifstream file("../charts(fixed).csv");
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
            cout << "Artists: " << fields[5] << endl;*/
           // cout << "Genres: " << fields[6] << endl;
           // cout << "Duration: " << fields[7] << endl;
           // cout << "Explicit: " << fields[8] << endl;
           // cout << "Name: " << fields[9] << endl;
            Song *x = new Song; // feel free to change this implementation
            x->date= fields[0];
            x->country = fields[1];
            x->position = stoi(fields[2]);
            x->streams = stoi(fields[2]);
            x->track_id = fields[4];
            x->artists =fields[5];
            x->artist_genres =fields[6];
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
    cout << "Artist Search: " << endl;
    vector<Song> songs = minHeap.searchByArtist("Avicii");
    for(int i=0; i<songs.size();i++){
        cout << songs[i].name << endl;
    }
    cout <<"Id Search:"<<endl;
    cout << minHeap.searchbyID("5dVUSdsePmEKkq4ryfrobU").name << endl;
    cout << "Genre Search: " << endl;
    vector<Song> genresongs = minHeap.searchByGenre("Pop");
    for(int i=0; i<genresongs.size();i++){
        cout << genresongs[i].name << endl;
    }
    /*
    filteredSongs = minHeap.searchByGenre(genre);
    for (auto i: filteredSongs) {
        cout << i.name << " by: ";
        for (int x = 0; x < i.artists.size(); x++) {
            if (x != i.artists.size() - 1) {
                cout << i.artists[x] << ", ";
            }
            else{
                cout << i.artists[x] << ' ';
            }
        }
        cout << " is explicit? : " << i.explicit_song << " highest position: " << i.position << " spotify id " << i.track_id << endl;
    }
     */
    file.close();
    cout << endl;
    cout << "minheap build finished.\n";
/*
// HASHMAP TESTING
    Hashmap hashmap;

    unordered_map<string, vector<string>> t = hashmap.getArtistNames();
    cout << t.size() << endl;

//    for (unordered_map<string, vector<string>>::iterator it=t.begin(); it!=t.end(); it++) {
//        cout << it->first << endl;
//    }

    // outputs all track IDs with Ed Sheeran as artist.
    vector<string> ts = hashmap.findTracksByArtist("'Ed Sheeran'");
    for (string i : ts) {
        cout << i << endl;
    }
*/

    return 0;
}