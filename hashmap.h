#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

// splits string by delimiter ",". Returns a vector of each word.
vector<string> splitString(const string& input) {

    vector<string> result;
    size_t start = 0;
    size_t pos;
    int loops = 0;

    while ((pos = input.find(",", start)) != std::string::npos) {

        if (loops == 9) break;
        // Check if the comma is followed by a space
        while (pos + 1 < input.size() && input[pos + 1] == ' ') {

            // Skip this comma and continue searching
            pos = input.find(",", pos + 2);
            if (pos == std::string::npos) break;
            //cout << ".";
        }


        //cout << endl;
        // Add the substring to the result
        result.push_back(input.substr(start, pos - start));
        //cout << input.substr(start, pos - start) << endl;
        start = pos + 1;
        loops ++;
    }

    // Add the last part of the string
    result.push_back(input.substr(start));

    return result;
}

// splits string in the cases of artist and genre
// which are bounded by '[' and ']'
vector<string> splitArtistGenre(string input) {


    if (input[0] == '"') {
        input = input.substr(1, input.length()-2);
    }

    //cout << input << endl;

    vector<string> result;
    input = input.substr(1,input.length()-2);
    size_t pos = 0;
    string token;

    // the following splitting algorithm was inspired from stack overflow.
    // find the position of the delimiter, push back the string from beginning->current,
    // remove that portion of the string, repeat.
    while ((pos = input.find(", ")) != std::string::npos) {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos +2);
    }

    result.push_back(input);
    return result;
}

// read in from file.
void readFileMaps(unordered_map<string, string> &trackNames,
                  unordered_map<string, vector<string>> &artistNames,
                  unordered_map<string, vector<string>> &genre,
                  unordered_map<string, vector<string>> & trackID) {
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

    getline(file, line);
    //int counter = 0;
    while(line != ",,,,,,,,,") {
        vector<string> test = splitString(line);

//        for(string j : test) {
//            cout << j << " ";
//        }
//        cout << endl;

        // the track ID will be the key, and all information will be held there.
        trackID[test[4]] = test;
        // add into tracknames.
        trackNames[test[test.size()-1]] = test[4];
        // add into artistnames.
        vector<string> aNames = splitArtistGenre(test[5]);
        for (string i : aNames) {
            //cout << i << endl;
            // current track will be added to all artist name keys.
            artistNames[i].push_back(test[4]);
        }
        // repeat the same for genres.
        vector<string> gs = splitArtistGenre(test[6]);
        for (string i : gs) {
            genre[i].push_back(test[4]);
        }
        //printing out each row.
        /*for (string i: test) {
            cout << i << " ";
        }
        cout << endl;*/

        //counter ++;
        getline(file, line);
        //cout << ".";
    }
    file.close();


}

class Hashmap {
private:
    unordered_map<string, string> trackNames;
    unordered_map<string, vector<string>> genres, artistNames;
    unordered_map<string, vector<string>> trackID;
public:
    Hashmap() {
        readFileMaps(trackNames, artistNames, genres, trackID);
        cout << "hashmap created.\n";
    }

    vector<string> findByID(string id) {
        // returns the vector<string> in the id map.
        // if the item does not exist, c++ returns an empty vector.
        return trackID[id];
    }

    vector<string> findTracksByArtist(string artist) {
        // returns a vector of strings, of track IDs by said artist.
        // if the artist does not exist, will return an empty vector.
        return artistNames[artist];
    }

    vector<string> findTracksByGenre(string g) {
        // returns a vector of strings, of track IDs that fall in a certain genre.
        // if the genre does not exist, will return an empty vector.
        return genres[g];
    }

    vector<string> findTracksByName(string n) {
        string id = trackNames[n];
        vector<string> temp = findByID(id);
        return temp;
    }

    unordered_map<string, vector<string>> getArtistNames() {
        return artistNames;
    }
};
