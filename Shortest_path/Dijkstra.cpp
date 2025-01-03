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
    const int n = 19; // Número de vértices no grafo

    // Representação do grafo como lista de adjacência
    vector<vector<pair<int, int>>> graph(n);

    // Matriz de adjacência representando o grafo (baseado na matriz fornecida)
    vector<vector<int>> matriz = {
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 9, 7, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 10, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 2, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 15, 0, 0, 0, 0, 0, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 1, 0, 0, 0, 0, 18},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 20},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 20, 0}
    };

    // Constrói o grafo com base na matriz
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] != 0) {
                graph[i].push_back({j, matriz[i][j]});
            }
        }
    }

    int src = 0; // Vértice de origem (indexado como 0)

    vector<int> dist;
    dijkstra(src, graph, dist);

    cout << "Distâncias mínimas a partir do vértice de origem " << src + 1 << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << "Vértice " << i + 1 << ": INF\n";
        } else {
            cout << "Vértice " << i + 1 << ": " << dist[i] << "\n";
        }
    }

    return 0;
}
