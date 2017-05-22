// Copyright 2017 Andrei Rares, Popa Adrian
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_MOVIE_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_MOVIE_H_

#include<string>
#include<vector>
#include<cmath>
#include<sstream>
#include<iomanip>

struct Movie
{
    std::string name;
    std::string id;
    int timestamp;
    std::vector<std::string> categories;
    std::string director_name;
    std::vector<std::string> actors_ids;
    // rating mediu
    double rating;
    // voturi
    int votes;
    // suma rating-urilor
    double sum;

    // default constructor
    Movie()
    {
        this->votes = 0;
        this->sum = 0;
    }

    // constructor cu parametri
    Movie(std::string movie_name, std::string movie_id, int timestamp,
          std::vector<std::string> categories, std::string director_name,
          std::vector<std::string> actor_ids)
    {
        this->name = movie_name;
        this->id = movie_id;
        this->timestamp = timestamp;
        this->categories = categories;
        this->director_name = director_name;
        this->actors_ids = actor_ids;
        this->votes = 0;
        this->sum = 0;
    }

    // se adauga un rating
    void add_rating(double new_rating)
    {
        this->votes += 1;
        this->sum += new_rating;
        this->rating = this->sum / (double)this->votes;
    }

    // se actualizeaza un rating
    void update_rating(double new_rating, double old_rating)
    {
        this->sum -= old_rating;
        this->sum += new_rating;
        this->rating = this->sum / (double)this->votes;
    }

    // se sterge un rating
    void remove_rating(double old_rating)
    {
        this->votes -= 1;
        this->sum -= old_rating;
        this->rating = this->sum / (double)this->votes;
    }

    // intoarce rating-ul mediu
    std::string get_rating()
    {
        if (this->votes != 0)
        {
            // rotunjire
            double result = round(this->rating * 100) / 100;
            std::stringstream tmp;
            // precizie de doua zecimale
            tmp << std::fixed << std::setprecision(2) << result;
            std::string aux = tmp.str();
            return aux;
        }
        return "none";
    }

    // intoarce categoriile
    std::vector<std::string> get_categories()
    {
        return this->categories;
    }

    // intoarce timestamp-ul
    int get_timestamp()
    {
        return this->timestamp;
    }

    // intoarce rating-ul mediu
    double return_rating()
    {
        if (this->votes != 0)
        {
            return this->rating;
        }
        return -1;
    }
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_MOVIE_H_
