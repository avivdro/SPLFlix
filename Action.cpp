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
#include <vector>
#include "Watchable.h"
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
        case PENDING: return "PENDING";
        case ERROR: return getErrorMsg();
        case COMPLETED: return "COMPLETE";
    }
    return "ERROR";
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
        string newmsg = "ERROR: Unknown user type.";
        setErrorMsg(newmsg);
        error(getErrorMsg());
        return;
    }
    if (sess.addUser(name, newUser)){
        complete();
        return;
    }
    string newmsg = "ERROR: User with that name already exists.";
    setErrorMsg(newmsg);
    error(getErrorMsg());
    delete (newUser);
    newUser = nullptr;
}

std::string CreateUser::toString() const {
    return "Create user: " + name + " - " + getStatusString();
}

CreateUser::CreateUser(string &name, int code): name(name), code(code){
    string msg = "Error creating user.";
    this->setErrorMsg(msg);
}

//-------------------------------------------------------------------
//CHANGE ACTIVE USER

void ChangeActiveUser::act(Session &sess) {
    if (!sess.setActiveUser(name)){
        string newmsg = "ERROR: User does not exist";
        setErrorMsg(newmsg);
        error(getErrorMsg());
        return;
    }
    complete();
}

std::string ChangeActiveUser::toString() const {
    return "Change active user to " + name + " - " + getStatusString();
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
    else{
        string newmsg = "ERROR: User does not exist.";
        setErrorMsg(newmsg);
        error(getErrorMsg());
    }
}

std::string DeleteUser::toString() const {
    return "Delete user: " + name + " - " + getStatusString();
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
        string newmsg = "ERROR: User does not exist.";
        setErrorMsg(newmsg);
        error(getErrorMsg());
        return;
    }
    if (sess.getUserByName(newName) != nullptr) {
        //this means there already exists a user with that name.
        string newmsg = "ERROR: User already exists.";
        setErrorMsg(newmsg);
        error(getErrorMsg());
        return;
    }
    //here: oldUser exists and newUser does not.
    User *newUser = old->clone(newName);
    if (sess.addUser(newName, newUser)) {
        complete();
        return;
    }
    //delete (newUser);
    //newUser = nullptr;
    error(getErrorMsg());
}

std::string DuplicateUser::toString() const {
    return "Duplicate user " + oldName + " to new user " + newName + " - " + getStatusString();
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
}

std::string PrintContentList::toString() const {
    return "Print content list. - " + getStatusString();
}

PrintContentList::PrintContentList() {
    string msg = "Error printing content list.";
    this->setErrorMsg(msg);
}

//-------------------------------------------------------------------
//PRINT WATCH HISTORY
void PrintWatchHistory::act(Session &sess) {
    User *user=sess.getActiveUser();
    vector<Watchable*> v=user->get_history();
    int i=1;
    string name;
    cout<<"Watch History for " + user->getName()<< endl;
    if (v.empty())
        cout << "No movies have been watched yet." <<endl;
    for(auto & w : v) {
        name = (w)->toStringForHistory();
        cout << i << ". " << name << endl;
        i++;
    }
    //delete user;
    complete();
}

std::string PrintWatchHistory::toString() const {
    return "Print watch history. - " + getStatusString();
}

PrintWatchHistory::PrintWatchHistory(){}

//-------------------------------------------------------------------
//WATCH
void Watch::act(Session &sess) {
    //get the watchable and watch it.
    Watchable* w = sess.getWatchableById(id);
    if (w == nullptr){
        string msg = "ERROR: No movie/episode with that id.";
        setErrorMsg(msg);
        error(getErrorMsg());
        return;
    }
    cout << "Watching: " + w->toStringForHistory() <<endl;
    //add the watchable to user's watch history
    sess.addToWatchHistory(w);
    complete();
}

std::string Watch::toString() const {
    return "Watch: " + to_string(id) + " - " + getStatusString();
}

Watch::Watch(int id): id(id){
    string msg = "Error watching id " + to_string(id);
    this->setErrorMsg(msg);
}

//-------------------------------------------------------------------
//PRINT ACTIONS LOG
void PrintActionsLog::act(Session &sess) {
    cout << "SPLFlix actions log:" << endl;
    vector<BaseAction*> v=sess.getActionsLog();
    for(auto it=v.rbegin(); it!=v.rend(); it++){
        cout<<(*it)->toString()<<endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const {
    return "Print actions log. - " + getStatusString();
}

PrintActionsLog::PrintActionsLog(){}

//-------------------------------------------------------------------
//EXIT
void Exit::act(Session &sess) {
    sess.setExit(true);
    complete();
}

std::string Exit::toString() const {
    return "Exit session.";
}

Exit::Exit(){
    string msg = "Error exiting session.";
    this->setErrorMsg(msg);
}


