#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>

using namespace std;

class Vertex {
public:
    bool visited = false;
    std::set<Vertex*> neighbors;
    int nodeID;
    int shortestDistanceFromStart;

    Vertex(int nodeID) : nodeID(nodeID), shortestDistanceFromStart(INT_MAX / 2) {}
    Vertex() : shortestDistanceFromStart(INT_MAX / 2) {}
    void printList() {
        std::cout << "Node " << nodeID << " has neighbors ";
        for (std::set<Vertex*>::iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
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
    std::set<T> elements;
    int distance;
    bool visited = false;

    Edge(T source_V, T destinate_V, int distance) : p(source_V), q(destinate_V), distance(distance) {
        p->neighbors.insert(q);
        q->neighbors.insert(p);
        elements.insert(p);
        elements.insert(q);
    }
    Edge() {}

    void printEdgeNeighbors() {
        std::cout << "(" << p->nodeID << ", " << q->nodeID << ") has neighbors: ";
        for (typename std::set<Edge<T>*>::iterator e = neighbors.begin(); e != neighbors.end(); ++e) {
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

    int getEdgeDistance(T startVertice, T endVertice) {
        int edgeDistance = INT_MAX / 2;  // a value beyond scope
        std::set<T> searchEdge;
        searchEdge.insert(startVertice);
        searchEdge.insert(endVertice);
        for (typename std::set<Edge<T>*>::iterator targetEdge = edgesSet.begin(); targetEdge != edgesSet.end(); ++targetEdge)
            if ((*targetEdge)->signature == searchEdge) edgeDistance = (*targetEdge)->distance;

        return edgeDistance;
    }

    T findShortestPath(T startVertice, T endVertice) {
        std::cout << "findShortestPath ..." << std::endl;

        if (verticesSet.find(startVertice) == verticesSet.end()) return NULL;

        queue<Vertex*> q;
        startVertice->shortestDistanceFromStart = 0;  // initial setting
        q.push(startVertice);
        int nextDistance;

        while (!q.empty()) {
            Vertex* current = q.front();
            q.pop();

            cout << "Visited vertex " << current->nodeID << endl;
            for (set<Vertex*>::iterator neighbor = current->neighbors.begin();
                neighbor != current->neighbors.end(); ++neighbor) {
                if ((*neighbor) == startVertice) continue;

                nextDistance = getEdgeDistance(current, (*neighbor));
                if (current->shortestDistanceFromStart + nextDistance >= (*neighbor)->shortestDistanceFromStart) continue;
                (*neighbor)->shortestDistanceFromStart = current->shortestDistanceFromStart + nextDistance;
                q.push((*neighbor));
            }
        }

        return endVertice;
    }

    void bfs(Vertex* startVertice) {
        if (verticesSet.find(startVertice) == verticesSet.end()) return;

        queue<Vertex*> q;
        startVertice->visited = true;
        q.push(startVertice);

        while (!q.empty()) {
            Vertex* current = q.front();
            q.pop();

            cout << "Visited vertex " << current->nodeID << endl;
            for (set<Vertex*>::iterator neighbor = current->neighbors.begin();
                neighbor != current->neighbors.end(); ++neighbor) {
                if (!(*neighbor)->visited) {
                    (*neighbor)->visited = true;
                    q.push((*neighbor));
                }
            }
        }
    }

    void buildEdgeNeighbors() {
        for (typename std::set<Edge<T>*>::iterator e1 = edgesSet.begin(); e1 != edgesSet.end(); ++e1) {
            std::cout << "e1(" << (*e1)->p->nodeID << "," << (*e1)->q->nodeID << ") has neighbors: ";
            for (typename std::set<Edge<T>*>::iterator e2 = edgesSet.begin(); e2 != edgesSet.end(); ++e2) {
                if (*e1 != *e2 && (
                    ((*e1)->p == (*e2)->p) ||
                    ((*e1)->p == (*e2)->q) ||
                    ((*e1)->q == (*e2)->p) ||
                    ((*e1)->q == (*e2)->q))) {
                    (*e1)->neighbors.insert(*e2);
                    std::cout << "e2(" << (*e2)->p->nodeID << "," << (*e2)->q->nodeID << "), ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 1}
    };
    int rowCount = mat.size();
    int columnCount = mat[0].size();

    Graph<Vertex*> g;

    Vertex node[rowCount];
    for (int i = 0; i < rowCount; i++) {
        node[i].nodeID = i;
        node[i].shortestDistanceFromStart = INT_MAX / 2;  // a value beyond scope
        g.verticesSet.insert(&node[i]);
    }

    // Initialize edges with correct size
    vector<vector<Edge<Vertex*>*>> edges(rowCount, vector<Edge<Vertex*>*>(rowCount, nullptr));
    std::cout<< "XXXXXXXX  edges size " << edges.size() << std::endl;

    
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rowCount; j++) { // include all possible edges
            if (mat[i][j] != 0) {
                edges[i][j] = new Edge<Vertex*>(&node[i], &node[j], mat[i][j]);
                std::cout << "edges[" << i << "," << j << "] " << std::endl;
                g.edgesSet.insert(edges[i][j]);
            }
        }
    }

    g.buildEdgeNeighbors();
    g.findShortestPath(&node[0], &node[4]);

    // Clean up dynamically allocated edges
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            if (edges[i][j] != nullptr) {
                delete edges[i][j];
            }
        }
    }

    int i;
    std::cin >> i;

    return 0;
}
