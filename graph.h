//
    #ifndef __GRAPH__H
    #define __GRAPH__H
	#include <iostream>
	#include <string>
	#include <queue>

	using namespace std;

    struct date{
    	int filme;
    	std::string actor_id1;
    	std::string actor_id2;
    	int numar_ordine;

    	date(){
    		filme = 0;
    		actor_id1 = "";
    		actor_id2 = "";
    		numar_ordine = -1;
    	}

    	void operator  = ( const date& d){
            filme = d.filme;
            actor_id1 = d.actor_id1;
            actor_id2 = d.actor_id2;
            numar_ordine = d.numar_ordine;
        }
        date(const date& d) {
        	filme = d.filme;
            actor_id1 = d.actor_id1;
            actor_id2 = d.actor_id2;
            numar_ordine = d.numar_ordine;
        }


    	void alfabetic(string actor_id1, string actor_id2){
    		if ( actor_id1 < actor_id2){
    			this->actor_id1 = actor_id1;
    			this->actor_id2 = actor_id2;
   			} else{
    			this->actor_id1 = actor_id2;
    			this->actor_id2 = actor_id1;
    		}
    	}
    	string pereche(string actor_id){
    		if (actor_id == actor_id1){
    			return actor_id2;
    		}
    		return actor_id1;
    	}
    };

    class Graph {
     private:
     		int pozitie;
	    	int size;
            struct date **adiacency_matrix;

     public:
            Graph() {
            	pozitie = -1;
				this->size = 100;

				adiacency_matrix = new struct date* [100];
				for (int i=0 ; i < 100 ; i++){
					adiacency_matrix[i] = new struct date[100];
				}
			}
            ~Graph(){
            	cout<<"destructor\n";
				for (int i = 0; i < size ; i++){
					delete[] adiacency_matrix[i];
				}
				delete[] adiacency_matrix;
			}
			void redimensionare(){
				struct date **aux;
				size += 100;
				aux = new struct date* [size];
				for (int i=0 ; i < size ; i++){
					aux[i] = new struct date[size];
				}
				for ( int i = 0; i < pozitie; ++i){
					for ( int j = i ; i <= pozitie; ++j){
						aux[i][j] = adiacency_matrix[i][j];
						aux[j][i] = adiacency_matrix[j][i];
					}
				}
				for (int i = 0; i <= pozitie ; i++){
					delete[] adiacency_matrix[i];
				}
				adiacency_matrix = aux;
				delete[] aux;

			}

			void adauga_film(int src, int dst, string a, string b){
				if ( (src >= size) || (dst >= size)){
					redimensionare();
				}
				

				if (src > pozitie){
					adiacency_matrix[src][dst].numar_ordine = src;
					adiacency_matrix[src][src].actor_id1 = a;
					pozitie++;
				}
				if (dst > pozitie){
					adiacency_matrix[dst][src].numar_ordine = dst;
					adiacency_matrix[dst][dst].actor_id1 = b;
					pozitie++;
				}
			

				adiacency_matrix[src][dst].filme += 1;
				adiacency_matrix[dst][src].filme += 1;

				adiacency_matrix[src][dst].alfabetic(a,b);
				adiacency_matrix[dst][src].alfabetic(a,b);

				
			}

     		void QUICKSORT(int inf, int sup, struct date A[]) {
		      int x, i, j, t;
		      struct date *aux;
		      aux = new struct date; 
		      i = inf;
		      j = sup;
		      x = A[(i + j) / 2].filme;
		      do {
		        while ( (i < sup) && (A[i].filme > x) ) i++;
		        while ( (j > inf) &&(A[j].filme < x) ) j--;
		        if (i <= j) {
		          *aux = A[i];
		          A[i] = A[j];
		          A[j] = *aux;
		          i++;
		          j--;
		        }
		      } while ( i <= j );
		      delete aux;
		      if ( inf < j ) QUICKSORT(inf, j, A);
		      if ( i < sup ) QUICKSORT(i, sup, A);
		    }

		    void top_k_perechi(int k){     
		    	struct date *vector;
		    	vector = new struct date[pozitie*(pozitie/2)];
		    	int w = -1;
		    	// copii toate filmele intr-un vector de structa date
		    	for (int i = 0; i < pozitie-1; ++i){
		    		for (int j = i+1; j < pozitie; ++j){
		    			w++;
		    			// daca exista film intre actori
		    			if (adiacency_matrix[i][j].filme != 0){
		    				
			    			vector[w].filme = adiacency_matrix[i][j].filme;
			    			vector[w].actor_id1 = adiacency_matrix[i][j].actor_id1;
			    			vector[w].actor_id2 = adiacency_matrix[i][j].actor_id2;
		    			}
		    		}
		    	}
		    	QUICKSORT(0, w, vector);
		    	std::string aux;
		    	int index = 0, l;
		    	for (int j = 0; j <= w; j++){
                    index++;
                    if (index > k){
                        break;
                    }
                    l = j+1;
                    while ((vector[j].filme == vector[l].filme) && (l < w)){
                    	// ordonez alfabetic actorii care au celasi
                    	// numar de filme
                        if (vector[j].actor_id1 > vector[l].actor_id1){
                            aux = vector[j].actor_id1;
                            vector[j].actor_id1 = vector[l].actor_id1;
                            vector[l].actor_id1 = aux;
                            aux = vector[j].actor_id2;
                            vector[j].actor_id2 = vector[l].actor_id2;
                            vector[l].actor_id2 = aux;
                        } else if (vector[j].actor_id1 == vector[l].actor_id1){
                        	if (vector[j].actor_id2 > vector[l].actor_id2){
                        		aux = vector[j].actor_id2;
	                            vector[j].actor_id2 = vector[l].actor_id2;
	                            vector[l].actor_id2 = aux;
                        	}
                        }
                        l++;
                    }
                    if (vector[j].filme != 0){
                    	std::cout<<vector[j].actor_id1 << " ";
                    	std::cout << vector[j].actor_id2 << " ";
						std::cout << vector[j].filme << "\n";
                	}
                }
            	std::cout << "\n";
		    	delete[] vector;
		    }


		    bool has_movie(int src, int dst){
				if (adiacency_matrix[src][dst].filme == 0) 
					return false;
				else 
					return true;
			}


     		void QUICKSORT2(int inf, int sup, string A[] ) {
		      int i, j;
		      std::string aux, x;
		      i = inf;
		      j = sup;
		      x = A[(i + j) / 2];
		      do {
		        while ( (i < sup) && (A[i] > x) ) i++;
		        while ( (j > inf) &&(A[j] < x) ) j--;
		        if (i <= j) {
		          aux = A[i];
		          A[i] = A[j];
		          A[j] = aux;
		          i++;
		          j--;
		        }
		      } while ( i <= j );
		      if ( inf < j ) QUICKSORT2(inf, j, A);
		      if ( i < sup ) QUICKSORT2(i, sup, A);
		    }

			void BFS(int nod){ // de grad 2
				int dimensiune = pozitie;
				string culoare[dimensiune];
        		int distanta[dimensiune];
        		int i;

				for ( i=0; i<dimensiune; i++){
				        culoare[i]="alb";
				        distanta[i]=-1;
				}

				culoare[0]="gri";
				distanta[0]=0;
				queue <int> Q;

				Q.push(0);
				int v;
				int ok =0;
				int numar =0;
				string noduri[dimensiune];
				int j=0;

				while (!Q.empty()) {
				        v=Q.front();
				        Q.pop();
				        for (  i=0; i<dimensiune; i++){
				                if ( has_movie(v,i)){
				                        if (culoare[i]=="alb"){
				                        		if (distanta[v]+1 == 3){
				                        			ok = 1;
				                        			break;
				                        		}
				                        		numar++;
				                                culoare[i]="gri";

				                                distanta[i]=distanta[v]+1;
				                                if (distanta[i] == 2){
				                                	noduri[j++] = adiacency_matrix[i][i].actor_id1;	
				                                }
				                                Q.push(i);
				                        }
				                }
				        }
				        if (ok == 1){
				        	break;
				        }
				        culoare[v]="negru";
				}
				if (j == 0){
					cout<<"none\n";
					return;
				}
				QUICKSORT2(0, j-1, noduri);
				//cout <<"\nNoduri de grad 2:  ";
				for (i=0; i<j; ++i){

					cout << noduri[i]<<  "\n";
				}

			}
			// se da din structura de unde e definit pozitia
			void top_k_partners(int k, int pozitia, string actor_id){
				cout<<"Top k parteneri: \n";
				struct date *parteneri;
				int poz = 0;
				cout<<pozitie<<" pozitii\n";
				cout << adiacency_matrix[pozitia][pozitia].actor_id1<<" actor\n";
				parteneri = new struct date [pozitie - 1];
				for (int i = 0; i< pozitie; ++i){
					if (pozitia == i){
						continue;
					}
					if (adiacency_matrix[pozitia][i].filme != 0){
						parteneri[poz].actor_id1 = adiacency_matrix[pozitia][i].pereche(actor_id);
						parteneri[poz].filme = adiacency_matrix[pozitia][i].filme;
						poz++;
					}
				}
				QUICKSORT(0, poz-1, parteneri);
				
		    	std::string aux;
		    	int index = 0 ,l;
		    	for (int j = 0; j <= poz; j++){
                    index++;
                    if (index > k){
                        break;
                    }
                    l = j+1;
                    while ((parteneri[j].filme == parteneri[l].filme) && (l < poz)){
                    	// ordonez crescator actorii dupa id, daca aucelasi nr de filme
                        if (parteneri[j].actor_id1 > parteneri[l].actor_id1){
                            aux = parteneri[j].actor_id1;
                            parteneri[j].actor_id1 = parteneri[l].actor_id1;
                            parteneri[l].actor_id1 = aux;
                        }
                        l++;
                    }
                    if (parteneri[j].filme != 0){
                    	std::cout<<parteneri[j].actor_id1 << " ";
                	}
                }
            	std::cout << "\n";
		    	delete[] parteneri;
		    }
	};
#endif  // GRAPH_H_
