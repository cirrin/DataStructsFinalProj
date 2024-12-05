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
#include <chrono>
#include <thread>


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
    MinHeap minHeap;
    vector<string> genres;
    vector<Song> filteredSongs;
    ifstream file("charts(fixed).csv");
    if(!file.is_open()){
        cerr << "Could not open the file!" << endl;
        return 1;
    }
    string line;
    string header;
    getline(file, header);
    auto befMin = chrono::steady_clock::now();
    while(getline(file, line)){
        //trims leading or trailing whitespaces if necessary
        line = regex_replace(line, regex("^\\s+|\\s+$"), "");
        //splits the line into fields
        vector<string> fields = splitCSVLine(line);

        //process the fields
        //CSV isnt set yet for the minheap, use the fields as their values if you can do it, feel free to change datatypes in song struct
        if(fields.size() == 10){

            Song *x = new Song; // feel free to change this implementation
            x->date= fields[0];
            x->country = fields[1];
            x->position = stoi(fields[2]);
            x->streams = stoi(fields[2]);
            x->track_id = fields[4];
            x->artists =fields[5];
            x->artist_genres =fields[6];
            x->duration = stoi(fields[7]);
            x->explicit_song = fields[8];
            x->name = fields[9];
            minHeap.insert(*x);
        }else{
            cerr << "Invalid line: " << line << endl;
        }
    }
    auto afterMin = std::chrono::steady_clock::now();
    auto durationMin = afterMin - befMin;
    file.close();
    auto b4hash = std::chrono::steady_clock::now();
    cout << "here1" << endl;
    Hashmap hashmap;
    cout << "here2" << endl;
    auto afterHash = std::chrono::steady_clock::now();
    auto duration = afterHash - b4hash;


    cout << "======================" << endl;
    cout << " | Group 54 Spotify |" << endl;
    cout << " | Song Finder      |" << endl;
    cout << " | from top 200s :D |" << endl;
    cout << "======================" << endl;
    int choice;

    cout << "\nHashmap created in: " << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << " microseconds or ";
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " milliseconds\n\n";

    cout << "MinHeap created in: " << chrono::duration_cast<chrono::microseconds>(durationMin).count() << " microseconds or ";
    cout << chrono::duration_cast<std::chrono::milliseconds>(durationMin).count() << " milliseconds\n\n";

    do{
        cout << "1: Search by Name" << endl;
        cout << "2: Search by Track ID" << endl;
        cout << "3: Suggestions by Artist" << endl;
        cout << "4: Suggestions by Genre" << endl;
        cout << "0: Exit" << endl;
        cout << "Enter choice:";
        cin >> choice;
        cin.ignore();
        if(choice == 1){
            cout << "Search by Name selected." << endl;
            string name;
            cout << "Input name of song, try to be exact:";
            getline(cin, name);
            int searchchoice;
            cout << "What method would you like to use?" << endl;
            cout << "1 for Hashmap, 2 for Minheap:";
            cin >> searchchoice;
            cout << endl;
            if(searchchoice == 1){
                // need to display name, explicit, duration (in seconds).
                // get trackID map. Find the vector associated. Then print out information
                auto beforeSearchHash = std::chrono::steady_clock::now();
                vector<string> trackIDInformation = hashmap.findTracksByName(name);
                auto afterSearchHash = std::chrono::steady_clock::now();
                auto searchDuration = afterSearchHash - beforeSearchHash;


                // if findbyid finds no match, then we return an empty list.
                // this catches the empty list.
                if (trackIDInformation.size() == 0) {
                    cout << "Track name not found. Please type exact name.\n";
                }
                else {
                    cout << "Song name: " << trackIDInformation[9] << endl;
                    cout << "Duration (seconds): " << int(stoi(trackIDInformation[7])/1000) << endl;
                    cout << "Explicit?: " << trackIDInformation[8] << endl;
                }

                cout << "\nSearch function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(searchDuration).count() << " microseconds or ";
                cout << std::chrono::duration_cast<std::chrono::nanoseconds>(searchDuration).count() << " nanoseconds\n";

            }
            else if(searchchoice == 2){
                try{
                    auto befMinS = chrono::steady_clock::now();
                    Song foundsong = minHeap.searchByName(name);
                    auto aftMinS = chrono::steady_clock::now();
                    auto totMin = aftMinS - befMinS;
                    cout << "Song name: " << foundsong.name << ", Duration in sec: " <<foundsong.duration/1000 << ", Position: " << foundsong.position;
                    cout << ", Explicit? " << foundsong.explicit_song << endl << endl;
                    cout << "Search function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(totMin).count() << " microseconds or ";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(totMin).count() << " nanoseconds\n" << endl;
                    cout << "What next?" << endl;
                    cout << "===============" << endl;
                }catch(exception& e){
                    cout << "Song not found, try again from menu."<< endl;
                    cout << "===============" << endl;
                }
            }else{
                cout << "Invalid method choice, try again from menu." << endl;
                cout << "===============" << endl;
            }
        }
        else if(choice == 2){
            cout << "Search by Track ID selected (Case Sensitive)." << endl;
            string ID;
            cout << "Input ID of track:";
            getline(cin, ID);
            int searchchoice;
            cout << "What method would you like to use?" << endl;
            cout << "1 for Hashmap, 2 for Minheap:";
            cin >> searchchoice;

            cout << endl;

            if(searchchoice == 1){
                auto beforeSearchHash = std::chrono::steady_clock::now();
                vector<string> trackIDInformation = hashmap.findByID(ID);


                // if findbyid finds no match, then we return an empty list.
                // this catches the empty list.
                if (trackIDInformation.size() == 0) {
                    cout << "Track name not found. Please type exact name.\n";
                }
                else {
                    cout << "Song name: " << trackIDInformation[9] << endl;
                    cout << "Duration (seconds): " << int(stoi(trackIDInformation[7])/1000) << endl;
                    cout << "Explicit?: " << trackIDInformation[8] << endl;
                }
                auto afterSearchHash = std::chrono::steady_clock::now();
                auto searchDuration = afterSearchHash - beforeSearchHash;
                cout << "\nSearch function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(searchDuration).count() << " microseconds or ";
                cout << std::chrono::duration_cast<std::chrono::nanoseconds>(searchDuration).count() << " nanoseconds\n";

            }
            else if(searchchoice == 2){
                try{
                    auto befMinS = chrono::steady_clock::now();
                    Song foundsong = minHeap.searchbyID(ID);
                    auto aftMinS = chrono::steady_clock::now();
                    auto totMin = aftMinS - befMinS;
                    cout << endl;
                    cout << "Song name: " << foundsong.name << ", Duration in sec: " <<foundsong.duration/1000 << ", Position: " << foundsong.position;
                    cout << ", Explicit? " << foundsong.explicit_song << endl;
                    cout << endl;
                    cout << "Search function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(totMin).count() << " microseconds or ";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(totMin).count() << " nanoseconds\n" << endl;
                    cout << "What next?" << endl;
                    cout << endl;
                    cout << "===============" << endl;
                }catch(exception& e){
                    cout << endl;
                    cout << "Song not found, try again from menu."<< endl;
                    cout << endl;
                    cout << "===============" << endl;
                }
            }else{
                cout << "Invalid method choice, try again from menu." << endl;
                cout << "===============" << endl;
            }
        }
        else if(choice == 3){
            cout << "Suggestions by Artist selected." << endl;
            string Artist;
            cout << "Input Artist name, try to be exact (Case Sensitive):";
            getline(cin, Artist);
            if (Artist == "Ed Sheeran") cout << "true\n";
            int searchchoice;
            cout << "What method would you like to use?" << endl;
            cout << "1 for Hashmap, 2 for Minheap:";
            cin >> searchchoice;

            cout << endl;

            // CHOSE HASHMAP
            if(searchchoice == 1){
                auto beforeSearchHash = std::chrono::steady_clock::now();
                vector<string> artistTracksInformation = hashmap.findTracksByArtist(Artist);


                cout << endl;

                // if findbyid finds no match, then we return an empty list.
                // this catches the empty list.
                if (artistTracksInformation.size() == 0) {
                    cout << "Track name not found. Please type exact name.\n";
                }
                else {
                    cout << "ALL TRACKS BY " << Artist << ": \n\n";
                    // we need to loop through each track, and post the track information of each.
                    for (string id : artistTracksInformation) {
                        vector<string> trackIDInformation = hashmap.findByID(id);

                        cout << "Song name: " << trackIDInformation[9] << endl;
                        cout << "Duration (seconds): " << int(stoi(trackIDInformation[7])/1000) << endl;
                        cout << "Explicit?: " << trackIDInformation[8] << endl;

                        cout << endl;
                    }
                }
                auto afterSearchHash = std::chrono::steady_clock::now();
                auto searchDuration = afterSearchHash - beforeSearchHash;
                cout << "\nSearch function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(searchDuration).count() << " microseconds or ";
                cout << std::chrono::duration_cast<std::chrono::nanoseconds>(searchDuration).count() << " nanoseconds\n";

            }
            else if(searchchoice == 2){
                auto befMinS = chrono::steady_clock::now();
                vector<Song> songsuggestions = minHeap.searchByArtist(Artist);
                auto aftMinS = chrono::steady_clock::now();
                auto totMin = aftMinS - befMinS;
                if(!songsuggestions.empty()){
                    cout << endl;
                    cout << "Here are some suggestions!"<< endl;
                    cout << "Order is name, duration, and explicit." << endl;
                    cout << endl;
                    for(int i =0; i<songsuggestions.size();i++){
                        cout<< i+1 << ": " << songsuggestions[i].name << ", "<<songsuggestions[i].duration/1000<<", "<<songsuggestions[i].explicit_song<<endl;
                    }
                    cout << endl;
                    cout << "Search function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(totMin).count() << " microseconds or ";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(totMin).count() << " nanoseconds\n" << endl;
                    cout << "What next?" << endl;
                    cout << endl;
                    cout << "===============" << endl;
                }else{
                    cout << endl;
                    cout << "Artist not found, try again from menu."<< endl;
                    cout << endl;
                    cout << "===============" << endl;
                }
            }else{
                cout << endl;
                cout << "Invalid method choice, try again from menu." << endl;
                cout << endl;
                cout << "===============" << endl;
            }
        }
        else if(choice == 4){
            cout << "Suggestions by Genre selected." << endl;
            string Genre;
            cout << "Input Genre, lowercase only:";
            getline(cin, Genre);
            cout << Genre << endl;
            int searchchoice;
            cout << "What method would you like to use?" << endl;
            cout << "1 for Hashmap, 2 for Minheap:";
            cin >> searchchoice;

            cout << endl;

            if(searchchoice == 1){
                auto beforeSearchHash = std::chrono::steady_clock::now();
                vector<string> genreTracksInformation = hashmap.findTracksByGenre(Genre);

                // if findbyid finds no match, then we return an empty list.
                // this catches the empty list.
                if (genreTracksInformation.size() == 0) {
                    cout << "Genre not found. Please type exact genre.\n";
                }
                else {
                    cout << "ALL TRACKS OF GENRE \"" << Genre << "\":\n\n";

                    // we need to loop through each track, and post the track information of each.
                    for (string id : genreTracksInformation) {
                        vector<string> trackIDInformation = hashmap.findByID(id);

                        cout << "Song name: " << trackIDInformation[9] << endl;
                        cout << "Duration (seconds): " << int(stoi(trackIDInformation[7])/1000) << endl;
                        cout << "Explicit?: " << trackIDInformation[8] << endl;

                        cout << endl;
                    }
                }
                auto afterSearchHash = std::chrono::steady_clock::now();
                auto searchDuration = afterSearchHash - beforeSearchHash;
                cout << "\nSearch function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(searchDuration).count() << " microseconds or ";
                cout << std::chrono::duration_cast<std::chrono::nanoseconds>(searchDuration).count() << " nanoseconds\n";

            }else if(searchchoice == 2){
                auto befMinS = chrono::steady_clock::now();
                vector<Song> songsuggestions = minHeap.searchByGenre(Genre);
                auto aftMinS = chrono::steady_clock::now();
                auto totMin = aftMinS - befMinS;
                if(!songsuggestions.empty()){
                    cout << endl;
                    cout << "Here are some suggestions!"<< endl;
                    cout << "Order is name, duration, and explicit." << endl;
                    cout << endl;
                    for(int i =0; i<songsuggestions.size();i++){
                        cout << i+1 << ": " << songsuggestions[i].name << ", "<<songsuggestions[i].duration/1000<<", "<<songsuggestions[i].explicit_song<<endl;
                    }
                    cout << endl;
                    cout << "Search function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(totMin).count() << " microseconds or ";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(totMin).count() << " nanoseconds\n" << endl;
                    cout << endl;
                    cout << "What next?" << endl;
                    cout << endl;
                    cout << "===============" << endl;
                }else{
                    cout << endl;
                    cout << "Genre not found, try again from menu."<< endl;
                    cout << endl;
                    cout << "===============" << endl;
                }
            }else{
                cout << endl;
                cout << "Invalid method choice, try again from menu." << endl;
                cout << endl;
                cout << "===============" << endl;
            }
        }else if(choice < 0 || choice > 4){
            cout << endl;
            cout << "Invalid choice, try again." << endl;
        }
    }while(choice != 0);
    cout << endl;
    cout << "Exiting program. Goodbye!" << endl;
    file.close();
    return 0;
}