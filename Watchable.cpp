//
// Created by aviv on 20/05/2021.
//

#include <iostream>
#include <iterator>
#include "Watchable.h"
#include "Session.h"

using namespace std;

//-------------------------------------------------------------------
//WATCHABLE
//constructor (main)
Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length),
    tags(tags) {}

//GETTERS AND SETTERS
long Watchable::getId() const {
    return this->id;
}

int Watchable::getLength() const {
    return length;
}

std::vector<std::string> *Watchable::getTags() {
    return &tags;
}

//personal - for toString of MOVIE and EPISODE
std::string Watchable::getTagsString() const {
  const std::vector<std::string> vec = this->tags;
    std::string s="[";
    for (vector<string>::const_iterator it=vec.begin(); it!=vec.end()-1; it++)
        s = s + (*it) + ", ";
    s=s + vec[vec.size()-1] + "]";
    return s;
}

//destructor - default
Watchable::~Watchable() = default;

//comparator ==
bool Watchable::operator==(const Watchable &other) const{
    return id == other.id;
}

//-------------------------------------------------------------------
//MOVIE
//ctor
Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) :
Watchable(id, length, tags), name(name) {}

std::string Movie::toString() const {
    // <id>: <name> - <length> minutes - <tags>
    return to_string(getId()) + ": " + name + " - " + to_string(getLength()) + " minutes - " + getTagsString();
}

Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}

std::string Movie::getName() {
    return name;
}

Watchable *Movie::clone(){
    return new Movie(*this);
}

string Movie::toStringForHistory() const{
    return name;
}
string Movie::getSeriesName() const{
    //this function should NEVER be called!!!!
    return name;
}


//-------------------------------------------------------------------
//EPISODE

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) :
        Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode){}

std::string Episode::toString() const {
    //<id>: <seriesName> S<season>E<episode> - <length> minutes - <tags>
    return to_string(getId()) + ": " + getSeriesName() + " | S" + to_string(season) + "E" + to_string(episode) + " " +
            to_string(getLength()) + " minutes - " + getTagsString() + "NEXT:" + to_string(nextEpisodeId);
}

Watchable *Episode::getNextWatchable(Session &) const {
    return nullptr;
}

std::string Episode::getSeriesName() const {
    return seriesName;
}

int Episode::getSeason() {
    return season;
}

int Episode::getEpisode() {
    return episode;
}

long Episode::getNextEpisodeId() {
    return nextEpisodeId;
}

Watchable *Episode::clone(){
    return new Episode(*this);
}

string Episode::toStringForHistory() const{
    return getSeriesName() + " S" + to_string(season) + "E" + to_string(episode);
}



