#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAX_NODES = 100;

vector<vector<int>> capacity(MAX_NODES, vector<int>(MAX_NODES, 0));
vector<vector<int>> flow(MAX_NODES, vector<int>(MAX_NODES, 0));
vector<int> parent(MAX_NODES);

bool bfs(int source, int sink, int num_nodes) {
    vector<bool> visited(num_nodes, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < num_nodes; ++neighbor) {
            if (!visited[neighbor] && capacity[current][neighbor] - flow[current][neighbor] > 0) {
                q.push(neighbor);
                parent[neighbor] = current;
                visited[neighbor] = true;
                if (neighbor == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}

int edmonds_karp(int source, int sink, int num_nodes) {
    int max_flow = 0;

    while (bfs(source, sink, num_nodes)) {
        int path_flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow;
            flow[v][u] -= path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int num_nodes = 6; // Número de nós no grafo

    // Inicializar a matriz de capacidades (exemplo do grafo)
    capacity[0][1] = 10;
    capacity[0][2] = 10;
    capacity[1][2] = 2;
    capacity[1][3] = 4;
    capacity[1][4] = 8;
    capacity[2][4] = 9;
    capacity[3][5] = 10;
    capacity[4][3] = 6;
    capacity[4][5] = 10;

    int source = 0, sink = 5;
    cout << "O fluxo máximo de " << source << " para " << sink << " é " << edmonds_karp(source, sink, num_nodes) << "." << endl;

    return 0;
}
