/* Copyright 2017 Andrei Petre */

# include <iterator>

# include <string>

# include <vector>

# include <utility>

# include <ctime>

# include <algorithm>

# include "include/imdb.h"

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

    this->number = 0;
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp,  // unix timestamp when movie was launched
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

    this->recent_movies.emplace(timestamp, Movie(movie_name, movie_id, timestamp, categories, director_name, actor_ids));

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
    for (unsigned int i = 0; i < actor_ids.size()-1; i++)
    {
        for (unsigned int j = i+1; j < actor_ids.size(); j++)
        {
            actors_links.adauga_film(actors[actor_ids[i]].number,actors[actor_ids[j]].number,actor_ids[i],actor_ids[j]);
        }
    }
}

void IMDb::add_user(std::string user_id, std::string name)
{
    this->users.emplace(user_id, User(user_id, name));
}

void IMDb::add_actor(std::string actor_id, std::string name)
{
    this->number++;

    this->actors.emplace(actor_id, Actor(actor_id, name, number));
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating)
{
    this->users[user_id].add_rating(movie_id, (double)rating);

    this->movies[movie_id].add_rating((double)rating);

    std::vector<std::string> categories = this->movies[movie_id].get_categories();

    int timestamp = this->movies[movie_id].get_timestamp();

    this->recent_movies.find(timestamp)->second.add_rating((double)rating);

    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].add_rating(year, (double)rating);
    }
}

void IMDb::update_rating(std::string user_id, std::string movie_id,
                         int rating)
{
    double old_rating = this->users[user_id].update_rating(movie_id, (double)rating);

    this->movies[movie_id].update_rating((double)rating, old_rating);

    std::vector<std::string> categories = this->movies[movie_id].get_categories();

    int timestamp = this->movies[movie_id].get_timestamp();

    this->recent_movies.find(timestamp)->second.update_rating((double)rating, old_rating);

    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].update_rating(year, (double)rating, old_rating);
    }
}

void IMDb::remove_rating(std::string user_id, std::string movie_id)
{
    double old_rating = this->users[user_id].remove_rating(movie_id);

    this->movies[movie_id].remove_rating(old_rating);

    std::vector<std::string> categories = this->movies[movie_id].get_categories();

    int timestamp = this->movies[movie_id].get_timestamp();

    this->recent_movies.find(timestamp)->second.remove_rating(old_rating);

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
    std::string actor_id;

    int career = -1;

    int aux;

    std::unordered_map<std::string, Actor>::iterator it;

    for (it = actors.begin(); it != actors.end(); it++)
    {
        aux = it->second.get_career();

        if (career < aux)
        {
            actor_id = it->first;

            career = aux;
        }
        else
        {
            if (career == aux)
            {
                if (actor_id > it->first)
                {
                    actor_id = it->first;
                }
            }
        }
    }
    if (career == -1)
    {
        return "none";
    }
    return actor_id;
}

std::string IMDb::get_most_influential_director()
{
    std::string director_id;

    int actors = -1;

    int aux;

    std::unordered_map<std::string, Director>::iterator it;

    for (it = directors.begin(); it != directors.end(); it++)
    {
        aux = it->second.get_no_actors();

        if (actors < aux)
        {
            director_id = it->first;

            actors = aux;
        }
        else
        {
            if (actors == aux)
            {
                if (director_id > it->first)
                {
                    director_id = it->first;
                }
            }
        }
    }
    if (actors == -1)
    {
        return "none";
    }
    return director_id;
}

std::string IMDb::get_best_year_for_category(std::string category)
{
    return this->categories[category].get_rating();
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id)
{
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k)
{
    std::multimap<int, Movie>::reverse_iterator rit;

    int i = 0;

    std::string result;

    for (rit = this->recent_movies.rbegin(); rit != this->recent_movies.rend(); rit++)
    {
        i++;

        result += rit->second.id;

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
    return actors_links.top_k_perechi(k);
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id)
{
    return "";
}

std::string IMDb::get_top_k_most_popular_movies(int k)
{
    std::vector<std::pair<std::string, Movie>> top_votes(this->movies.begin(), this->movies.end());

    std::vector<std::pair<std::string, Movie>> buffer;

    std::sort(top_votes.begin(), top_votes.end(), compare);

    std::vector<std::pair<std::string, Movie>>::iterator it1;

    std::vector<std::pair<std::string, Movie>>::iterator it2 = top_votes.begin();

    std::vector<std::pair<std::string, Movie>>::iterator it3;

    std::vector<std::pair<std::string, Movie>>::iterator it4;

    int i = 0;

    std::string result;

    for (it1 = top_votes.begin(); it1 != top_votes.end(); it1++)
    {
        if (it2 != top_votes.end())
        {
            it2++;
        }
        if (it2 != top_votes.end())
        {
            if (it1->second.votes == it2->second.votes)
            {
                buffer.push_back(*(it1));

                buffer.push_back(*(it2));

                it1 = it2;

                it2++;

                it3 = it2;

                if (it3 != top_votes.end())
                {
                    while (it3->second.votes == it1->second.votes)
                    {
                        buffer.push_back(*(it3));

                        it3++;

                        if (it3 == top_votes.end())
                        {
                            break;
                        }
                    }
                    it1 = it3;

                    it1--;

                    it2 = it3;
                }
                std::sort(buffer.begin(), buffer.end(), compare);

                for (it4 = buffer.begin(); it4 != buffer.end(); it4++)
                {
                    if (i != k)
                    {
                        result += it4->first;

                        i++;

                        result += " ";
                    }
                    else
                    {
                        break;
                    }
                }
                buffer.clear();
            }
        }
        if (i != k)
        {
            result += it1->first;

            i++;

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
    std::multimap<int, Movie>::iterator it1;

    double result = 0;

    double n = 0;

    double aux;

    int ok = 1;

    for (it1 = this->recent_movies.begin(); it1 != this->recent_movies.end(); it1++)
    {
        if (it1->first >= start)
        {
            while (it1->first <= end)
            {
                aux = it1->second.return_rating();

                if (aux != 0)
                {
                    result += aux;

                    n++;
                }
                it1++;

                if (it1 == this->recent_movies.end())
                {
                    ok = 0;

                    break;
                }
            }
        }
        if (ok == 0)
        {
            break;
        }
    }
    if (result != 0)
    {
        result /= n;

        result = round(result * 100) / 100;

        std::stringstream tmp;

        tmp << std::fixed << std::setprecision (2) << result;

        std::string aux = tmp.str();

        return aux;
    }
    return "none";
}
