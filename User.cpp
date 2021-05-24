//
// Created by aviv on 20/05/2021.
//

#include "User.h"
#include "Watchable.h"
#include <string>
#include <algorithm>

using namespace std;

//ctor
User::User(const std::string &name)
    : history(), name(name) {}

//copy ctor
User::User(const User& other) : history(), name(other.name){
    copy(other);
}

//copy assignment
User &User::operator=(const User &other){
    if (this != &other){
        clear();
        copy(other);
    }
    return *this;
}
//move ctor
User::User(User &&other) : history(), name(other.name){
    move(std::move(other));
}
//move assignment
User &User::operator=(User &&other){
    if (this != &other){
        clear();
        move(std::move(other));
    }
    return *this;
}
//destructor
User::~User(){
    clear();
}
//clone
//add to history
void User::addToHistory(Watchable *w) {
    history.push_back(w);
}
//is in history?
bool User::isInHistory(Watchable *w) const{
    if (std::find(history.begin(), history.end(), w) != history.end()){
        return true;
    }
    return false;
}

std::string User::getName() const {
    return name;
}

std::vector<Watchable *> User::get_history() const {
    return history;
}

void User::copy(const User &other){
    for (auto wPtr : other.history){
        // history.push_back(wPtr->clone()); //TODO implement clone
    }
}

void User::clear(){
    for (auto &wPtr : history){
        delete wPtr;
        wPtr = nullptr;
    }
    history.clear();
}

void User::move(User &&other){
    for (auto &wPtr : other.history){
        history.push_back(wPtr);
        wPtr = nullptr;
    }
}


//CHILD CLASSES----------------------
//------------------------------------------------------------------------
//LENGTH RECOMMENDER-----------------------------
//ctor
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), averageLength(0){}

//TODO implement the next method
Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}

//copy ctor
LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &other): User(other), averageLength(other.averageLength) {}

//destructor
LengthRecommenderUser::~LengthRecommenderUser() = default;

//add to history: need to update avg.
void LengthRecommenderUser::addToHistory(Watchable *w) {
    int temp = averageLength * (history.size());
    temp += (w->getLength());
    User::addToHistory(w); //now history size is ++
    averageLength = temp / history.size();
}


//------------------------------------------------------------------------
//RERUN RECOMMENDER------------------------------
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {

}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}

//------------------------------------------------------------------------
//GENRE RECOMMENDER------------------------------
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}
