#include <iostream>
#include <vector>
#include <iomanip> // Para formatação da saída
#include <limits>  // Para std::numeric_limits

using namespace std;

// Definindo um valor infinito para representar a ausência de aresta
const int INF = std::numeric_limits<int>::max(); // Correção: uso de std::numeric_limits

// Função para imprimir a matriz de distâncias
void printMatrix(const vector<vector<int>>& dist, int V) {
    cout << "Matriz de distâncias mínimas (Floyd-Warshall):" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << setw(4) << "INF"; // Formatação para alinhamento
            else
                cout << setw(4) << dist[i][j];
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
    int V = 19;

    // Matriz de adjacência do grafo
    vector<vector<int>> matriz = {
        {0, INF, INF, INF, INF, 3, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, 0, INF, INF, INF, INF, INF, 8, INF, INF, INF, 1, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, 0, 2, INF, INF, 1, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, 0, INF, INF, INF, INF, 9, 7, INF, INF, 15, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, 4, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, 2, 9, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {2, INF, 8, INF, INF, 7, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, 0, 7, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, 2, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, 5, INF, INF, INF, INF, 0, INF, INF, INF, 6, 9, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, 2, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 0, INF, INF, INF, INF, 1, INF, INF},
        {INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, 4, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, 18},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, INF, INF, INF, 0, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, 0, 2, 5},
        {INF, INF, INF, INF, INF, INF, INF, INF, 2, INF, INF, INF, INF, INF, INF, INF, 20, 0, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0}
    };

    // Executando o algoritmo de Floyd-Warshall
    floydWarshall(matriz, V);

    return 0;
}
