#ifndef __GRAPH__H
#define __GRAPH__H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct partner{
	int movies;
	std::string id;

	partner(){
		movies = 0;
		id = "";
	}
	void operator  = ( const partner& d)
    {
        movies = d.movies;
        id = d.id;
    }
    partner(const partner& aux)
    {
        movies = aux.movies;
        id = aux.id;
    }
	bool operator < ( const partner &aux) const {
		if (movies != aux.movies){
			return (movies > aux.movies );
		}
		return (id < aux.id);
	}	

};
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

    void operator  = ( const date& d)
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

    void alfabetic(string actor_id1, string actor_id2)
    {
        if ( actor_id1 < actor_id2)
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
    string partner(string actor_id)
    {
        if (actor_id == actor_id1)
        {
            return actor_id2;
        }
        return actor_id1;
    }
	bool operator < ( const date &aux) const
	{
		if (movies != aux.movies){
			return (movies > aux.movies );
		}
		if (actor_id1 != aux.actor_id1){
			return (actor_id1 < aux.actor_id1);
		}
		return (actor_id2 < aux.actor_id2);
	}
};

class Graph
{
 private:
    int position;
    int size;
    std::vector< std::vector<struct date> > adiacency_matrix;

 public:
    Graph()
    {
        position = 0;
        this->size = 100;
        adiacency_matrix.resize(size);
        for(int i = 0 ; i < size; ++i)
        {
            adiacency_matrix[i].resize(size);
        }
    }
    ~Graph() {}

    void resize_matrix()
    {
        size *=2;
        adiacency_matrix.resize(size);
        for(int i = 0 ; i < size; ++i)
        {
            adiacency_matrix[i].resize(size);
        }

    }

    void add_actor(int src, string nume)
    {
        if (src+1 > size)
        {
            resize_matrix();
        }

        adiacency_matrix[src][src].actor_id1 = nume;
        position++;
        for(int i = 0 ; i< src; ++i)
        {
            adiacency_matrix[i][src].movies = 0;
            adiacency_matrix[src][i].movies = 0;

        }
    }

    void add_movie(int src, int dst, string actor_id1, string actor_id2)
    {
        if ( (src >= size) || (dst >= size))
        {
            resize_matrix();
        }

        if (src+1 > position)
        {
            adiacency_matrix[src][src].actor_id1 = actor_id1;
            position++;
        }
        if (dst+1 > position)
        {
            adiacency_matrix[dst][dst].actor_id1 = actor_id2;
            position++;
        }

        adiacency_matrix[src][dst].movies += 1;
        adiacency_matrix[dst][src].movies += 1;

        adiacency_matrix[src][dst].alfabetic(actor_id1,actor_id2);
        adiacency_matrix[dst][src].alfabetic(actor_id1,actor_id2);
    }

    string top_k_actor_pairs(int k)
    {

        if (position == 0)
        {
            return "none";
        }
		string result = "";

		vector <struct date> partners;
 
        for (int i = 0; i < position ; ++i)
        {
            for (int j = i+1; j < position; ++j)
            {
                if (adiacency_matrix[i][j].movies != 0)
                {
					partners.push_back(adiacency_matrix[i][j]);
                }
            }
        }
        if (partners.empty()){
			return "none";
		}
		sort( partners.begin(),partners.end());

        int top = 0;

		vector <struct date>::iterator it;

        for (it = partners.begin(); it != partners.end(); it++)
        {
            top++;
            if (top > k)
            {
                break;
            }
            string movies = to_string(it->movies);
                result= result+"("+ it->actor_id1+ " " + it->actor_id2 + " " + movies +") " ;
			
        }
        
        if (result== "")
        {
            return "none";
        }
        result.resize( result.size () - 1);
        return result;
    }

    bool has_movie(int src, int dst)
    {
        if (adiacency_matrix[src][dst].movies == 0)
            return false;
        else
            return true;
    }

    string second_degree_colleagues(int nod)  // de grad 2
    {
        string culoare[position];
        int distanta[position];
        int i;

        for ( i=0; i<position; i++)
        {
            culoare[i]="alb";
            distanta[i]=-1;
        }

        culoare[nod]="gri";
        distanta[nod]=0;
        queue <int> Q;

        Q.push(nod);
        int v;
        int ok =0;
        int numar =0;
        string noduri[position];
        int j=0;

        while (!Q.empty())
        {
            v=Q.front();
            Q.pop();
            for (  i=0; i<position; i++)
            {
                if ( has_movie(v,i))
                {
                    if (culoare[i]=="alb")
                    {
                        if (distanta[v]+1 == 3)
                        {
                            ok = 1;
                            break;
                        }
                        numar++;
                        culoare[i]="gri";

                        distanta[i]=distanta[v]+1;
                        if (distanta[i] == 2)
                        {
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
            culoare[v]="negru";
        }
        if (j == 0)
        {
            return "none";
        }
		sort(noduri, noduri + j);

        std::string result = "";

        for (i=0; i<j; ++i)
        {
            result= result + noduri[i]+" ";
        }
		result.resize(result.size () - 1);
        return result;
    }
    
    string top_k_partners(int k, int number, string actor_id)
    {
        if (position == 1)
        {
            return "none";
        }
		struct partner aux;

        string result="";

		vector <struct partner> partners;

        for (int i = 0; i< position; ++i)
        {
            if (number == i)
            {
                continue;
            }
            if (adiacency_matrix[number][i].movies != 0)
            {
				aux.id = adiacency_matrix[number][i].partner(actor_id);
				aux.movies = adiacency_matrix[number][i].movies;
				partners.push_back(aux);
            }
        }
		if (partners.empty())
		{
			return "none";
		}
		sort( partners.begin(), partners.end() );

        int top = 0;
		vector <struct partner>::iterator it;
        for (it = partners.begin(); it != partners.end(); it++)
        {
            top++;
            if (top > k)
            {
                break;
            }
            result = result + it->id + " ";  
        }


        if (result == "")
        {
            return "none";
        }

		result.resize( result.size() - 1);
        return result;
    }
};
#endif  // GRAPH_H_
