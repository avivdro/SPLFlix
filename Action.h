//
// Created by aviv on 20/05/2021.
//

#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

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
};

class ChangeActiveUser : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
};

class DeleteUser : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session & sess);
    virtual std::string toString() const;
};


class DuplicateUser : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session & sess);
    virtual std::string toString() const;
};

class PrintContentList : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act (Session& sess);
    virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act (Session& sess);
    virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
};


class PrintActionsLog : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
    //BUILT IN - UNCHANGEABLE
    virtual void act(Session& sess);
    virtual std::string toString() const;
};
#endif
