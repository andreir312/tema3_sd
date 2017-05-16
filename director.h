#ifndef DIRECTOR__H__
#define DIRECTOR__H__

# include <string>

# include <vector>

# include <unordered_map>

struct Director
{
    std::string name;

    std::unordered_map<std::string, char> actors;

    Director(std::string director_name, std::vector<std::string> actor_ids)
    {
        this->name = director_name;

        for (unsigned int i = 0; i < actor_ids.length(); i++)
        {
            this->actors.emplace(actor_ids[i], 0);
        }
    }

    void sync_actors(std::vector<std::string> actor_ids)
    {
        for (unsigned int i = 0; i < actor_ids.length(); i++)
        {
            if (this->actors.find(actor_ids[i]) == this->actors.end())
            {
                this->actors.emplace(actor_ids[i], 0);
            }
        }
    }

    unsigned int get_no_actors()
    {
        return this->actors.size();
    }
};

#endif  // DIRECTOR__H__
