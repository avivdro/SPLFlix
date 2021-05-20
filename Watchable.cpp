//
// Created by aviv on 20/05/2021.
//

#include <iostream>
#include <iterator>
#include "Watchable.h"

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
std::string Watchable::getTagsString() {
    std::vector<string>* vec = getTags();
    std::string s;
    for (const auto &piece : *vec) s += piece;
    return s;
}

//destructor - default
Watchable::~Watchable() = default;

//-------------------------------------------------------------------
//MOVIE
//ctor
Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) :
Watchable(id, length, tags), name(name) {}

std::string Movie::toString() const {
    return to_string(getId()) + ": " + name + " - " + to_string(getLength()) + " minutes - ";
    //TODO add tags!!!!
}

Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}

std::string Movie::getName() {
    return name;
}

//-------------------------------------------------------------------
//EPISODE

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) :
        Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode){}

std::string Episode::toString() const {
    return to_string(getId()) + ": " + getSeriesName() + "S" + to_string(season) + "E" + to_string(episode) + " " +
            to_string(getLength()) + " minutes "; //TODO add tags
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
