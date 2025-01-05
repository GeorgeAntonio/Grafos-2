#include <iostream>
#include <vector>
#include <queue> // Incluído para usar priority_queue
#include <limits> // Incluído para usar numeric_limits

using namespace std;

const int INF = numeric_limits<int>::max();

// Função que implementa o algoritmo de Dijkstra
void dijkstra(int src, const vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[src] = 0;

    // Fila de prioridade para processar os vértices
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

    // Matriz de adjacência representando o grafo
    vector<vector<int>> matriz = {
        {INF, INF, INF, INF, INF, 3, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, 8, INF, INF, INF, 1, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, 2, INF, INF, 1, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, 9, 7, INF, INF, 15, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, 2, 9, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {2, INF, 8, INF, INF, 7, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, 7, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, 6, 9, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, INF, INF, 1, INF, INF},
        {INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, 18},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF, 2, 5},
        {INF, INF, INF, INF, INF, INF, INF, INF, 2, INF, INF, INF, INF, INF, INF, INF, 20, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}
    };

    // Constrói o grafo com base na matriz
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] != INF) {
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
