//
// Created by aviv on 20/05/2021.
//

#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    //BUILT IN - UNCHANGEABLE
    //ctor
    User(const std::string& name);
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    //OURS-
    //copy ctor
    User(const User& other);
    //copy assignment
    User &operator=(const User &other);
    //move ctor
    User(User &&other);
    //move assignment
    User &operator=(User &&other);
    //destructor
    virtual ~User();
    virtual User *clone(std::string &name) = 0;
    void addToHistory(Watchable *w);
    //bool isInHistory(const Watchable *w) const;

protected:
    //BUILT IN - UNCHANGEABLE
    std::vector<Watchable*> history;
private:
    //BUILT IN - UNCHANGEABLE
    std::string name;
    //OURS:
    void copy(const User &other);
    void clear();
    void move(User &&other);
};


class LengthRecommenderUser : public User {
public:
    //BUILT IN - UNCHANGEABLE
    LengthRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
    //TODO seems like i have to add a field for AVERAGE LENGTH???
};

class RerunRecommenderUser : public User {
public:
    //BUILT IN - UNCHANGEABLE
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
};

class GenreRecommenderUser : public User {
public:
    //BUILT IN - UNCHANGEABLE
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
};

#endif