#ifndef ACTOR__H__
#define ACTOR__H__

# include <string>

# include <cmath>

struct Actor
{
    std::string id;

    std::string name;

    int number;

    bool is_begin;

    bool is_end;

    int begin;

    int end;

    Actor()
    {
        this->is_begin = false;

        this->is_end = false;
    }

    Actor(std::string actor_id, std::string name, int number)
    {
        this->id = actor_id;

        this->name = name;

        this->number = number;

        this->is_begin = false;

        this->is_end = false;
    }

    void sync_bounds(int timestamp)
    {
        if (this->is_begin == false)
        {
            this->begin = timestamp;

            this->is_begin = true;
        }
        else
        {
            if (this->begin > timestamp)
            {
                if (this->is_end == false)
                {
                    this->end = this->begin;

                    this->is_end = true;
                }
                this->begin = timestamp;
            }
            else
            {
                if (this->is_end == false)
                {
                    this->end = timestamp;

                    this->is_end = true;
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
        return (int)std::abs(this->end - this->begin);
    }
};

#endif  // ACTOR__H__
