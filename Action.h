//
// Created by aviv on 20/05/2021.
//

#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "User.h"

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
    //BUILT IN - UNCHANGEABLE
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;
    virtual ~BaseAction();
    virtual std::string getStatusString() const;
    virtual void setErrorMsg(std::string &msg);
protected:
    //BUILT IN - UNCHANGEABLE
    void complete();
    void error(const std::string& errorMsg);
    std::string getErrorMsg() const;
private:
    //BUILT IN - UNCHANGEABLE
    std::string errorMsg;
    ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
    //OURS - free to edit:
    CreateUser(std::string &name, int code);
private:
    //OURS
    std::string name;
    int code; //code = 1: len, 2: rer, 3: gen.
};

class ChangeActiveUser : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
    //OURS
    ChangeActiveUser(std::string &name);
private:
    //OURS
    std::string name;
};

class DeleteUser : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session & sess);
    virtual std::string toString() const;
    DeleteUser(std::string &name);
    //OURS:
private:
    //OURS:
    std::string name;
};


class DuplicateUser : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session & sess);
    virtual std::string toString() const;
    //OURS:
    DuplicateUser(std::string &oldName, std::string &newName);
private:
    std::string oldName;
    std::string newName;
};

class PrintContentList : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act (Session& sess);
    virtual std::string toString() const;
    //OURS:
    //ctor
    PrintContentList();
};

class PrintWatchHistory : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act (Session& sess);
    virtual std::string toString() const;
    //OURS:
    //ctor
    PrintWatchHistory();
};


class Watch : public BaseAction {
private:
    //OURS
    int id;
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
    //OURS:
    Watch(int id);
};


class PrintActionsLog : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
    //OURS:
    //ctor
    PrintActionsLog();

};

class Exit : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
    //OURS - free to add edit and change
    Exit();
};
#endif
