//
// Created by aviv on 20/05/2021.
//

#include "User.h"
#include <string>

using namespace std;

//ctor
User::User(const std::string &name)
    : history(), name(name) {}

std::string User::getName() const {
    return name;
}

std::vector<Watchable *> User::get_history() const {
    return std::vector<Watchable *>();
}

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {

}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}

RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {

}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}
