#include <iostream>
#include <list>
#include <set>
/*   (*it)->nodeID   */
using namespace std;

class Vertice{
private:
public:
    bool visited=false; 
    std::list<Vertice*> neighbors;
    
    int nodeID;    
    Vertice(int nodeID):nodeID(nodeID){
      //std::cout<< "A p is "<< nodeID << std::endl;
    };
    
    void printList(){
    	std::cout<<"Node "<< nodeID <<" has neighbors ";
    	for(std::list<Vertice*>::iterator 
		    it=neighbors.begin(); it!=neighbors.end(); it++){
				std::cout<<(*it)->nodeID<<", ";
			}
		std::cout<<std::endl;	
	}
};

template <typename T>
class Edge{
public:
    T p,q;
    
    Edge(T source_V, T destinate_V):p(source_V), q(destinate_V)
    {
        p->neighbors.push_back(q);
        q->neighbors.push_back(p);
        //std::cout<< "E q is "<< q->nodeID << std::endl;        
    };
};

template <typename T>
class Graph {
  public:
  std::set<T> vSet;
  std::set<Edge<T>*> eSet;
  void bfs(T startVertex){
		  if (vSet.find(startVertex) != vSet.end()) findNeighbors(startVertex);
	}
  
	bool isVisited(T startVertex){
		if((*startVertex).visited) 
			return true; 
	}
	bool findNeighbors(T startVertex){
		if (isVisited(startVertex)) return true;
		
		std::list<Vertice*> theRest;
		(*startVertex).visited=true;
		T nextVertex;
		
    	std::cout<< "visited vertice "<< (*startVertex).nodeID<<endl;;
		for(std::list<Vertice*>::iterator it=(*startVertex).neighbors.begin(); it!=(*startVertex).neighbors.end(); ++it){
				if (isVisited(*it)) continue;
				theRest.push_back(*it); //std::cout<<(*it)->nodeID <<" ";
			} 
		for(std::list<Vertice*>::iterator it=(theRest).begin(); it!=(theRest).end(); ++it)
			findNeighbors(*it);
		
		return true;				
	}
  
};

int main() {
	
    Vertice v0(0), v1(1), v2(2), v3(3), v4(4);
    Edge<Vertice*> 
    e1(&v0, &v1),
    e2(&v0, &v2),
    e3(&v1, &v3),
    e4(&v1, &v4),
    e5(&v2, &v4);
    
    Graph<Vertice*> g;
    g.vSet.insert(&v0);
    g.vSet.insert(&v1);
    g.vSet.insert(&v2);
    g.vSet.insert(&v3);
    g.vSet.insert(&v4);


    g.eSet.insert(&e1);
    g.eSet.insert(&e2);
    g.eSet.insert(&e3);
    g.eSet.insert(&e4);
    g.eSet.insert(&e5);
    g.bfs(&v1);
  
    int i;
    std::cin >> i;
 


  return 0;
}
