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

    int votes;
};

#endif  // MOVIE__H__
