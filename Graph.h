/*Graph.h*/

#ifndef GRAPH_H
#define GRAPH_H

#include<stack>
#include<queue>
#include<list>
#include "Hash.h"
using namespace std;

static const double INF = 9999999;

template<class DT>
class Graph {
private:
    double **adjMatrix;
    //Stores minimum cost path from point i to point j
    list<DT> **APSPMatrix;
    //Stores minimum hop path from point i to point j
    list<DT> **minHopMatrix;
    //Stores MST path from point i to point j
    list<DT> **MSTMatrix;
    int Vertices;
public:
    //constructor
    Graph(int vertices);
    int getVertices();
    void addEdge(int src, int des, double weight);
    void removeEdge(int src, int des);
    int degree(int src);
    void print();

    /* | Algorithms | */
    /* V    used    V */


    /*---------------------------------------------------*/

    //builds shortest Distance paths, min hops paths, and MST Paths
    void buildPaths(Hash<DT> h);
    int findMin(double dist[], list<int> Q);
    bool lcon(int find, list<int> l);

    /*---------------------------------------------------*/

    //minimum cost spanning tree from src to all other points
    void prims(int src, Hash<DT> h);
    //finds path in O(1) time then displays path
    void MSTpath(int src, int des);

    /*---------------------------------------------------*/

    //single source shortest path
    void dijkstra(int src, Hash<DT> h);
    //finds path in O(1) time then displays path
    void ShortestPath(int src, int des);

    /*---------------------------------------------------*/

    //Minimum number of hops from node to node
    void BreadthFirstSearch(int src, Hash<DT> h);
    //finds path in O(1) time then displays path
    void ShortestHop(int src, int des);

    /*---------------------------------------------------*/

    //Uses Floyd-Warshall algorithm to find distance
    double minDist(int src, int des);

};

template<class DT>
Graph<DT>::Graph(int vertices) {
    Vertices = vertices;
    adjMatrix = new double*[vertices];
    APSPMatrix = new list<DT>*[vertices];
    minHopMatrix = new list<DT>*[vertices];
    MSTMatrix = new list<DT>*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjMatrix[i] = new double[vertices];
        APSPMatrix[i] = new list<DT>[vertices];
        minHopMatrix[i] = new list<DT>[vertices];
        MSTMatrix[i] = new list<DT>[vertices];
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = INF;
        }
    }
}

template<class DT>
int Graph<DT>::getVertices() { return Vertices; }

template<class DT>
void Graph<DT>::addEdge(int src, int des, double weight) {
    if (src < Vertices && des < Vertices && src >= 0 && des >= 0) {
        adjMatrix[src][des] = weight;
        adjMatrix[des][src] = weight;
    }
}

template<class DT>
void Graph<DT>::removeEdge(int src, int des) {
    if (src < Vertices && des < Vertices  && src >= 0 && des >= 0) {
        adjMatrix[src][des] = INF;
        adjMatrix[des][src] = INF;
    }
}

template<class DT>
int Graph<DT>::degree(int src) {
    if (src < 0 || src >= Vertices)
        return -1;
    int num = 0;
    int degree = 0;
    for (int i = 0; i < Vertices; i++)
        if (adjMatrix[src][i] != INF)
            num++;
    return num;
}

template<class DT>
void Graph<DT>::print() {
    for (int i = 0; i < Vertices; i++) {
        for (int j = 0; j < Vertices; j++) {
            if (adjMatrix[i][j] == INF)
                cout << "X\t";
            else
                cout << adjMatrix[i][j] << "\t";
        }
        cout << endl;
    }
}

template<class DT>
void Graph<DT>::buildPaths(Hash<DT> h) {
    //Builds the paths with all the algorithms
    //saves them in their respective list matrices
    for (int i = 0; i < Vertices; i++) {
        dijkstra(i, h);//APSPMatrix
        prims(i, h);//MSTMatrix
        BreadthFirstSearch(i, h);//MinHopMatrix
    }
}

template<class DT>
void Graph<DT>::prims(int src, Hash<DT> h) {
    if (src >= Vertices || src < 0)
        return;
    list<int> Q;
    double *dist = new double[Vertices];
    DT *prev = new DT[Vertices];

    for (int v = 0; v < Vertices; v++) {
        dist[v] = INF;
        prev[v] = DT();
        Q.push_back(v);
    }
    int u;
    dist[src] = 0;
    while (!Q.empty()) {
        u = findMin(dist, Q);
        Q.remove(u);
        for (int v = 0; v < Vertices; v++) {
            if (adjMatrix[u][v] != INF) {
                if (lcon(v, Q) && adjMatrix[u][v] < dist[v]) {
                    dist[v] = adjMatrix[u][v];
                    prev[v] = h[u];
                }
            }
        }

    }

    //sets the paths in relevant index of list matrix
    for (int j = 0; j < Vertices; j++) {
        if (src != j && degree(j) != 0) {
            MSTMatrix[src][j].push_front(prev[j]);
            while (MSTMatrix[src][j].front() != DT())
                //pushes the parent at the index which corresponds to the front of this list to the front of this list
                MSTMatrix[src][j].push_front(prev[h.hash(MSTMatrix[src][j].front())]);
            MSTMatrix[src][j].pop_front();
            MSTMatrix[src][j].push_back(h[j]);
        }
    }

}

