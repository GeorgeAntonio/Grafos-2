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
    int V = 19;

    // Matriz de adjacência do grafo
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

    // Executando o algoritmo de Floyd-Warshall
    floydWarshall(graph, V);

    return 0;
}
