# include <iterator>

# include <string>

# include <vector>

# include <utility>

# include <ctime>

# include <algorithm>

# include "imdb.h"

std::string convert(int timestamp)
{
    time_t aux = timestamp;

    struct tm *tmp;

    char buffer[5];

    tmp = gmtime(&aux);

    strftime(buffer, 5, "%Y", tmp);

    std::string year(buffer);

    return year;
}

bool compare(std::pair<std::string, Movie> a, std::pair<std::string, Movie> b)
{
    return a.second.votes > b.second.votes;
}

IMDb::IMDb()
{
    // initialize what you need here.
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp, // unix timestamp when movie was launched
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids)
{
    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        if (this->categories.find(categories[i]) == this->categories.end())
        {
            this->categories.emplace(categories[i], Category(categories[i], year));
        }
        else
        {
            this->categories[categories[i]].sync(year);
        }
    }
    this->movies.emplace(movie_id, Movie(movie_name, movie_id, timestamp, categories, director_name, actor_ids));

    this->recent_movies.emplace(timestamp, movie_id);

    for (unsigned int i = 0; i < actor_ids.size(); i++)
    {
        this->actors[actor_ids[i]].sync_bounds(timestamp);
    }
    if (this->directors.find(director_name) == this->directors.end())
    {
        this->directors.emplace(director_name, Director(director_name, actor_ids));
    }
    else
    {
        this->directors[director_name].sync_actors(actor_ids);
    }
}

void IMDb::add_user(std::string user_id, std::string name)
{

    this->users.emplace(user_id, User(user_id, name));

}

void IMDb::add_actor(std::string actor_id, std::string name)
{

    this->actors.emplace(actor_id, Actor(actor_id, name));

}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating)
{

    this->users[user_id].sync_rating(movie_id, (double)rating);

    this->movies[movie_id].add_rating((double)rating);

    std::vector<std::string> categories = this->movies[movie_id].get_categories();

    int timestamp = this->movies[movie_id].get_timestamp();

    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].add_rating(year, rating);
    }
}

void IMDb::update_rating(std::string user_id, std::string movie_id, int rating)
{

    double old_rating = this->users[user_id].get_rating(movie_id);

    this->users[user_id].sync_rating(movie_id, (double)rating);

    this->movies[movie_id].update_rating((double)rating, old_rating);

    std::vector<std::string> categories = this->movies[movie_id].get_categories();

    int timestamp = this->movies[movie_id].get_timestamp();

    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].update_rating(year, rating, old_rating);
    }

}

void IMDb::remove_rating(std::string user_id, std::string movie_id)
{

    double old_rating = this->users[user_id].get_rating(movie_id);

    this->users[user_id].remove_rating(movie_id);

    this->movies[movie_id].remove_rating(old_rating);

    std::vector<std::string> categories = this->movies[movie_id].get_categories();

    int timestamp = this->movies[movie_id].get_timestamp();

    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].remove_rating(year, old_rating);
    }

}

std::string IMDb::get_rating(std::string movie_id)
{
    return this->movies[movie_id].get_rating();
}

std::string IMDb::get_longest_career_actor()
{
    return "";
}

std::string IMDb::get_most_influential_director()
{
    return "";
}

std::string IMDb::get_best_year_for_category(std::string category)
{
    return "";
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id)
{
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k)
{
    std::multimap<int, std::string, Compare>::iterator it;

    int i = 0;

    std::string result;

    for (it = this->recent_movies.begin(); it != this->recent_movies.end(); it++)
    {
        i++;

        result += it->second;

        if (i != k)
        {
            result += " ";
        }
        else
        {
            break;
        }
    }
    return result;
}

std::string IMDb::get_top_k_actor_pairs(int k)
{
    return "";
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id)
{
    return "";
}

std::string IMDb::get_top_k_most_popular_movies(int k)
{
    std::vector<std::pair<std::string, Movie>> top_votes(this->movies.begin(), this->movies.end());

    std::sort(top_votes.begin(), top_votes.end(), compare);

    std::vector<std::pair<std::string, Movie>>::iterator it;

    int i = 0;

    std::string result;

    for (it = top_votes.begin(); it != top_votes.end(); it++)
    {
        i++;

        result += it->first;

        if (i != k)
        {
            result += " ";
        }
        else
        {
            break;
        }
    }
    return result;
}

std::string IMDb::get_avg_rating_in_range(int start, int end)
{
    return "";
}
