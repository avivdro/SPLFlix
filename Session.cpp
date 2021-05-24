//
// Created by aviv on 20/05/2021.
//

#include "Session.h"
#include "Watchable.h"
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &configFilePath) {
    cout << "will the real slim shady please stand up?" << endl;
    //TODO remove this :)
    cout << "SPLFlix is now on!";
    extractContent(configFilePath);
    printAllContent(); //TODO remove this test
    //create the default user:

}

Session::~Session() = default;

void Session::start() {

}

void Session::extractContent(const string &configFilePath){
    std::fstream file(configFilePath);
    json j;
    try {
        j = json::parse(file);
    }
    catch (const std::exception& e){
        cout << "Error opening file" << endl;
        //TODO : EXIT PROGRAM
    }
    long id = 1;
    //extracting MOVIES
    json jMovies = j["movies"];
    for (auto &mov : jMovies.items()) {
        json movie = mov.value();
        auto *newMovie = new Movie(id, movie["name"], movie["length"], movie["tags"]);
        content.push_back(newMovie);
        id++;
        //cout << newMovie->toString() << endl;  //TODO remove this print
    }
    //extracting EPISODES
    json jEpisodes = j["tv_series"];
    for (auto &epi : jEpisodes.items()) {
        json series = epi.value();
        string seriesName = series["name"];
        int episodeLength = series["episode_length"];
        vector<int> seasons = series["seasons"];
        vector<string> tags = series["tags"];
        int season = 1;
        for (auto & element : seasons){
            int numOfEpisodes = element;
            int episodeNum = 1;
            for (int i = 1; i<= numOfEpisodes; i++) {
                auto *newEp = new Episode(id, seriesName, episodeLength, season, episodeNum, tags);
                content.push_back(newEp);
                id++;
                episodeNum++;
                //cout << newEp->toString() << endl; //TODO remove this print
            }
            season++;
        }
    }
}

void Session::printAllContent() {
    // method for PrintContentList action!
    for (Watchable* w : content)
        cout << w->toString() << endl;
}

void Session::initDefaultUser(){

}
