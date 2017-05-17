#ifndef YEAR__H__
#define YEAR__H__

# include <string>

# include <sstream>

# include <iomanip>

struct Year
{
    std::string name;

    double rating;

    double votes;

    double sum;

    Year()
    {
        this-> votes = 0;

        this->sum = 0;
    }

    Year(std::string name)
    {
        this->name = name;

        this-> votes = 0;

        this->sum = 0;
    }

    void add_rating(double new_rating)
    {
        this->votes += 1;

        this->sum += new_rating;

        this->rating = this->sum / this->votes;
    }

    void update_rating(double new_rating, double old_rating)
    {
        this->sum -= old_rating;

        this->sum += new_rating;

        this->rating = this->sum / this->votes;
    }

    void remove_rating(double old_rating)
    {
        this->votes -= 1;

        this->sum -= old_rating;

        this->rating = this->sum / this->votes;
    }

    std::string get_rating()
    {
        if (this->votes != 0)
        {
            double result = round(this->rating * 100) / 100;

            std::stringstream tmp;

            tmp << std::fixed << std::setprecision (2) << result;

            std::string aux = tmp.str();

            return aux;
        }
        return "none";
    }
};

#endif  // YEAR__H__


