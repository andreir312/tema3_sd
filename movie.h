#ifndef MOVIE__H__
#define MOVIE__H__

# include <string>
# include <vector>

struct Movie
{
    std::string name;

    std::string id;

    int timestamp;

    std::vector<std::string> categories;

    std::string director_name;

    std::vector<std::string> actors_ids;

    double rating;

    double votes;

    double sum;

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
    }

    add_rating(int new_rating)
    {
        this->votes += 1;

        this->sum += (double)new_rating;

        this->rating = this->sum / this->votes;
    }

    update_rating(int new_rating, int old_rating)
    {
        this->sum -= (double)old_rating;

        this->sum += (double)new_rating;

        this->rating = this->sum / this->votes;
    }

    remove_rating(int old_rating)
    {
        this->votes -= 1;

        this->sum -= (double)old_rating;

        this->rating = this->sum / this->votes;
    }
};

#endif  // MOVIE__H__
