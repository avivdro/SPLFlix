//
// Created by aviv on 20/05/2021.
//

#include "User.h"

User::User(const std::string &name) {

}

std::string User::getName() const {
    return std::string();
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
