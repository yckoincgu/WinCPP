#include <iostream>
#include <list>
#include <set>
#include<limits.h>
/*   (*it)->nodeID   */
using namespace std;


class Vertex{
private:
public:
    bool visited; 
    std::set<Vertex*> neighbors;    // knowledge set
	/* <Vertice*> is used as <typename T> in the whole program
		templates provide type safety and flexibility 
		raw pointers is efficient
	*/
    int nodeID;  

    Vertex(int nodeID):nodeID(nodeID){
      visited=false;
      std::cout<< "vertex is "<< nodeID << std::endl;
    };
    
    void printVertexNeighbors(){
    	std::cout<<"Node "<< nodeID <<" has neighbors ";
    	for(std::set<Vertex*>::iterator it=neighbors.begin(); it!=neighbors.end(); it++)
			std::cout<<(*it)->nodeID<<", ";
		
		std::cout<<std::endl;	
	}
};

template <typename T>
class Edge{
public:
    T p,q;
    std::set<T> twoNodes;	// no directions, data structure
    
    Edge(T source_V, T destinate_V):p(source_V),  q(destinate_V)
    {
        p->neighbors.insert(q);
        q->neighbors.insert(p);
		twoNodes.insert(p); twoNodes.insert(q);
        //std::cout<< "E q is "<< q->nodeID << std::endl;        
    };

};



template <typename T>
class Graph {
	public:
    std::set<T> verticesSet;
    /*	std::set<Edge<T>* > eSet;   std::set<Edge<T> > eSet; 
    	Use space between closing angle brackets in std::set<Edge<T> > 
		for older compiler compatibility.
	*/ 
	std::set<set<T>> edgesSet; // containing undirected edges with 2 vertices

	
	bool isEulerPath(){		// definition
		bool flag=false;
		int oddVerticeNumber=0;
		for(typename std::set<T>::iterator it=verticesSet.begin(); it!=verticesSet.end(); ++it)
			if((*it)->neighbors.size() % 2 != 0) oddVerticeNumber++;
			 
		std::cout<<"oddVerticeNumber is " << oddVerticeNumber<< endl;	
		if(oddVerticeNumber % 2 == 0) {
			flag=true;
			std::cout<<"This graph is an euler path" <<endl;
		}
		
		return flag;
			
	}	
	T getStartVertex(){	// definition
		T x;
		unsigned long long min=UINT_MAX;
		for(typename std::set<T>::iterator it=verticesSet.begin(); it!=verticesSet.end(); ++it)
			if((*it)->neighbors.size() % 2 != 0 && min > (*it)->neighbors.size()) {
				min=(*it)->neighbors.size();
				x=(*it);
			}
		std::cout<<"The start vertice is "<< x->nodeID <<endl;
		return x;
	}
	void printEulerPath(T startVertice){	// design based on definition
		T nextVertex;	// operation space
		std::set<T> targetEdge; // knowledge set
		for(typename std::set<T>::iterator it=verticesSet.begin(); it!=verticesSet.end(); ++it)
			if((*it)== startVertice) {
				//std::cout<<(*startVertice).nodeID <<" has unvisited neighbors  ";
				for(std::set<Vertex*>::iterator it=(*startVertice).neighbors.begin(); it!=(*startVertice).neighbors.end(); ++it){
					targetEdge.clear();
					targetEdge.insert(startVertice); targetEdge.insert(*it);
					if (edgesSet.find(targetEdge) != edgesSet.end()) {nextVertex=(*it); break;}
					//std::cout<<nextVertex->nodeID <<", ";
				} 
				//std::cout<<endl;
			}
			printEdges(startVertice, nextVertex);
			edgesSet.erase(targetEdge);
			if(!edgesSet.empty()) printEulerPath(nextVertex);

		}
	
	void printEdges(T startVertice, T endVertice){
		std::cout
			<<" vistited edge (" 
			<<startVertice->nodeID
			<<","<<endVertice->nodeID
			<< ")"
			<<endl;	
	}
  
};

int main() {
	
    Vertex v0(0), v1(1), v2(2), v3(3);		// user designed class
    
    Edge<Vertex*> 
    e1(&v0, &v1), e11(&v1, &v0),
    e2(&v0, &v2), e12(&v2, &v0),
    e3(&v1, &v2), e13(&v2, &v1),
    e4(&v2, &v3), e14(&v3, &v2);
    //v0.printVerticeNeighbors();
    //v1.printVerticeNeighbors();
    
    
    Graph<Vertex*> g;
    g.verticesSet.insert(&v0);	
    g.verticesSet.insert(&v1);
    g.verticesSet.insert(&v2);
    g.verticesSet.insert(&v3);
    


    g.edgesSet.insert(e1.twoNodes); g.edgesSet.insert(e11.twoNodes);
    g.edgesSet.insert(e2.twoNodes); g.edgesSet.insert(e12.twoNodes);
    g.edgesSet.insert(e3.twoNodes); g.edgesSet.insert(e13.twoNodes);
    g.edgesSet.insert(e4.twoNodes); g.edgesSet.insert(e14.twoNodes);



	Vertex* x;
	if(g.isEulerPath()){
		x=g.getStartVertex();
    	//std::cout<<"Double check the start vertice "<< x->nodeID <<endl;
    	g.printEulerPath(x);}
	else std::cout<<"This is not a euler path"<<endl;
    


  return 0;
}
