// Copyright 2017 Andrei Rares
#include"include/imdb.h"

#include<iterator>
#include<string>
#include<map>
#include<unordered_map>
#include<vector>
#include<utility>
#include<ctime>
#include<algorithm>

std::string convert(int timestamp)
{
    time_t aux = timestamp;
    struct tm *tmp = new struct tm;
    char buffer[5];
    gmtime_r(&aux, tmp);
    strftime(buffer, 5, "%Y", tmp);
    std::string year(buffer);
    delete tmp;
    return year;
}

bool compare(std::pair<std::string, Movie> a, std::pair<std::string, Movie> b)
{
    if (a.second.votes != b.second.votes)
    {
        return a.second.votes > b.second.votes;
    }
    return a.first < b.first;
}

IMDb::IMDb()
{
    this->number = 0;
    this->ok = 0;
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp,
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids)
{
    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        if (this->categories.find(categories[i]) == this->categories.end())
        {
            this->categories.emplace(categories[i],
                                     Category(categories[i], year));
        }
        else
        {
            this->categories[categories[i]].sync(year);
        }
    }
    this->movies.emplace(movie_id, Movie(movie_name, movie_id, timestamp,
                                         categories, director_name, actor_ids));
    this->recent_movies.emplace(timestamp,
                                Movie(movie_name, movie_id, timestamp,
                                      categories, director_name, actor_ids));

    for (unsigned int i = 0; i < actor_ids.size(); i++)
    {
        this->actors[actor_ids[i]].sync_bounds(timestamp);
    }
    if (this->directors.find(director_name) == this->directors.end())
    {
        this->directors.emplace(director_name,
                                Director(director_name, actor_ids));
    }
    else
    {
        this->directors[director_name].sync_actors(actor_ids);
    }
    for (unsigned int i = 0; i < actor_ids.size() - 1; i++)
    {
        for (unsigned int j = i + 1; j < actor_ids.size(); j++)
        {
            actors_links.add_movie(actors[actor_ids[i]].number,
                                   actors[actor_ids[j]].number,
                                   actor_ids[i], actor_ids[j]);
        }
    }
    this->ok = 0;
}

void IMDb::add_user(std::string user_id, std::string name)
{
    this->users.emplace(user_id, User(user_id, name));
}

void IMDb::add_actor(std::string actor_id, std::string name)
{
    this->actors.emplace(actor_id, Actor(actor_id, name, number));
    this->actors_links.add_actor(number, actor_id);
    this->number++;
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating)
{
    this->users[user_id].add_rating(movie_id, (double)rating);
    double old = movies[movie_id].return_rating();
    this->movies[movie_id].add_rating((double)rating);
    std::vector<std::string> categories =
        this->movies[movie_id].get_categories();
    int timestamp = this->movies[movie_id].get_timestamp();
    this->recent_movies.find(timestamp)->second.add_rating((double)rating);
    std::string year = convert(timestamp);
    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].
        update_rating(year, movies[movie_id].return_rating(), old);
    }
    this->ok = 0;
}

void IMDb::update_rating(std::string user_id, std::string movie_id, int rating)
{
    double old_rating = this->users[user_id].
                        update_rating(movie_id, (double)rating);
    double old = movies[movie_id].return_rating();
    this->movies[movie_id].update_rating((double)rating, old_rating);
    std::vector<std::string> categories =
        this->movies[movie_id].get_categories();
    int timestamp = this->movies[movie_id].get_timestamp();
    this->recent_movies.find(timestamp)->second.
    update_rating((double)rating, old_rating);
    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].
        update_rating(year, movies[movie_id].return_rating(), old);
    }
}

void IMDb::remove_rating(std::string user_id, std::string movie_id)
{
    double old_rating = this->users[user_id].remove_rating(movie_id);
    double old = movies[movie_id].return_rating();
    this->movies[movie_id].remove_rating(old_rating);
    std::vector<std::string> categories =
        this->movies[movie_id].get_categories();
    int timestamp = this->movies[movie_id].get_timestamp();
    this->recent_movies.find(timestamp)->second.remove_rating(old_rating);
    std::string year = convert(timestamp);

    for (unsigned int i = 0; i < categories.size(); i++)
    {
        this->categories[categories[i]].
        update_rating(year, movies[movie_id].return_rating(), old);
    }
    this->ok = 0;
}

std::string IMDb::get_rating(std::string movie_id)
{
    return this->movies[movie_id].get_rating();
}

std::string IMDb::get_longest_career_actor()
{
    std::string actor_id;
    int career = -2;
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
    if (this->movies.empty() == true)
    {
        return "none";
    }
    return actors_links.second_degree_colleagues(actors[actor_id].number);
}

std::string IMDb::get_top_k_most_recent_movies(int k)
{
    if (this->recent_movies.empty() == true)
    {
        return "none";
    }
    std::map<int, Movie>::reverse_iterator rit;
    int i = 0;
    std::string result;

    for (rit = this->recent_movies.rbegin(); rit !=
            this->recent_movies.rend(); rit++)
    {
        i++;
        result += rit->second.id;

        if (i != k)
        {
            result += " ";
        }
        else
        {
            return result;
        }
    }
    result.resize(result.length() - 1);
    return result;
}

std::string IMDb::get_top_k_actor_pairs(int k)
{
    return actors_links.top_k_actor_pairs(k);
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id)
{
    return actors_links.top_k_partners(k, actors[actor_id].number, actor_id);
}

std::string IMDb::get_top_k_most_popular_movies(int k)
{
    if (this->movies.empty() == true)
    {
        return "none";
    }
    if (this->ok == 0)
    {
        popular_movies.assign(this->movies.begin(), this->movies.end());
        std::sort(popular_movies.begin(), popular_movies.end(), compare);
        this->ok = 1;
    }
    std::vector<std::pair<std::string, Movie>>::iterator it;
    int i = 0;
    std::string result;

    for (it = this->popular_movies.begin(); it !=
            this->popular_movies.end(); it++)
    {
        i++;
        result += it->second.id;

        if (i != k)
        {
            result += " ";
        }
        else
        {
            return result;
        }
    }
    result.resize(result.length() - 1);
    return result;
}

std::string IMDb::get_avg_rating_in_range(int start, int end)
{
    std::map<int, Movie>::iterator it1;
    double result = 0;
    double n = 0;
    double aux;

    for (it1 = this->recent_movies.begin(); it1 !=
            this->recent_movies.end(); it1++)
    {
        if (it1->first >= start)
        {
            while (it1->first <= end)
            {
                aux = it1->second.return_rating();

                if (aux > -1)
                {
                    result += aux;
                    n++;
                }
                it1++;

                if (it1 == this->recent_movies.end())
                {
                    break;
                }
            }
            break;
        }
    }
    if (n != 0)
    {
        result /= n;
        result = round(result * 100) / 100;
        std::stringstream tmp;
        tmp << std::fixed << std::setprecision(2) << result;
        std::string aux = tmp.str();
        return aux;
    }
    return "none";
}
