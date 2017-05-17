#ifndef YEAR__H__
#define YEAR__H__

# include <string>

struct Year
{
    std::string name;

    double rating;

    double votes;

    double sum;

    Year(std::string name)
    {
        this->name = name;
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
        this->rating = round(this->rating * 100) / 100;

        std::ostringstream aux;

        aux << this->rating;

        return aux.str();
    }
};

#endif  // YEAR__H__


