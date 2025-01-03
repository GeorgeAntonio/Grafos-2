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
           1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
        01{00, 00, 00, 00, 00, 03, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00},
        02{00, 00, 00, 00, 00, 00, 00, 08, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00},
        03{00, 00, 00, 02, 00, 00, 01, 10, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
        04{00, 00, 00, 00, 00, 00, 00, 00, 09, 07, 00, 00, 15, 00, 00, 00, 00, 00, 00},
        05{00, 00, 00, 04, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
        06{00, 02, 09, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
        07{02, 00, 08, 00, 00, 07, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
        08{00, 00, 00, 00, 00, 00, 00, 00, 07, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
        09{00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00},
        10{00, 00, 00, 00, 05, 00, 00, 00, 00, 00, 00, 00, 00, 06, 09, 00, 00, 00, 00},
        11{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00},
        12{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 04, 00, 00, 00, 00, 00, 01, 00, 00},
        13{00, 05, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 04, 00},
        14{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 18},
        15{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
        16{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 03, 00, 00, 00, 00, 00, 00, 00},
        17{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 05},
        18{00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 20, 00, 00},
        19{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00}
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
