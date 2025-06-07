#include <iostream>
#include <list>
#include <set>
#include <limits.h>

using namespace std;

class Vertex {
public:
    bool visited;
    std::set<Vertex*> neighbors;
    int nodeID;

    Vertex(int nodeID) : nodeID(nodeID), visited(false) {
        std::cout << "Vertex created: " << nodeID << std::endl;
    }

    void addNeighbor(Vertex* neighbor) {
        neighbors.insert(neighbor);
    }

    int degree() const {
        return neighbors.size();
    }

    void printNeighbors() const {
        std::cout << "Node " << nodeID << " has neighbors ";
        for (Vertex* neighbor : neighbors) {
            std::cout << neighbor->nodeID << ", ";
        }
        std::cout << std::endl;
    }
};

class Edge {
public:
    std::set<Vertex*> vertices;

    Edge(Vertex* source, Vertex* destination) {
        vertices.insert(source);
        vertices.insert(destination);
        source->addNeighbor(destination);
        destination->addNeighbor(source);
    }
};

class Graph {
public:
    std::set<Vertex*> vertices;
    std::set<std::set<Vertex*>> edges;

    void addEdge(Vertex* source, Vertex* destination) {
        Edge edge(source, destination);
        edges.insert(edge.vertices);
    }

    bool isEulerPath() const {
        int oddDegreeCount = 0;
        for (const auto& vertex : vertices) {
            if (vertex->degree() % 2 != 0) {
                oddDegreeCount++;
            }
        }
        std::cout << "Number of vertices with odd degree: " << oddDegreeCount << std::endl;
        return oddDegreeCount == 0 || oddDegreeCount == 2;
    }

    Vertex* getStartVertice() const {
        Vertex* start = nullptr;
        for (const auto& vertex : vertices) {
            if (vertex->degree() % 2 != 0) {
                if (!start || vertex->degree() < start->degree()) {
                    start = vertex;
                }
            }
        }
        if (!start) {
            start = *vertices.begin();
        }
        std::cout << "The start vertex is " << start->nodeID << std::endl;
        return start;
    }

    void printEulerPath(Vertex* startVertice) {
        std::list<Vertex*> path;
        findEulerPath(startVertice, path);
        for (auto it = path.begin(); it != path.end(); ++it) {
            auto nextIt = std::next(it);
            if (nextIt != path.end()) {
                std::cout << "Visited edge (" << (*it)->nodeID << "," << (*nextIt)->nodeID << ")" << std::endl;
            }
        }
    }

private:
    void findEulerPath(Vertex* currentVertex, std::list<Vertex*>& path) {
        for (auto it = currentVertex->neighbors.begin(); it != currentVertex->neighbors.end();) {
            Vertex* neighbor = *it;
            std::set<Vertex*> edge = { currentVertex, neighbor };
            if (edges.find(edge) != edges.end()) {
                edges.erase(edge);
                currentVertex->neighbors.erase(it++);
                neighbor->neighbors.erase(currentVertex);
                findEulerPath(neighbor, path);
            } else {
                ++it;
            }
        }
        path.push_front(currentVertex);
    }
};

int main() {
    Vertex v0(0), v1(1), v2(2), v3(3);

    Graph g;
    g.vertices.insert(&v0);
    g.vertices.insert(&v1);
    g.vertices.insert(&v2);
    g.vertices.insert(&v3);

    g.addEdge(&v0, &v1);
    g.addEdge(&v0, &v2);
    g.addEdge(&v1, &v2);
    g.addEdge(&v2, &v3);

    if (g.isEulerPath()) {
        Vertex* start = g.getStartVertice();
        g.printEulerPath(start);
    } else {
        std::cout << "This graph does not have an Euler path" << std::endl;
    }


    int i;
    std:cin>>i;
    return 0;
}
