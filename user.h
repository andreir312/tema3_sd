#ifndef USER__H__
#define USER__H__

# include <string>

# include <unordered_map>

struct User
{
    std::string id;

    std::string name;

    std::unordered_map<std::string, double> movies;

    User()
    {
        this->name = "";
    }

    User(std::string user_id, std::string name)
    {
        this->id = user_id;

        this->name = name;
    }

    void sync_rating(std::string movie_id, double rating)
    {
        this->movies[movie_id] = rating; // works with both add and update
    }

    void remove_rating(std::string movie_id)
    {
        this->movies.erase(movie_id);
    }

    double get_rating(std::string movie_id)
    {
        return this->movies[movie_id];
    }
};

#endif  // USER__H__
