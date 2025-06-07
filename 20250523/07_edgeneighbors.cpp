#include <iostream>
#include <set>
using namespace std;

class Vertex {
public:
    bool visited = false;
    std::set<Vertex*> neighbors;
    int nodeID;
    Vertex(int nodeID) : nodeID(nodeID) {}

    void printList() {
        std::cout << "Node " << nodeID << " has neighbors ";
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            std::cout << (*it)->nodeID << ", ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
class Edge {
public:
    T p, q;
    std::set<Edge*> neighbors;
    bool visited=false;
    Edge(T source_V, T destinate_V) : p(source_V), q(destinate_V) {
        p->neighbors.insert(q);
        q->neighbors.insert(p);
    }

    void printEdgeNeighbors() {
        std::cout << "(" << p->nodeID << ", " << q->nodeID << ") has neighbors: ";
        for (auto e = neighbors.begin(); e != neighbors.end(); ++e) {
            std::cout << "(" << (*e)->p->nodeID << ", " << (*e)->q->nodeID << ") ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
class Graph {
public:
    std::set<T> verticesSet;
    std::set<Edge<T>*> edgesSet;
    
    void buildEdgeNeighbors() {
        for (auto e1 = edgesSet.begin(); e1 != edgesSet.end(); ++e1) {
            std::cout<< "e1(" << (*e1)->p->nodeID<<"," <<(*e1)->q->nodeID<<") has neighbors: ";
            for (auto e2 = edgesSet.begin(); e2 != edgesSet.end(); ++e2) {
                if (*e1 != *e2  && (        // 
                    ((*e1)->p == (*e2)->p) ||
                    ((*e1)->p == (*e2)->q) ||
                    ((*e1)->q == (*e2)->p) ||
                    ((*e1)->q == (*e2)->q))) 
                {
                    (*e1)->neighbors.insert(*e2);
                    std::cout<< "e2(" << (*e2)->p->nodeID<<"," <<(*e2)->q->nodeID<<"), ";
                }
            }
            std::cout<<  std::endl;
        }
    }
};

int main() {
    Vertex v0(0), v1(1), v2(2), v3(3), v4(4);
    Edge<Vertex*> e1(&v0, &v1), e2(&v0, &v2), e3(&v1, &v3), e4(&v1, &v4), e5(&v2, &v4);

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
    g.buildEdgeNeighbors();

    int i;
    std::cin >> i;

    return 0;
}
