//
// Created by aviv on 20/05/2021.
//

#include "Watchable.h"

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) {

}

Watchable::~Watchable() {

}

Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) {

}

std::string Movie::toString() const {
    return std::string();
}

Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) {

}

std::string Episode::toString() const {
    return std::string();
}

Watchable *Episode::getNextWatchable(Session &) const {
    return nullptr;
}
