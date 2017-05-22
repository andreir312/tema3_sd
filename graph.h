// Copyright 2017 Andrei Rares, Popa Adrian
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_GRAPH_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_GRAPH_H_

#include<string>
#include<queue>
#include<vector>
#include<algorithm>

// clasa folosita pentru sortarea rezultatului functiei top_k_partners
struct partner
{
    int movies;
    std::string id;

    partner()
    {
        movies = 0;
        id = "";
    }

    void operator =(const partner& d)
    {
        movies = d.movies;
        id = d.id;
    }

    partner(const partner& aux)
    {
        movies = aux.movies;
        id = aux.id;
    }
    // operatia de sortare
    bool operator <(const partner &aux) const
    {
        if (movies != aux.movies)
        {
            return (movies > aux.movies);
        }
        return (id < aux.id);
    }
};
// clasa folosita la memorarea actorilor si a numarului de filme dintre acestia
struct date
{
    int movies;
    std::string actor_id1;
    std::string actor_id2;

    date()
    {
        movies = 0;
        actor_id1 = "";
        actor_id2 = "";
    }

    void operator =(const date& d)
    {
        movies = d.movies;
        actor_id1 = d.actor_id1;
        actor_id2 = d.actor_id2;
    }

    date(const date& d)
    {
        movies = d.movies;
        actor_id1 = d.actor_id1;
        actor_id2 = d.actor_id2;
    }
    // actorii se introduc alfabetic in clasa
    void alfabetic(std::string actor_id1, std::string actor_id2)
    {
        if (actor_id1 < actor_id2)
        {
            this->actor_id1 = actor_id1;
            this->actor_id2 = actor_id2;
        }
        else
        {
            this->actor_id1 = actor_id2;
            this->actor_id2 = actor_id1;
        }
    }
    // determina partenerul de film al unui actor
    std::string partner(std::string actor_id)
    {
        if (actor_id == actor_id1)
        {
            return actor_id2;
        }
        return actor_id1;
    }
    // functie folosita la sortare
    bool operator <(const date &aux) const
    {
        // dupa numarul de filme
        if (movies != aux.movies)
        {
            return (movies > aux.movies);
        }
        //dupa primul id 
        if (actor_id1 != aux.actor_id1)
        {
            return (actor_id1 < aux.actor_id1);
        }
        // dupa al doilea id
        return (actor_id2 < aux.actor_id2);
    }
};

class Graph
{
 private:
    int position;  // numarul de actori din graf
    int size;  // dimensiunea totala a grafului
    std::vector<std::vector<struct date>> adiacency_matrix;

 public:
    Graph()
    {
        position = 0;
        this->size = 100;
        adiacency_matrix.resize(size);

        for (int i = 0; i < size; ++i)
        {
            adiacency_matrix[i].resize(size);
        }
    }
    // redimensionare graf
    void resize_matrix()
    {
        size *= 2;
        adiacency_matrix.resize(size);

        for (int i = 0 ; i < size; ++i)
        {
            adiacency_matrix[i].resize(size);
        }
    }
    // se intoduce un actor in graf si se seteaza filmele pe 0
    void add_actor(int src, std::string nume)
    {
        // daca nu mai e loc in graf
        if (src + 1 > size)
        {
            resize_matrix();
        }
        adiacency_matrix[src][src].actor_id1 = nume;
        position++;

        for (int i = 0 ; i< src; ++i)
        {
            adiacency_matrix[i][src].movies = 0;
            adiacency_matrix[src][i].movies = 0;
        }
    }
    // se introduce un film intre doi actori
    void add_movie(int src, int dst, std::string actor_id1,
                   std::string actor_id2)
    {
        // daca nu mai e loc in graf
        if (src >= size || dst >= size)
        {
            resize_matrix();
        }
        // daca nu exista actorul se introduce in graf
        // iar pe diagonala se retine numele acestuia
        if (src + 1 > position)
        {
            adiacency_matrix[src][src].actor_id1 = actor_id1;
            position++;
        }
        if (dst + 1 > position)
        {
            adiacency_matrix[dst][dst].actor_id1 = actor_id2;
            position++;
        }
        // se majoreaza contorul de filme si se pun alfabetic in graf
        adiacency_matrix[src][dst].movies += 1;
        adiacency_matrix[dst][src].movies += 1;
        adiacency_matrix[src][dst].alfabetic(actor_id1, actor_id2);
        adiacency_matrix[dst][src].alfabetic(actor_id1, actor_id2);
    }

