#include <iostream>
#include <list>
#include <set>
/*   (*it)->nodeID   */
using namespace std;

class Vertex{
private:
public:
    bool visited=false; 
    std::list<Vertex*> neighbors;
    
    int nodeID;    
    Vertex(int nodeID):nodeID(nodeID){
      //std::cout<< "A p is "<< nodeID << std::endl;
    };
    
    void printList(){
    	std::cout<<"Node "<< nodeID <<" has neighbors ";
    	for(std::list<Vertex*>::iterator 
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
  std::set<T> verticesSet;
  std::set<Edge<T>*> edgesSet;
  void bfs(T startVertex){
		  if (verticesSet.find(startVertex) != verticesSet.end()) findNeighbors(startVertex);
	}
  
	bool isVisited(T startVertex){
		if((*startVertex).visited) 
			return true; 
	}
	bool findNeighbors(T startVertex){
		if (isVisited(startVertex)) return true;
		
		std::list<Vertex*> theRest;
		(*startVertex).visited=true;
		T nextVertex;
		
    	std::cout<< "visited vertice "<< (*startVertex).nodeID<<endl;;
		for(std::list<Vertex*>::iterator it=(*startVertex).neighbors.begin(); it!=(*startVertex).neighbors.end(); ++it){
				if (isVisited(*it)) continue;
				theRest.push_back(*it); //std::cout<<(*it)->nodeID <<" ";
			} 
		for(std::list<Vertex*>::iterator it=(theRest).begin(); it!=(theRest).end(); ++it)
			findNeighbors(*it);
		
		return true;				
	}
  
};

int main() {
	
    Vertex v0(0), v1(1), v2(2), v3(3), v4(4);
    Edge<Vertex*> 
    e1(&v0, &v1),
    e2(&v0, &v2),
    e3(&v1, &v3),
    e4(&v1, &v4),
    e5(&v2, &v4);
    
    Graph<Vertex*> g;
    g.verticesSet.insert(&v0);
    g.verticesSet.insert(&v1);
    g.verticesSet.insert(&v2);
    g.verticesSet.insert(&v3);
    g.verticesSet.insert(&v4);


    g.edgesSet.insert(&e1);
    g.edgesSet.insert(&e2);
    g.edgesSet.insert(&e3);
    g.edgesSet.insert(&e4);
    g.edgesSet.insert(&e5);
    g.bfs(&v1);
  
    int i;
    std::cin >> i;
 


  return 0;
}
