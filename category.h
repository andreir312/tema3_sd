#ifndef CATEGORY__H__
#define CATEGORY__H__

# include <string>

# include <vector>

# include <unordered_map>

struct Category
{
    std::string name;

    std::unordered_map<std::string, Year> years;

    Category()
    {
        this->name = "";
    }

    Category(std::string name, std::string year)
    {
        this->name = name;

        this->years.emplace(year, Year(year));
    }

    void sync(std::string year)
    {
        if (this->years.find(year) == this->years.end())
        {
            this->years.emplace(year, Year(year));
        }
    }

    void add_rating(std::string year, double new_rating)
    {
        this->years[year].add_rating(new_rating);
    }

    void update_rating(std::string year, double new_rating, double old_rating)
    {
        this->years[year].update_rating(new_rating, old_rating);
    }

    void remove_rating(std::string year, double old_rating)
    {
        this->years[year].remove_rating(old_rating);
    }

    std::string get_rating(std::string year)
    {
        return this->years[year].get_rating();
    }
};

#endif  // CATEGORY__H__

