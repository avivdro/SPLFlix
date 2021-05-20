//
// Created by aviv on 20/05/2021.
//

#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;

class Session{
public:
    //BUILT IN - UNCHANGEABLE
    Session(const std::string &configFilePath);
    ~Session();
    void start();
private:
    //BUILT IN - UNCHANGEABLE
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
};
#endif