template<class DT>
void Graph<DT>::MSTpath(int src, int des) {
    if (src < 0 || des < 0 || src >= Vertices || des >= Vertices)
        return;
    for (DT x : MSTMatrix[src][des])
        cout << x << "   ";
    cout << endl;
}

template<class DT>
void Graph<DT>::dijkstra(int src, Hash<DT> h) {
    if (src >= Vertices || src < 0)
        return;
    list<int> Q;
    double *dist = new double[Vertices];
    DT *prev = new DT[Vertices];

    for (int v = 0; v < Vertices; v++) {
        dist[v] = INF;
        prev[v] = DT();
        Q.push_back(v);
    }
    int u;
    dist[src] = 0;
    while (!Q.empty()) {
        u = findMin(dist, Q);
        Q.remove(u);
        for (int v = 0; v < Vertices; v++) {
            if (adjMatrix[u][v] != INF) {
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = h[u];
                }
            }
        }

    }

    //sets the paths in relevant index of list matrix
    for (int j = 0; j < Vertices; j++) {
        if (src != j && degree(j) != 0) {
            APSPMatrix[src][j].push_front(prev[j]);
            while (APSPMatrix[src][j].front() != DT())
                //pushes the parent at the index which corresponds to the front of this list to the front of this list
                APSPMatrix[src][j].push_front(prev[h.hash(APSPMatrix[src][j].front())]);
            APSPMatrix[src][j].pop_front();
            APSPMatrix[src][j].push_back(h[j]);
        }
    }

}

template<class DT>
int Graph<DT>::findMin(double dist[], list<int> Q) {
    //finds the minimum index of array dist[]
    //that is also present in the list Q
    double min = INF;
    int mini = -1;
    for (int i = 0; i < Vertices; i++) {
        if (dist[i] < min && lcon(i, Q)) {
            min = dist[i];
            mini = i;
        }
    }
    return mini;
}

template<class DT>
bool Graph<DT>::lcon(int find, list<int> l) {
    //checks if the index is present in list Q
    for (int x : l)
        if (x == find)
            return true;
    return false;
}

template<class DT>
void Graph<DT>::ShortestPath(int src, int des) {
    if (src < 0 || des < 0 || src >= Vertices || des >= Vertices)
        return;
    for (DT x : APSPMatrix[src][des])
        cout << x << "   ";
    cout << endl;
}

template<class DT>
void Graph<DT>::BreadthFirstSearch(int src, Hash<DT> h) {
    if (src >= Vertices || src < 0)
        return;

    queue<int> Q;
    bool *visited = new bool[Vertices];
    bool *inQ = new bool[Vertices];
    DT *prev = new DT[Vertices];
    for (int i = 0; i < Vertices; i++) {
        visited[i] = false;//black
        inQ[i] = false;//gray
        prev[i] = DT();
    }

    int u;
    prev[src] = DT();
    Q.push(src);
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        visited[u] = true;
        for (int v = 0; v < Vertices; v++) {
            if (adjMatrix[u][v] != INF) {
                if (!visited[v] && !inQ[v]) {
                    Q.push(v);
                    inQ[v] = true;
                    prev[v] = h[u];
                }
            }
        }
    }

    //sets the paths in relevant index of list matrix
    for (int j = 0; j < Vertices; j++) {
        if (src != j && degree(j) != 0) {
            minHopMatrix[src][j].push_front(prev[j]);
            while (minHopMatrix[src][j].front() != DT())
                //pushes the parent at the index which corresponds to the front of this list to the front of this list
                minHopMatrix[src][j].push_front(prev[h.hash(minHopMatrix[src][j].front())]);
            minHopMatrix[src][j].pop_front();
            minHopMatrix[src][j].push_back(h[j]);
        }
    }

}

template<class DT>
void Graph<DT>::ShortestHop(int src, int des) {
    if (src < 0 || des < 0 || src >= Vertices || des >= Vertices)
        return;
    for (DT x : minHopMatrix[src][des])
        cout << x << "   ";
    cout << endl;
}

template<class DT>
double Graph<DT>::minDist(int src, int des) {
    //Floyd - Warshall algorithm to find minimum distance between 2 vertices
    if (src >= Vertices && des >= Vertices && src < 0 && des < 0)
        return INF;
    double **dist = new double*[Vertices];
    for (int i = 0; i < Vertices; i++) {
        dist[i] = new double[Vertices];
        for (int j = 0; j < Vertices; j++) {
            dist[i][j] = adjMatrix[i][j];
        }
    }
    for (int k = 0; k < Vertices; k++) {
        for (int i = 0; i < Vertices; i++) {
            for (int j = 0; j < Vertices; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    return dist[src][des];

}
#endif // !GRAPH_H