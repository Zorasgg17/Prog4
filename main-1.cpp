//push-relabel
#include <bits/stdc++.h> 
using namespace std; 
  
struct Edge // e E
{ 
    // neka e umat cap
    int flow, capacity; 
  
    // za e neka u e start a v e end
    int u, v; 
  
    Edge(int flow, int capacity, int u, int v) 
    { 
        this->flow = flow; 
        this->capacity = capacity; 
        this->u = u; 
        this->v = v; 
    } 
}; 
  

struct Vertex //v E
{ 
    int h, e_flow; 
  
    Vertex(int h, int e_flow) 
    { 
        this->h = h; 
        this->e_flow = e_flow; 
    } 
}; 
  
//neka flow network E
class Graph 
{ 
    int V;    //broj na v
    vector<Vertex> ver; 
    vector<Edge> edge; 
  
    // Func za push extra flow od u 
    bool push(int u); 
  
    // relabel a vertex u 
    void relabel(int u); 
  
    
    //func za preflow E
    void preflow(int s); 
  
    // Func za reverse na e
    void updateReverseEdgeFlow(int i, int flow); 
  
public: 
    Graph(int V);  // neka A E
  
    // func za +1 e vo graph 
    void addEdge(int u, int v, int w); 
  
    // return max flow od s do t 
    int getMaxFlow(int s, int t); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
  
   // A v se so 0 height i 0 extra flow 
    for (int i = 0; i < V; i++) 
        ver.push_back(Vertex(0, 0)); 
} 
  
void Graph::addEdge(int u, int v, int capacity) 
{ 
    //neka flow so 0 za A e
    edge.push_back(Edge(0, capacity, u, v)); 
} 
  
void Graph::preflow(int s) 
{ 
    //neka h od sourceV = br. od v
    // h od A dr v = 0 
    ver[s].h = ver.size(); 
  
    //neka for loop
    for (int i = 0; i < edge.size(); i++) 
    { 
        //?current e goes from source ?
        if (edge[i].u == s) 
        { 
            // Flow = cap (yay)
            edge[i].flow = edge[i].capacity; 
  
            // initialize extra flow for neighbouring v 
            ver[edge[i].v].e_flow += edge[i].flow; 
  
   // +1 edge od v do s in residual graph with cap = 0 
            edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s)); 
        } 
    } 
} 
  
// return index od overflowing v 
int overFlowVertex(vector<Vertex>& ver) 
{ 
    //?vazi?
    for (int i = 1; i < ver.size() - 1; i++) 
       if (ver[i].e_flow > 0) 
            return i; //ako ok
  
    //return -1 if no overflowing v 
    return -1; 
} 
  
//Update reverse flow za +1 flow na ith e
void Graph::updateReverseEdgeFlow(int i, int flow) 
{ 
    int u = edge[i].v, v = edge[i].u; 
  
    for (int j = 0; j < edge.size(); j++) 
    { 
        if (edge[j].v == v && edge[j].u == u) 
        { 
            edge[j].flow -= flow; 
            return; 
        } 
    } 
  
    //neka +1 reverse e in residual graph 
    Edge e = Edge(0, flow, u, v); 
    edge.push_back(e); 
} 
  
//push flow od overflowing v (v ē u)
bool Graph::push(int u) 
{ 
    //baraj niz A e za adjacent (of u) kade flow moze push
    for (int i = 0; i < edge.size(); i++) 
    { 
        //?promena vo u od e?
        // overflowing v
        if (edge[i].u == u) 
        { 
            // if flow is equal to capacity then no push 
            // is possible 
            if (edge[i].flow == edge[i].capacity) 
                continue; 
  
            // Push is only possible if height of adjacent 
            // is smaller than height of overflowing vertex 
            if (ver[u].h > ver[edge[i].v].h) 
            { 
                // Flow to be pushed is equal to minimum of 
                // remaining flow on edge and excess flow. 
                int flow = min(edge[i].capacity - edge[i].flow, 
                               ver[u].e_flow); 
  
                // Reduce excess flow for overflowing vertex 
                ver[u].e_flow -= flow; 
  
                // Increase excess flow for adjacent 
                ver[edge[i].v].e_flow += flow; 
  
                // Add residual flow (With capacity 0 and negative 
                // flow) 
                edge[i].flow += flow; 
  
                updateReverseEdgeFlow(i, flow); 
  
                return true; 
            } 
        } 
    } 
    return false; 
} 
  
// function to relabel vertex u 
void Graph::relabel(int u) 
{ 
    // Initialize minimum height of an adjacent 
    int mh = INT_MAX; 
  
    // Find the adjacent with minimum height 
    for (int i = 0; i < edge.size(); i++) 
    { 
        if (edge[i].u == u) 
        { 
            // if flow is equal to capacity then no 
            // relabeling 
            if (edge[i].flow == edge[i].capacity) 
                continue; 
  
            // Update minimum height 
            if (ver[edge[i].v].h < mh) 
            { 
                mh = ver[edge[i].v].h; 
  
                // updating height of u 
                ver[u].h = mh + 1; 
            } 
        } 
    } 
} 
  
// main function for printing maximum flow of graph 
int Graph::getMaxFlow(int s, int t) 
{ 
    preflow(s); 
  
    // loop until none of the Vertex is in overflow 
    while (overFlowVertex(ver) != -1) 
    { 
        int u = overFlowVertex(ver); 
        if (!push(u)) 
            relabel(u); 
    } 
  
    // ver.back() returns last Vertex, whose 
    // e_flow will be final maximum flow 
    return ver.back().e_flow; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int V = 6; 
    Graph g(V); 
  
    // Creating above shown flow network 
    g.addEdge(0, 1, 16); 
    g.addEdge(0, 2, 13); 
    g.addEdge(1, 2, 10); 
    g.addEdge(2, 1, 4); 
    g.addEdge(1, 3, 12); 
    g.addEdge(2, 4, 14); 
    g.addEdge(3, 2, 9); 
    g.addEdge(3, 5, 20); 
    g.addEdge(4, 3, 7); 
    g.addEdge(4, 5, 4); 
  
    // Initialize source and sink 
    int s = 0, t = 5; 
  
    cout << "Maximum flow is " << g.getMaxFlow(s, t); 
    return 0; 
}