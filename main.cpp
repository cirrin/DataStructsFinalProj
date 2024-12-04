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
            x->explicit_song = fields[8];
            x->name = fields[9];
            minHeap.insert(*x);
        }else{
            cerr << "Invalid line: " << line << endl;
        }

    }/*
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
    }*/
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

    auto b4hash = std::chrono::steady_clock::now();
    Hashmap hashmap;
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

            }else if(searchchoice == 2){
                try{
                Song foundsong = minHeap.searchByName(name);
                cout << "Song name: " << foundsong.name << ", Duration in sec: " <<foundsong.duration/1000 << ", Position: " << foundsong.position;
                cout << ", Explicit? " << foundsong.explicit_song << endl;
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
        }else if(choice == 2){
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

            }else if(searchchoice == 2){
                try{
                    Song foundsong = minHeap.searchbyID(ID);
                    cout << endl;
                    cout << "Song name: " << foundsong.name << ", Duration in sec: " <<foundsong.duration/1000 << ", Position: " << foundsong.position;
                    cout << ", Explicit? " << foundsong.explicit_song << endl;
                    cout << endl;
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
        }else if(choice == 3){
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
                auto afterSearchHash = std::chrono::steady_clock::now();
                auto searchDuration = afterSearchHash - beforeSearchHash;

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

                cout << "\nSearch function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(searchDuration).count() << " microseconds or ";
                cout << std::chrono::duration_cast<std::chrono::nanoseconds>(searchDuration).count() << " nanoseconds\n";

            }else if(searchchoice == 2){
                vector<Song> songsuggestions = minHeap.searchByArtist(Artist);
                if(!songsuggestions.empty()){
                    cout << endl;
                    cout << "Here are some suggestions!"<< endl;
                    cout << "Order is name, duration, and explicit." << endl;
                    cout << endl;
                    for(int i =0; i<songsuggestions.size();i++){
                        cout<< i+1 << ": " << songsuggestions[i].name << ", "<<songsuggestions[i].duration/1000<<", "<<songsuggestions[i].explicit_song<<endl;
                    }
                    cout << endl;
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
        }else if(choice == 4){
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
                auto afterSearchHash = std::chrono::steady_clock::now();
                auto searchDuration = afterSearchHash - beforeSearchHash;


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

                cout << "\nSearch function done in: " << std::chrono::duration_cast<std::chrono::microseconds>(searchDuration).count() << " microseconds or ";
                cout << std::chrono::duration_cast<std::chrono::nanoseconds>(searchDuration).count() << " nanoseconds\n";

            }else if(searchchoice == 2){
                vector<Song> songsuggestions = minHeap.searchByGenre(Genre);
                if(!songsuggestions.empty()){
                    cout << endl;
                    cout << "Here are some suggestions!"<< endl;
                    cout << "Order is name, duration, and explicit." << endl;
                    cout << endl;
                    for(int i =0; i<songsuggestions.size();i++){
                        cout << i+1 << ": " << songsuggestions[i].name << ", "<<songsuggestions[i].duration/1000<<", "<<songsuggestions[i].explicit_song<<endl;
                    }
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