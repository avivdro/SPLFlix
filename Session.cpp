//
// Created by aviv on 20/05/2021.
//

#include <sstream>
#include "Session.h"
#include "Watchable.h"
#include "User.h"
#include "Action.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &configFilePath) {
    cout << "will the real slim shady please stand up?" << endl;
    //TODO remove this :)
    exit = false;
    extractContent(configFilePath);
    //printAllContent(); //TODO remove this test
    //create the default user:
    initDefaultUser();
    start();
}

Session::~Session() = default;

void Session::start() {
    //MAIN EVENT LOOP!!!!!!
    cout << "SPLFlix is now on!";
    string input;
    while (! exit){
        cout << "\n$ ";
        getline(cin, input);
        //cout << "start received: " << input;
        parseInput(input);
        //clearInput();
    }
    cout << "You have exited SPLFlix. See you later!";
}

void Session::clearInput(){
    // Not sure that this is needed.
    cin.clear();
    int c;
    while ( (c=getchar()) != '\n' && c != EOF ){;}
};

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
    }
    int episodesStartId = id;
    //int tmp = id;
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

bool Session::addUser(std::string &name, User *newUser) {
    pair<string, User*> toInsert(name, newUser);
    bool inserted = userMap.insert(toInsert).second;
    return inserted;
}

void Session::initDefaultUser(){
    string defaultName = "default";
    auto createUser = CreateUser(defaultName, 1);
    createUser.act(*this);
    setActiveUser(defaultName); //TODO make sure this works
}

unordered_map<string, User*> const &Session::getUserMap(){
    return userMap;
}

bool Session::setActiveUser(string &name){
    //this returns true if user with name exists and is set to activeUser
    auto found = getUserMap().find(name);
    if (found != getUserMap().end()){
        activeUser = found->second;
        return true;
    }
    return false;
}

User* Session::getUserByName(string &name){
    auto found = getUserMap().find(name);
    if (found != getUserMap().end()){
        return found->second;
    }
    return nullptr;
}

bool Session::deleteUser(string &name){
    User *toDelete = getUserByName(name);
    if(toDelete == nullptr)
        return false;
    delete toDelete;
    toDelete = nullptr;
    return userMap.erase(name);
}

void Session::setExit(bool whatToSet){
    exit = whatToSet;
}

User* Session::getActiveUser() {
    return this->activeUser;
}

std::vector<BaseAction*> Session::getActionsLog(){
    return this->actionsLog;
}

void SortContentByLengthVector(){


}

//------------------------------------------------------------------------
void Session::parseInput(string &input){
    //get a string as an input and parse it
    //then do the action.
    //createuser <username> <len/gen/rer>
    //changeuser <username>
    //deleteuser <username>
    //dupuser <originalname> <newusername>
    //content
    //watchhist
    //watch <content_id>
    //log
    //exit

    istringstream iss(input);
    vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};

    if (words.empty()){
        cout << "No input detected.";
    }
    if (words[0] == "createuser"){
        sessCreateUser(words);
    }
    else if (words[0] == "changeuser"){
        sessChangeUser(words);
    }
    else if (words[0] == "deleteuser"){
        sessDeleteUser(words);
    }
    else if (words[0] == "dupuser"){
        sessDupUser(words);
    }
    else if (words[0] == "content"){
        sessContent(words);
    }
    else if (words[0] == "watchhist"){
        sessWatchHistory(words);
    }
    else if (words[0] == "watch"){
        sessWatch(words);
    }
    else if (words[0] == "log"){
        sessLog(words);
    }
    else if (words[0] == "exit"){
        sessExit(words);
    }
    else{
        cout << "'" + words[0] + "'" + " is not a valid command";
    }

}

void Session::addActionToLog(BaseAction *action) {
    actionsLog.push_back(action);
}

void Session::addToWatchHistory(Watchable *w){
    activeUser->addToHistory(w);
}

Watchable* Session::getWatchableById(int id){
    if (id>=content.size()) {
        return nullptr;
    }
    //ok
    if (content[id - 1]->getId() == id) {
        return content[id - 1];
    }
    else {
        return nullptr;
    }
}

int Session::getLastId(){
    return content.size();
}

