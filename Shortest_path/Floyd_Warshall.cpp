#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Definindo um valor infinito para representar a ausência de aresta
const int INF = numeric_limits<int>::max();

// Função para imprimir a matriz de distâncias
void printMatrix(const vector<vector<int>>& dist, int V) {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

// Função que implementa o algoritmo de Floyd-Warshall
void floydWarshall(vector<vector<int>>& graph, int V) {
    // Matriz de distâncias
    vector<vector<int>> dist = graph;

    // Iterando sobre todos os pares de vértices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // Verificando se existe um caminho mais curto passando pelo vértice k
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Imprimindo a matriz de distâncias finais
    printMatrix(dist, V);
}

int main() {
    // Número de vértices
    int V = 4;

    // Matriz de adjacência do grafo
    vector<vector<int>> graph = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };

    // Executando o algoritmo de Floyd-Warshall
    floydWarshall(graph, V);

    return 0;
}