    std::string top_k_actor_pairs(int k)
    {
        // daca nu exista nici un actor in graf
        if (position == 0)
        {
            return "none";
        }
        std::string result = "";
        // se declara un vector de parteneri
        std::vector<struct date> partners;

        for (int i = 0; i < position ; ++i)
        {
            for (int j = i + 1; j < position; ++j)
            {
                if (adiacency_matrix[i][j].movies != 0)
                {
                    partners.push_back(adiacency_matrix[i][j]);
                }
            }
        }
        // daca nu exista nici un film intre doi actori
        if (partners.empty())
        {
            return "none";
        }
        // se sorteaza vectorul
        std::sort(partners.begin(), partners.end());
        int top = 0;
        std::vector<struct date>::iterator it;

        for (it = partners.begin(); it != partners.end(); it++)
        {
            top++;
            // daca s-a depasit numarul cerut de perechi
            if (top > k)
            {
                break;
            }
            // se concateneaza numele actorilor la rezultat
            std::string movies = std::to_string(it->movies);
            result = result + "(" + it->actor_id1 + " " + it->actor_id2 + " "
            + movies + ") ";
        }
        // se sterge ultimul spatiu
        result.resize(result.size() - 1);
        return result;
    }
    // daca cei doi actori au jucat impreuna intr-un film
    bool has_movie(int src, int dst)
    {
        if (adiacency_matrix[src][dst].movies == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    // colegii de grad 2 ai unui actor;
    // este un BFS care se opeste dupa ce a gasit 
    // toti actorii la distanta 2 de sursa
    std::string second_degree_colleagues(int nod)
    {
        std::string *culoare = new std::string[position];
        int *distanta = new int[position];
        int i;

        for (i = 0; i < position; i++)
        {
            culoare[i] = "alb";
            distanta[i] = -1;
        }
        culoare[nod] = "gri";
        distanta[nod] = 0;
        std::queue<int> Q;
        Q.push(nod);
        int v;
        int ok = 0;
        int numar = 0;
        std::string *noduri = new std::string[position];
        int j = 0;

        while (!Q.empty())
        {
            v = Q.front();
            Q.pop();

            for (i = 0; i < position; i++)
            {
                if (has_movie(v, i))
                {
                    if (culoare[i] == "alb")
                    {
                        if (distanta[v] + 1 == 3)
                        {
                            ok = 1;
                            break;
                        }
                        numar++;
                        culoare[i] = "gri";
                        distanta[i] = distanta[v] + 1;

                        if (distanta[i] == 2)
                        {
                            // se extrage numele actorului de grad 2
                            noduri[j++] = adiacency_matrix[i][i].actor_id1;
                        }
                        Q.push(i);
                    }
                }
            }
            if (ok == 1)
            {
                break;
            }
            culoare[v] = "negru";
        }
        if (j == 0)
        {
            delete [] culoare;
			delete [] distanta;
			delete [] noduri;
			return "none";
        }
        std::sort(noduri, noduri + j);
        std::string result = "";

        for (i = 0; i < j; ++i)
        {
            result = result + noduri[i] + " ";
        }
        result.resize(result.size() - 1);
		delete [] culoare;
		delete [] distanta;
		delete [] noduri;
        return result;
    }

    std::string top_k_partners(int k, int number, std::string actor_id)
    {
        // daca exista doar actorul sursa in graf
        if (position == 1)
        {
            return "none";
        }
        struct partner aux;
        std::string result = "";
        // de declara un vector de parteneri
        std::vector<struct partner> partners;
        // se cauta toti partenerii
        for (int i = 0; i < position; ++i)
        {
            if (number == i)
            {
                continue;
            }
            if (adiacency_matrix[number][i].movies != 0)
            {
                // se introduc in vector
                aux.id = adiacency_matrix[number][i].partner(actor_id);
                aux.movies = adiacency_matrix[number][i].movies;
                partners.push_back(aux);
            }
        }
        // daca nu are nici un partener
        if (partners.empty())
        {
            return "none";
        }
        std::sort(partners.begin(), partners.end());
        int top = 0;
        std::vector<struct partner>::iterator it;

        for (it = partners.begin(); it != partners.end(); it++)
        {
            top++;
            // daca s-a depasit numarul cerut de parteneri
            if (top > k)
            {
                break;
            }
            result = result + it->id + " ";
        }
        result.resize(result.size() - 1);
        return result;
    }
};
#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_GRAPH_H_
