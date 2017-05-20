// Copyright 2017 Andrei Rares
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_USER_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_USER_H_

#include<string>
#include<unordered_map>

struct User
{
    std::string id;
    std::string name;
    std::unordered_map<std::string, double> movies;

    User()
    {
        this->id = "";
        this->name = "";
    }

    User(std::string user_id, std::string name)
    {
        this->id = user_id;
        this->name = name;
    }

    void add_rating(std::string movie_id, double rating)
    {
        this->movies.emplace(movie_id, rating);
    }

    double update_rating(std::string movie_id, double rating)
    {
        double result = this->movies[movie_id];
        this->movies[movie_id] = rating;
        return result;
    }

    double remove_rating(std::string movie_id)
    {
        double result = this->movies[movie_id];
        this->movies.erase(movie_id);
        return result;
    }
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_USER_H_
