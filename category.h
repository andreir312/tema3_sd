// Copyright 2017 Andrei Rares
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORY_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORY_H_

#include<string>
#include<unordered_map>

struct Category
{
    std::string name;
    std::unordered_map<std::string, Year> years;

    Category()
    {
        this->name = "";
    }

    Category(std::string name, std::string year)
    {
        this->name = name;
        this->years.emplace(year, Year(year));
    }

    void sync(std::string year)
    {
        if (this->years.find(year) == this->years.end())
        {
            this->years.emplace(year, Year(year));
        }
    }

    void add_rating(std::string year, double new_rating)
    {
        this->years[year].add_rating(new_rating);
    }

    void update_rating(std::string year, double new_rating, double old_rating)
    {
        this->years[year].update_rating(new_rating, old_rating);
    }

    void remove_rating(std::string year, double new_rating, double old_rating)
    {
        this->years[year].remove_rating(new_rating, old_rating);
    }

    std::string get_rating()
    {
        std::string year;
        double rating = -1;
        double aux;
        std::unordered_map<std::string, Year>::iterator it;

        for (it = years.begin(); it != years.end(); it++)
        {
            aux = it->second.get_rating();

            if (rating < aux)
            {
                year = it->first;
                rating = aux;
            }
            else
            {
                if (rating == aux)
                {
                    if (year > it->first)
                    {
                        year = it->first;
                    }
                }
            }
        }
        if (rating == -1)
        {
            return "none";
        }
        return year;
    }
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORY_H_

