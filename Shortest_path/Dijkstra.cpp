#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int src, const vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Digite o número de vértices e arestas: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    cout << "Digite as arestas (u v w), onde u e v são vértices e w é o peso:\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Se o grafo for direcionado, remova esta linha
    }

    int src;
    cout << "Digite o vértice de origem: ";
    cin >> src;

    vector<int> dist;
    dijkstra(src, graph, dist);

    cout << "Distâncias mínimas a partir do vértice de origem " << src << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << "Vértice " << i << ": INF\n";
        } else {
            cout << "Vértice " << i << ": " << dist[i] << "\n";
        }
    }

    return 0;
}