//------------------------------------------------------------------------
//GUIDELINES for sessACTION:
//input: words vector.
//check the length of input is ok
//create Action object
//act
//add to actions log

void Session::sessCreateUser(vector<string> words){
    //FORMAT: createuser <username> <len/gen/rer>
    //check size of words
    if (words.size() != 3){
        cout << "Cannot do command: createuser syntax: 'createuser <username> <len/gen/rer>'";
        return;
    }
    //check name is not empty
    if (words[1].size() == 0){
        cout <<"Error: username must be at least one character.";
        return;
    }
    //check final argument
    int code = 0;
    if (words[2] == "len")
        code = 1;
    if (words[2] == "rer")
        code = 2;
    if (words[2] == "gen")
        code = 3;
    if (code == 0){
        cout << "Error: last argument must be len/gen/rer";
    }
    //doing it!
    auto command = new CreateUser(words[1], code);
    command->act(*this);
    addActionToLog(command);
};

void Session::sessChangeUser(vector<string> words) {
    //FORMAT: changeUser <username>
    //check size of words
    if (words.size() != 2) {
        cout << "Cannot do command: changeuser syntax: 'changeuser <username>'";
        return;
    }
    //check name is not empty
    if (words[1].size() == 0) {
        cout << "Error: username must be at least one character.";
        return;
    }
    auto command = new ChangeActiveUser(words[1]);
    command->act(*this);
    addActionToLog(command);
}

void Session::sessDeleteUser(vector<string> words) {
    //FORMAT: deleteUser <username>
    //check size of words
    if (words.size() != 2) {
        cout << "Cannot do command: deleteuser syntax: 'deleteuser <username>' ";
        return;
    }
    //check name is not empty
    if (words[1].size() == 0) {
        cout << "Error: username must be at least one character.";
        return;
    }
    auto command = new DeleteUser(words[1]);
    command->act(*this);
    addActionToLog(command);
}

void Session::sessDupUser(std::vector<std::string> words) {
    //FORMAT: dupuser <originalname> <newusername>
    //check size of words
    if (words.size() != 3) {
        cout << "Cannot do command: dupuser syntax: 'dupuser <originalname> <newusername>' ";
        return;
    }
    //check name is not empty
    if (words[1].empty() || words[2].empty()) {
        cout << "Error: username must be at least one character.";
        return;
    }
    auto command = new DuplicateUser(words[1], words[2]);
    command->act(*this);
    addActionToLog(command);
}

void Session::sessContent(vector<string> words){
    //FORMAT: content
    if (words.size() > 1){
        cout << "Syntax error: 'content' command must not have more arguments.";
        return;
    }
    auto cmd = new PrintContentList();
    cmd->act(*this);
    addActionToLog(cmd);
}

void Session::sessWatchHistory(vector<string> words){
    //FORMAT: watchhist
    if (words.size() > 1){
        cout << "Syntax error: 'watchhist' command must not have more arguments.";
        return;
    }
    auto cmd = new PrintWatchHistory();
    cmd->act(*this);
    addActionToLog(cmd);
}

void Session::sessWatch(vector<string> words){
    //FORMAT: watch <id>
    //Check that there are exactly two words
    if (words.size() != 2){
        cout << "Syntax error: Correct syntax for 'watch' command: 'watch <id>'";
        return;
    }
    //check that words[1] is a number
    int id = 0;
    stringstream ss;
    ss << words[1];
    ss >> id;
    if (id ==0 || to_string(id)!=words[1]){
        cout << "Syntax error: Correct syntax for 'watch' command: 'watch <id>'";
    }
    auto cmd = new Watch(id);
    cmd->act(*this);
    addActionToLog(cmd);
    //get recommendation
    //ask the user if he wants the recommendation or not.
}

void Session::sessLog(vector<string> words){
    //FORMAT: log
    if (words.size() > 1){
        cout << "Syntax error - 'log' command must not have more arguments.";
        return;
    }
    auto cmd = new PrintActionsLog();
    cmd->act(*this);
    addActionToLog(cmd);
}

void Session::sessExit(vector<string> words){
    //FORMAT: exit
    if (words.size() > 1){
        cout << "Syntax error - 'exit' command must not have more arguments.";
        return;
    }
    auto cmd = new Exit();
    cmd->act(*this);
    addActionToLog(cmd);
}



