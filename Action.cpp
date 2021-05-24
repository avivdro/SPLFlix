//
// Created by aviv on 20/05/2021.
//

/*list of implemented actions:
 - CreateUser - done ?
 - ChangeActiveUser - done ?
 - DeleteUser
 - DuplicateUser
 - PrintContentList - done ?
 - PrintWatchHistory
 - Watch
 - PrintActionsLog
 - Exit
 */

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
    cout << errorMsg; //TODO is this needed?
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void BaseAction::setErrorMsg(std::string &msg) {
    errorMsg = msg;
}
//-------------------------------------------------------------------
//CREATE USER
void CreateUser::act(Session &sess) {
    User *newUser;
    if (code == 1) //len
        newUser = new LengthRecommenderUser(name);
    else if (code == 2) //rerun
        newUser = new RerunRecommenderUser(name);
    else if (code == 3) //genre
        newUser = new GenreRecommenderUser(name);
    else{
        error(getErrorMsg());
        return;
    }
    if (sess.addUser(name, newUser)){
        complete();
        return;
    }
    error(getErrorMsg());
    delete (newUser);
    newUser = nullptr;
}

std::string CreateUser::toString() const {
    return "Created user: " + name + " -STATUS: " + getStatusString();
}

CreateUser::CreateUser(string &name, int code): name(name), code(code){
    string msg = "Error creating user.";
    this->setErrorMsg(msg);
}

//-------------------------------------------------------------------
//CHANGE ACTIVE USER

void ChangeActiveUser::act(Session &sess) {
    if (!sess.setActiveUser(name)){
        error(getErrorMsg());
        return;
    }
    complete();
}

std::string ChangeActiveUser::toString() const {
    return "Changed active user to " + name + " -STATUS: " + getStatusString();
}

ChangeActiveUser::ChangeActiveUser(std::string &name): name(name){
    string msg = "Error changing active user to: " + name;
    this->setErrorMsg(msg);
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
    return "Printed content list. -STATUS: " + getStatusString();
}

PrintContentList::PrintContentList() {
    string msg = "Error printing content list.";
    this->setErrorMsg(msg);
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
