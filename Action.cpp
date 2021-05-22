//
// Created by aviv on 20/05/2021.
//

#include "Action.h"
#include "Session.h"

using namespace std;

//ctor
BaseAction::BaseAction() : errorMsg("The action encountered an error."), status(PENDING){

}

//destructor
BaseAction::~BaseAction() = default;

ActionStatus BaseAction::getStatus() const {
    return status;
}

string BaseAction::getStatusString() const {
    switch (status) {
        case PENDING: return "Pending...";
        case ERROR: return "Error: " + getErrorMsg();
        case COMPLETED: return "Complete!";
    }
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(const std::string &errorMsg) {
    status = ERROR;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
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
    sess.printAllContent();
    complete();
    //TODO dont know if this works. need to check -aviv
}

std::string PrintContentList::toString() const {
    return "Printed content list. Status: " + getStatusString();
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
