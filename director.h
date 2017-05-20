// Copyright 2017 Andrei Rares
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_DIRECTOR_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_DIRECTOR_H_

#include<string>
#include<vector>
#include<unordered_map>

struct Director
{
    std::string name;
    std::unordered_map<std::string, char> actors;

    Director()
    {
        this->name = "";
    }

    Director(std::string director_name, std::vector<std::string> actor_ids)
    {
        this->name = director_name;

        for (unsigned int i = 0; i < actor_ids.size(); i++)
        {
            this->actors.emplace(actor_ids[i], 0);
        }
    }

    void sync_actors(std::vector<std::string> actor_ids)
    {
        for (unsigned int i = 0; i < actor_ids.size(); i++)
        {
            if (this->actors.find(actor_ids[i]) == this->actors.end())
            {
                this->actors.emplace(actor_ids[i], 0);
            }
        }
    }

    int get_no_actors()
    {
        return (int)this->actors.size();
    }
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_DIRECTOR_H_
