//
// Created by aviv on 20/05/2021.
//

#include "User.h"
#include "Session.h"
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
        history.push_back(wPtr->clone());
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

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    //get the contentSortedByLength vector
    vector<Watchable*> v = s.getContent();
    Watchable* toRet = nullptr;   //stack toret
    int toRetDistance = averageLength;
    //search for the closest to this.averageLength() and NOT isInHistory()
    for (auto &w : v){
        if ((abs(averageLength - w->getLength()) < toRetDistance) &&(!isInHistory(w))){
            toRet = w;
            toRetDistance  = abs(averageLength - w->getLength());
        }
    }
    return toRet;
    //pretty sure i nailed it. -aviv
}

//copy ctor
LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &other): User(other), averageLength(other.averageLength) {}

//destructor
LengthRecommenderUser::~LengthRecommenderUser() = default;

//clone
User *LengthRecommenderUser::clone(string &name){
    auto *clone = new LengthRecommenderUser(name);
    *clone = *this;
    return clone;
}

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
    whatWasLastRecommended = -1;
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    //TODO the code works as required by the project guidelines
    //TODO ask marina: there is in inherited problem in the instructions of the rec algorithm
    //it will always recommend the last thing in my history....
    whatWasLastRecommended++;
    if (whatWasLastRecommended == history.size()){
        whatWasLastRecommended = 0;
    }
    cout << "what was last rec: " << whatWasLastRecommended << " hist " << history.size() << endl;
    return history[whatWasLastRecommended];
}

void RerunRecommenderUser::zeroIndex(){
    this->whatWasLastRecommended = 0;
}

User *RerunRecommenderUser::clone(string &name){
    auto *clone = new RerunRecommenderUser(name);
    *clone = *this;
    return clone;
}

//------------------------------------------------------------------------
//GENRE RECOMMENDER------------------------------
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    //sort the popularTags into a vector of strings by the popularity
    // create an empty vector of pairs
    vector<pair<string, int>> vec;

    // copy key-value pairs from the map to the vector
    std::copy(popularTags.begin(),
              popularTags.end(),
              std::back_inserter<std::vector<pair<string, int>>>(vec));

    // sort the vector by increasing the order of its pair's second value
    // if the second value is equal, order by the pair's first value
    std::sort(vec.begin(), vec.end(),
              [](const pair<string, int> &l, const pair<string, int> &r)
              {
                  if (l.second != r.second) {
                      return l.second < r.second;
                  }
                  //lexicographic
                  return l.first < r.first;
              });
    //Now for each of the pairs i need to check if there exists a watchable with that tag that i did not yet watch
    for (auto &p : vec){
        for (auto* w: s.getContent()){
            if ((w->hasTag(p.first)) && (!isInHistory(w))){
                return w;
            }
        }
    }
    return nullptr;
}

void GenreRecommenderUser::addToHistory(Watchable *w) {
    User::addToHistory(w);
    vector<string> *tagsV = w->getTags();
    for (auto tag : *tagsV){
        if (popularTags.find(tag) == popularTags.end()){
            pair<string, int> toInsert(tag, 1);
            popularTags.insert(toInsert).second;
        }
        else{
            popularTags.find(tag)->second++;
        }
    }
}



//clone
User *GenreRecommenderUser::clone(string &name){
    auto *clone = new GenreRecommenderUser(name);
    *clone = *this;
    return clone;
}
