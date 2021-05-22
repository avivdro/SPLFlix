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
    User(const std::string& name);
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
protected:
    //BUILT IN - UNCHANGEABLE
    std::vector<Watchable*> history;
private:
    //BUILT IN - UNCHANGEABLE
    std::string name;

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