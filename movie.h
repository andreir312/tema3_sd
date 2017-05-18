#ifndef MOVIE__H__
#define MOVIE__H__

# include <string>

# include <vector>

# include <cmath>

# include <sstream>

# include <iomanip>

struct Movie
{
    std::string name;

    std::string id;

    int timestamp;

    std::vector<std::string> categories;

    std::string director_name;

    std::vector<std::string> actors_ids;

    double rating;

    int votes;

    double sum;

    Movie()
    {
        this->votes = 0;

        this->sum = 0;
    }

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

    void add_rating(double new_rating)
    {
        this->votes += 1;

        this->sum += new_rating;

        this->rating = this->sum / (double)this->votes;
    }

    void update_rating(double new_rating, double old_rating)
    {
        this->sum -= old_rating;

        this->sum += new_rating;

        this->rating = this->sum / (double)this->votes;
    }

    void remove_rating(double old_rating)
    {
        this->votes -= 1;

        this->sum -= old_rating;

        this->rating = this->sum / (double)this->votes;
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

    std::vector<std::string> get_categories()
    {
        return this->categories;
    }

    int get_timestamp()
    {
        return this->timestamp;
    }

    int get_votes()
    {
        return this->votes;
    }

    double return_rating()
    {
        if (this->votes != 0)
        {
            return this->rating;
        }
        return 0;
    }
};

#endif  // MOVIE__H__
