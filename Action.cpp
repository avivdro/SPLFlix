//
// Created by aviv on 20/05/2021.
//

/*list of implemented actions:
 - CreateUser - done ?
 - ChangeActiveUser - done ?
 - DeleteUser
 - DuplicateUser - done ?
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
    cout << errorMsg;
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
    return "Create user: " + name + " -STATUS: " + getStatusString();
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
    return "Change active user to " + name + " -STATUS: " + getStatusString();
}

ChangeActiveUser::ChangeActiveUser(std::string &name): name(name){
    string msg = "Error changing active user to: " + name;
    this->setErrorMsg(msg);
}

//-------------------------------------------------------------------
//DELETE USER
void DeleteUser::act(Session &sess) {
    if (sess.deleteUser(name))
        complete();
    else
        error(getErrorMsg());
}

std::string DeleteUser::toString() const {
    return "Delete user: " + name + " -STATUS: " + getStatusString();
}

DeleteUser::DeleteUser(string &name) : name(name){
    string msg = "Error deleting user " + name;
    this->setErrorMsg(msg);
}

//-------------------------------------------------------------------
//DUPLICATE USER
void DuplicateUser::act(Session &sess) {
    User *old = sess.getUserByName(oldName);
    if (old == nullptr) {
        //this means old user does not exist
        error(getErrorMsg());
        return;
    }
    if (sess.getUserByName(newName) != nullptr) {
        //this means there already exists a user with that name.
        error(getErrorMsg());
        return;
    }
    //here: oldUser exists and newUser does not.
    User *newUser = old->clone(newName);
    if (sess.addUser(newName, newUser)) {
        complete();
        return;
    }
    delete (newUser);
    newUser = nullptr;
    error(getErrorMsg());
}

std::string DuplicateUser::toString() const {
    return "Duplicate user " + oldName + " to new user " + newName;
}

DuplicateUser::DuplicateUser(string &oldName, string &newName) : oldName(oldName), newName(newName){
    string msg = "Error duplicating user " + oldName;
    this->setErrorMsg(msg);
}


//-------------------------------------------------------------------
//PRINT CONTENT LIST
void PrintContentList::act(Session &sess) {
    sess.printAllContent();
    complete();
    //TODO dont know if this works. need to check -aviv
}

std::string PrintContentList::toString() const {
    return "Print content list. -STATUS: " + getStatusString();
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
