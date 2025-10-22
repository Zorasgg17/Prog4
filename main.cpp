#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int V, const vector<vector<pair<int, int>>>& adj, int src) {
    vector<int> dist(V, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distanc " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            cout << "To " << i << ": Unreachable\n";
        } else {
            cout << "To " << i << ": " << dist[i] << "\n";
        }
    }
}

int main() {
    int V, E;
    cout << "cin num of vertices  i edges: ";
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    cout << "cin edges (u v weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
    }

    int src;
    cout << "cin vertex: ";
    cin >> src;

    dijkstra(V, adj, src);

    return 0;
}