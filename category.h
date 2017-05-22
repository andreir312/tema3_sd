// Copyright 2017 Andrei Rares, Popa Adrian
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORY_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORY_H_

#include<string>
#include<unordered_map>

struct Category
{
    std::string name;
    // hashtable cu ani
    std::unordered_map<std::string, Year> years;

    // default constructor
    Category()
    {
        this->name = "";
    }

    // constructor cu parametri
    Category(std::string name, std::string year)
    {
        this->name = name;
        this->years.emplace(year, Year(year));
    }

    // se adauga un an daca nu este existent
    void sync(std::string year)
    {
        if (this->years.find(year) == this->years.end())
        {
            this->years.emplace(year, Year(year));
        }
    }

    // se adauga un rating pentru un an
    void add_rating(std::string year, double new_rating)
    {
        this->years[year].add_rating(new_rating);
    }

    // se actualizeaza un rating pentru un an
    void update_rating(std::string year, double new_rating, double old_rating)
    {
        this->years[year].update_rating(new_rating, old_rating);
    }

    // se sterge un rating pentru un an
    void remove_rating(std::string year, double new_rating, double old_rating)
    {
        this->years[year].remove_rating(new_rating, old_rating);
    }

    // intoarce anul cu rating-ul maxim
    std::string get_rating()
    {
        // initializari
        std::string year;
        double rating = -1;
        double aux;
        std::unordered_map<std::string, Year>::iterator it;

        for (it = years.begin(); it != years.end(); it++)
        {
            aux = it->second.get_rating();

            if (rating < aux)
            {
                // se ia anul cu cel mai mare rating
                year = it->first;
                rating = aux;
            }
            else
            {
                if (rating == aux)
                {
                    if (year > it->first)
                    {
                        // in caz de egalitate se ia anul minim
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

