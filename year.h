// Copyright 2017 Andrei Rares, Popa Adrian
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_YEAR_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_YEAR_H_

#include<string>

struct Year
{
    std::string name;
    // rating mediu
    double rating;
    // voturi
    int votes;
    // suma rating-urilor
    double sum;

    // default constructor
    Year()
    {
        this->votes = 0;
        this->sum = 0;
    }

    // constructor cu parametri
    explicit Year(std::string name)
    {
        this->name = name;
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
        //
        if (old_rating == -1)
        {
            this->votes += 1;
            this->sum += new_rating;
            this->rating = this->sum / (double)this->votes;
        }
        //
        else
        {
            //
            if (new_rating == -1)
            {
                this->votes -= 1;
                this->sum -= old_rating;
                this->rating = this->sum / (double)this->votes;
            }
            //
            else
            {
                this->sum -= old_rating;
                this->sum += new_rating;
                this->rating = this->sum / (double)this->votes;
            }
        }
    }

    // se sterge un rating
    void remove_rating(double new_rating, double old_rating)
    {
        //
        if (new_rating == -1)
        {
            this->votes -= 1;
            this->sum -= old_rating;
            this->rating = this->sum / (double)this->votes;
        }
        //
        else
        {
            this->sum -= old_rating;
            this->sum += new_rating;
            this->rating = this->sum / (double)this->votes;
        }
    }

    // intoarce rating-ul mediu
    double get_rating()
    {
        if (this->votes != 0)
        {
            return this->rating;
        }
        return -2;
    }
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_YEAR_H_
