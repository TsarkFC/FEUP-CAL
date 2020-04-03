/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<vector<double>> adjMatrix;
    vector<vector<double>> minMatrix;
    vector<vector<double>> preMatrix;


public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPathTo(const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++){
        (*it)->dist = DBL_MAX;
        (*it)->path = NULL;
	}

	Vertex<T>* s = findVertex(orig);
	s->dist = 0;
	queue<Vertex<T>*> q;
	q.push(s);

	while (!q.empty()){
	    Vertex<T>* v = q.front();
	    q.pop();

	    for (auto it = v->adj.begin(); it != v->adj.end(); it++){
            if ((*it).dest->getDist() == DBL_MAX) {
                q.push((*it).dest);
                (*it).dest->dist = v->getDist() + 1;
                (*it).dest->path = v;
            }
	    }
	}
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    MutablePriorityQueue<Vertex<T>> q;
    Vertex<T>* s = findVertex(origin);

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++){
        (*it)->dist = DBL_MAX;
        (*it)->path = NULL;
    }

    s->dist = 0;
    q.insert(s);
    Vertex<T>* v;

    while (!q.empty()){
        v = q.extractMin();

        for (Edge<T> w : v->adj){
            if (w.dest->getDist() > v->getDist() + w.weight){
                double dist = w.dest->getDist();
                w.dest->dist = v->getDist() + w.weight;
                w.dest->path = v;

                if (dist == DBL_MAX)
                    q.insert(w.dest);
                else
                    q.decreaseKey(w.dest);
            }

        }
    }

}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    Vertex<T>* s = findVertex(orig);

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++){
        (*it)->dist = DBL_MAX;
        (*it)->path = NULL;
    }

    queue<Vertex<T>*> q;
    s->dist = 0;
    q.push(s);

    while (!q.empty()) {
        Vertex<T>* v = q.front();
        q.pop();
        for (Edge<T> w : v->adj) {
            if (w.dest->getDist() > v->getDist() + w.weight) {
                w.dest->dist = v->getDist() + w.weight;
                w.dest->path = v;
                q.push(w.dest);
            }
        }
    }

    q.push(s);
    while (!q.empty()) {
        Vertex<T>* v = q.front();
        q.pop();
        for (Edge<T> w : v->adj) {
            if (w.dest->dist > v->dist + w.weight) {
                cout << "there are cycles of negative weight" << endl;
                return;
            }
        }
    }

}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T>* v = findVertex(dest);

	while(v->dist != 0){
        res.push_back(v->info);
        v = v->path;
	}
	res.push_back(v->info);

	reverse(res.begin(), res.end());

	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    for (int i = 0; i <= vertexSet.size(); i++){
        vector<double> temp;
        for (int j = 0; j <= vertexSet.size(); j++){
            if (j == i) temp.push_back(0);
            else temp.push_back(DBL_MAX);
        }
        adjMatrix.push_back(temp);
    }

    for (Vertex<T>* v : vertexSet){
        for (Edge<T> edge : v->adj){
            adjMatrix[v->getInfo()][edge.dest->getInfo()] = edge.weight;
        }
    }

    for (int i = 0; i <= vertexSet.size(); i++){
        vector<double> temp;
        for (int j = 0; j <= vertexSet.size(); j++){
            temp.push_back(i);
        }
        preMatrix.push_back(temp);
    }

    minMatrix = adjMatrix;
    vector<vector<double>> temp = minMatrix;

    for (int k = 1; k <= vertexSet.size(); k++){
        for (int i = 1; i <= vertexSet.size(); i++){
            for (int j = 1; j <= vertexSet.size(); j++){
                if (minMatrix[i][j] > minMatrix[i][k] + minMatrix[k][j]) {
                    temp[i][j] = minMatrix[i][k] + minMatrix[k][j];
                    preMatrix[i][j] = preMatrix[k][j];
                }
            }
        }
        minMatrix = temp;
    }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;

    int num = dest;

    while(num != orig){
        res.push_back(num);

        num = preMatrix[orig][num];
    }
    res.push_back(orig);
    reverse(res.begin(), res.end());

    return res;
}


#endif /* GRAPH_H_ */
