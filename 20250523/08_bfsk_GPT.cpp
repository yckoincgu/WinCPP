#include <iostream>
#include <list>
#include <set>
#include <queue>

using namespace std;

class Vertex {
public:
    bool visited = false;
    list<Vertex*> neighbors;
    int nodeID;

    Vertex(int nodeID) : nodeID(nodeID) {}

    void printList() {
        cout << "Node " << nodeID << " has neighbors ";
        for (list<Vertex*>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
            cout << (*it)->nodeID << ", ";
        }
        cout << endl;
    }
};

template <typename T>
class Edge {
public:
    T p;
    T q;

    Edge(T source_V, T destinate_V) : p(source_V), q(destinate_V) {
        p->neighbors.push_back(q);
        q->neighbors.push_back(p);
    }
};

template<typename T, typename U>
class Graph {
public:
    set<T> verticesSet;
    set<U> edgesSet;

    void bfs(T startVertex) {
        if (verticesSet.find(startVertex) == verticesSet.end()) return;
        
        queue<T> q;
        startVertex->visited = true;
        q.push(startVertex);

        while (!q.empty()) {
            T current = q.front();
            q.pop();
            cout << "Visited vertex " << current->nodeID << endl;

            for (list<Vertex*>::iterator neighbor= current->neighbors.begin(); 
						  neighbor!=current->neighbors.end(); ++neighbor) {
                if (!(*neighbor)->visited) {
                    (*neighbor)->visited = true;
                    q.push((*neighbor));
                }
            }
        }
    }
};

int main() {
    Vertex v0(0), v1(1), v2(2), v3(3), v4(4), v5(5);
    Edge<Vertex*> 
    e1(&v0, &v1), e11(&v1, &v0), 
    e2(&v0, &v2), e12(&v2, &v0), 
    e3(&v1, &v3), e13(&v3, &v1),
    e4(&v1, &v4), e14(&v4, &v1),
    e5(&v2, &v4), e15(&v4, &v2),
    e6(&v3, &v5), e16(&v5, &v3);

    Graph<Vertex*, Edge<Vertex*>*> g;
    g.verticesSet.insert(&v0);
    g.verticesSet.insert(&v1);
    g.verticesSet.insert(&v2);
    g.verticesSet.insert(&v3);
    g.verticesSet.insert(&v4);
    g.verticesSet.insert(&v5);

    g.edgesSet.insert(&e1);
    g.edgesSet.insert(&e2);
    g.edgesSet.insert(&e3);
    g.edgesSet.insert(&e4);
    g.edgesSet.insert(&e5);
    g.edgesSet.insert(&e6);
    g.edgesSet.insert(&e11);
    g.edgesSet.insert(&e12);
    g.edgesSet.insert(&e13);
    g.edgesSet.insert(&e14);
    g.edgesSet.insert(&e15);
    g.edgesSet.insert(&e16);    

    g.bfs(&v1);

    return 0;
}
