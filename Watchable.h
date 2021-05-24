//
// Created by aviv on 20/05/2021.
//

#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{
public:
    //BUILT IN - UNCHANGEABLE
    Watchable(long id, int length, const std::vector<std::string>& tags);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    //OURS - free to use and edit
    virtual long getId() const;
    virtual int getLength() const;
    virtual std::vector<std::string> * getTags();
    virtual std::string getTagsString() const;
    virtual bool operator==(const Watchable &other) const;
private:
    //BUILT IN - UNCHANGEABLE
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    //BUILT IN - UNCHANGEABLE
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    //OURS - free to use and edit
    virtual std::string getName();
private:
    //BUILT IN - UNCHANGEABLE
    std::string name;
};


class Episode: public Watchable{
public:
    //BUILT IN - UNCHANGEABLE
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    //OURS - free to use and edit
    virtual std::string getSeriesName() const;
    virtual int getSeason();
    virtual int getEpisode();
    virtual long getNextEpisodeId();
private:
    //BUILT IN - UNCHANGEABLE
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
