#ifndef ACTOR__H__
#define ACTOR__H__

# include <string>

# include <cmath>

struct Actor
{
    std::string id;

    std::string name;

    bool is_begin;

    bool is_end;

    int begin;

    int end;

    Actor(std::string actor_id, std::string name)
    {
        this->id = actor_id;

        this->name = name;

        this->is_begin = false;

        this->is_end = false;
    }

    void sync_bounds(int timestamp)
    {
        if (this->is_begin == false)
        {
            this->begin = timestamp;
        }
        else
        {
            if (this->begin > timestamp)
            {
                if (this->is_end == false)
                {
                    this->end = this->begin;
                }
                this->begin = timestamp;
            }
            else
            {
                if (this->is_end == false)
                {
                    this->end = timestamp;
                }
                else
                {
                    if (this->end < timestamp)
                    {
                        this->end = timestamp;
                    }
                }
            }
        }
    }

    int get_career()
    {
        if (this->is_begin == false || this->is_end == false)
        {
            return 0;
        }
        return abs(this->end - this->begin);
    }
};

#endif  // ACTOR__H__
