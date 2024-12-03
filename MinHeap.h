#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>

using namespace std;

struct Song{
    string date, country, track_id, name;
    string artist_genres, artists;
    int position, streams, duration;
    bool explicit_song;
    bool operator<(const Song& other) const{
        return position < other.position;
    }
};

class MinHeap{
private:
    vector<Song> heap;

    int findParent(int i){
        return (i - 1)/2;
    }

    int findLeftChild(int i){
        return (2 * i) + 1;
    }

    int findRightChild(int i){
        return (2 * i) + 2;
    }

    void heapifyUp(int i){
        while(i > 0 && heap[i].position < heap[findParent(i)].position){ // heapifies based on position
            swap(heap[i], heap[findParent(i)]);
            i = findParent(i);
        }
    }

    string lowerCase(const string& search){
        string lower = search;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

public:
    Song getMin(){
        if (heap.empty()){
            throw out_of_range("Heap is empty");
        }
        return heap[0];
    }

    bool isEmpty() const{
        return heap.empty();
    }

    void insert(Song& song){
        heap.push_back(song);
        heapifyUp(heap.size() - 1);
    }

    Song searchByName(const string& name){
        string search = lowerCase(name);
        for(Song& song:heap){
            if(lowerCase(song.name) == search){
                return song;
            }
        }
        throw invalid_argument("Song not found.");
    }

    vector<Song> searchByGenre(const string& genre){
        string searchGenre = lowerCase(genre);
        vector<Song> matchingSongs;
        for(Song& song:heap){
                if(song.artist_genres.find(searchGenre) != string::npos&&matchingSongs.size()!=5){
                    matchingSongs.push_back(song);
                }
        }
        return matchingSongs;
    }

    vector<Song> searchByArtist(const string& artist){
        vector<Song> matchingSongs;
        for(Song& song:heap){
            if(song.artists.find(artist) != string::npos&&matchingSongs.size()!=5){
                matchingSongs.push_back(song);}
        }
        return matchingSongs;
    }

    Song searchbyID(const string& track_id){
        for(Song& song:heap){
            if(song.track_id==track_id){
                return song;
            }
        }
        throw invalid_argument("Song not found.");
    }


};
