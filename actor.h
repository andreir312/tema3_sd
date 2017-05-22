// Copyright 2017 Andrei Rares, Popa Adrian
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_ACTOR_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_ACTOR_H_

#include<string>
#include<cmath>

struct Actor
{
    std::string id;
    std::string name;
    int number;
    // daca a jucat intr-un film
    bool is_begin;
    // daca a jucat in cel putin doua filme
    bool is_end;
    // cand a inceput cariera
    int begin;
    // cand a finalizat cariera
    int end;

    // default constructor
    Actor()
    {
        this->is_begin = false;
        this->is_end = false;
    }

    // constructor cu parametri
    Actor(std::string actor_id, std::string name, int number)
    {
        this->id = actor_id;
        this->name = name;
        this->number = number;
        this->is_begin = false;
        this->is_end = false;
    }

    // copy constructor
    Actor(const Actor& aux)
    {
        this->id = aux.id;
        this->name = aux.name;
        this->number = aux.number;
        this->is_begin = aux.is_begin;
        this->is_end = aux.is_end;
        this->begin = aux.begin;
        this->end = aux.begin;
    }

    // se actualizeaza cariera pe baza unui timestamp primit
    void sync_bounds(int timestamp)
    {
        // daca nu a jucat in nici un film
        if (this->is_begin == false)
        {
            this->begin = timestamp;
            this->is_begin = true;
        }
        // daca a jucat in cel putin un film
        else
        {
            // daca filmul e mai vechi decat cel mai vechi inregistrat
            if (this->begin > timestamp)
            {
                // daca a jucat in doar un film
                if (this->is_end == false)
                {
                    this->end = this->begin;
                    this->is_end = true;
                }
                this->begin = timestamp;
            }
            // daca filmul e mai nou decat cel mai vechi inregistrat
            else
            {
                // daca a jucat in doar un film
                if (this->is_end == false)
                {
                    this->end = timestamp;
                    this->is_end = true;
                }
                // daca a jucat in cel putin doua filme
                else
                {
                    // daca filmul e mai nou decat cel mai nou inregistrat
                    if (this->end < timestamp)
                    {
                        this->end = timestamp;
                    }
                }
            }
        }
    }

    // intoarce cariera unui actor
    int get_career()
    {
        // daca nu a jucat in nici un film
        if (this->is_begin == false)
        {
            return -1;
        }
        // daca a jucat in cel putin un film
        else
        {
            // daca a jucat in doar un film
            if (this->is_end == false)
            {
                return 0;
            }
        }
        return (int)std::abs(this->end - this->begin);
    }
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_ACTOR_H_
