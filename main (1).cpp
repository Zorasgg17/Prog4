//Floyd-Warshall
#include <iostream>
#include <limits.h>
#include <vector>
//neka ovie 3 mesto bits

#define INF INT_MAX  //neka beskoneco

using namespace std;

// Func za cout na mtx
void printSolution(const vector<vector<int>> &dist) //dist e distance
{
    int V = dist.size();
    cout << "shortest distances here:\n";
    
    for (int i = 0; i < V; ++i)//i i j se start i end v, kade k e megu (ili ne e megu) niv(c k podolu-->)
    {
        for (int j = 0; j < V; ++j)
        {
            if (dist[i][j] == INF)
                cout << "INF"
                     << "\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

//Floyd-Warshall here -->
void floydWarshall(vector<vector<int>> &graph)
{
    int V = graph.size();
    vector<vector<int>> dist = graph;

    // Update mtx spored v
    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j]; 
            }
        }
    }

    // cout mtx here -->
    printSolution(dist);
}

int main()
{
   //primer mtx, change permissible here -->
    vector<vector<int>> graph = {{0, 5, INF, 10}, {INF, 0, 3, INF}, {INF, INF, 0, 1}, {INF, INF, INF, 0}};

    //Use here ->>
    floydWarshall(graph);

    return 0;
}