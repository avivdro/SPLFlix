//
// Created by aviv on 20/05/2021.
//

#include "Watchable.h"

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length),
                                                                                  tags(tags) {}


Watchable::~Watchable() {

}

Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) :
Watchable(id, length, tags), name(name) {}

std::string Movie::toString() const {
    return std::string();
}

Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) :
        Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode){}

std::string Episode::toString() const {
    return std::string();
}

Watchable *Episode::getNextWatchable(Session &) const {
    return nullptr;
}
