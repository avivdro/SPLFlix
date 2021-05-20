//
// Created by aviv on 20/05/2021.
//

#include "Action.h"

BaseAction::BaseAction() {

}

ActionStatus BaseAction::getStatus() const {
    return ERROR;
}

void BaseAction::complete() {

}

void BaseAction::error(const std::string &errorMsg) {

}

std::string BaseAction::getErrorMsg() const {
    return std::string();
}
//-------------------------------------------------------------------
//CREATE USER
void CreateUser::act(Session &sess) {

}

std::string CreateUser::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//CHANGE ACTIVE USER

void ChangeActiveUser::act(Session &sess) {

}

std::string ChangeActiveUser::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//DELETE USER
void DeleteUser::act(Session &sess) {

}

std::string DeleteUser::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//DUPLICATE USER
void DuplicateUser::act(Session &sess) {

}

std::string DuplicateUser::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//PRINT CONTENT LIST
void PrintContentList::act(Session &sess) {

}

std::string PrintContentList::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//PRINT WATCH HISTORY
void PrintWatchHistory::act(Session &sess) {

}

std::string PrintWatchHistory::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//WATCH
void Watch::act(Session &sess) {

}

std::string Watch::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//PRINT ACTIONS LOG
void PrintActionsLog::act(Session &sess) {

}

std::string PrintActionsLog::toString() const {
    return std::string();
}

//-------------------------------------------------------------------
//EXIT
void Exit::act(Session &sess) {

}

std::string Exit::toString() const {
    return std::string();
}
