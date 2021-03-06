//
// Created by aviv on 20/05/2021.
//

#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include "User.h"

class User;
class Watchable;

class Session{
public:
    //BUILT IN - UNCHANGEABLE
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    //OURS-
    void printAllContent();
    bool addUser(std::string &name, User* newUser);
    bool setActiveUser(std::string &name);
    User* getUserByName(std::string &name);
    bool deleteUser(std::string &name);
    void setExit(bool whatToSet);
    static void clearInput();
    User* getActiveUser();
    std::vector<Watchable*> getContent();
    std::vector<BaseAction*> getActionsLog();
    Watchable* getWatchableById(int id);
    int getLastId();
    bool hasRecommendation(int id);
    void addToWatchHistory(Watchable *w);

private:
    //BUILT IN - UNCHANGEABLE
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    //OURS - free to edit and change
    std::vector<Watchable*> contentSortedByLength;
    void extractContent(const std::string &configFilePath);
    void initDefaultUser();
    const std::unordered_map<std::string, User *> &getUserMap();
    bool exit; //if true - exit program
    void parseInput(std::string &whatToDo);
    void addActionToLog(BaseAction *action);
    void sortContentByLengthVector();
    static bool compare(const Watchable *w1, const Watchable *w2);
    //-------------------------
    void sessCreateUser(std::vector<std::string> words);
    void sessChangeUser(std::vector<std::string> words);
    void sessDeleteUser(std::vector<std::string> words);
    void sessDupUser(std::vector<std::string> words);
    void sessContent(std::vector<std::string> words);
    void sessWatchHistory(std::vector<std::string> words);
    void sessWatch(std::vector<std::string> words);
    void sessWatch2(std::vector<std::string> words);
    void sessLog(std::vector<std::string> words);
    void sessExit(std::vector<std::string> words);
};
#endif
