#ifndef USER__H__
#define USER__H__

# include <string>
# include <unordered_map>

struct User
{
    std::string id;

    std::string name;

    std::unordered_map<std::string, double> movies;

    User(std::string user_id, std::string name)
    {
        this->id = user_id;

        this->name = name;
    }

    sync_rating(std::string movie_id, int rating)
    {
        movies[movie_id] = (double)rating; // works with both add and update
    }

    remove_rating(std::string movie_id)
    {
        movies.erase(movie_id);
    }
};

#endif  // USER__H__
