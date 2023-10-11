#include "graph.h"
#include <iostream>
#include <fstream>
using namespace std;

void error(string msg){
    cout << "ERROR: " << msg << endl;
}

DisjointSet::DisjointSet(int numVertices){
    cout<<numVertices<<endl;
    for (int i = 0; i < numVertices; ++i)
        makeSet(i);
}

void DisjointSet::makeSet(Vertex x){
    subsets.emplace_back(Set{x});
  
}

Vertex DisjointSet::findSet(Vertex x){
    Vertex& parent = subsets[x].parent;
    if (parent == x)
        return x;
    else{
        parent = findSet(parent);
        return parent;
    }

}

void DisjointSet::unionSets(Vertex x, Vertex y){
    Vertex px = findSet(x);
    Vertex py = findSet(y);
    subsets[px].parent = py;
    
}

Graph Graph::sort_edges() const{
    Graph sortedGraph;
    for (const Edge & edge : *this){
        sortedGraph.push_back(edge);
    }
    std::sort(sortedGraph.begin(), sortedGraph.end(), [](const Edge& a, const Edge& b){
        return a.weight < b.weight;
    });
    return sortedGraph;
}

VertexList Graph::edges_from(Vertex vertex) const{
    VertexList result;
    for( const Edge & edge: *this){
        if (edge.u == vertex)
            result.push_back(edge.v);    
    }
    return result;
}

EdgeList Kruskals(const Graph& G){
    const Graph& sorted_edges = G.sort_edges();
    size_t sized = G.numVertices-1;
    DisjointSet ds(G.numVertices);
    EdgeList result;
    for (Edge e : sorted_edges){
        if (ds.findSet(e.u) != ds.findSet(e.v)){
            ds.unionSets(e.u, e.v);
            result.push_back(e);
            if (result.size() >= sized) 
                break;
        }
    }
    return result;
}

int sum_weights(EdgeList const& L){
    int total = 0;
    for (const auto edge: L)
        total += edge.weight;
    return total;
}

void file_to_graph(string filename, Graph & G){
    ifstream in(filename);
    in >> G;
}

VertexList dfs(const Graph& graph, Vertex startVertex){
    //int numVert = graph.numVertices;
    VertexList traversed;
    vector<bool> visited(graph.size(), false);
    stack<Vertex> stk;
    visited[startVertex] = true;
    stk.push(startVertex);
    while (!stk.empty()){
        Vertex currentV = stk.top();
        stk.pop();
        traversed.push_back(currentV);
        for(Vertex v : graph.edges_from(currentV)){
            if (!visited[v]){
                visited[v] = true;
                stk.push(v);
            }
        }
    }
    return traversed;
}

VertexList bfs(const Graph& graph, Vertex startVertex){
    VertexList traversed;
    vector<bool> visited(graph.size(), false);
    queue<Vertex> vertexQueue;
    visited[startVertex] = true;
    vertexQueue.push(startVertex);
    while (!vertexQueue.empty()){
        Vertex currentVert = vertexQueue.front();
        vertexQueue.pop();
        traversed.push_back(currentVert);
        for(Vertex v: graph.edges_from(currentVert)){

            if (!visited[v]){
                visited[v] = true;
                vertexQueue.push(v);
            }
        }
        
    }
    return traversed;
}

string get_arg(int argc, char *argv[], string def){
    if (argc == 2)
        return string(argv[1]);
    else
        return def;
}

