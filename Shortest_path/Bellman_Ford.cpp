#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino, peso;
};

// Função para imprimir a solução
void imprimirSolucao(vector<int>& dist, int V) {
    cout << "Distância do vértice origem para cada vértice:" << endl;
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << i + 1 << "\t\tINF" << endl;
        } else {
            cout << i + 1 << "\t\t" << dist[i] << endl;
        }
    }
}

// Função que implementa o algoritmo de Bellman-Ford
void bellmanFord(vector<Aresta>& arestas, int V, int E, int origem) {
    // Inicializa a distância de todos os vértices como infinito
    vector<int> dist(V, INT_MAX);
    dist[origem] = 0;

    // Relaxa todas as arestas V-1 vezes
    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = arestas[j].origem;
            int v = arestas[j].destino;
            int peso = arestas[j].peso;
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    // Verifica se há ciclos de peso negativo
    for (int i = 0; i < E; ++i) {
        int u = arestas[i].origem;
        int v = arestas[i].destino;
        int peso = arestas[i].peso;
        if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
            cout << "Grafo contém ciclo de peso negativo" << endl;
            return;
        }
    }

    // Imprime a solução
    imprimirSolucao(dist, V);
}

int main() {
    int V = 19; // Número de vértices no grafo
    vector<Aresta> arestas;

    // Adiciona as arestas baseadas na matriz fornecida
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

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matriz[i][j] > 0) { // Se houver peso na aresta
                arestas.push_back({i, j, matriz[i][j]});
            }
        }
    }

    int origem = 0; // Vértice de origem (indexado como 0)

    // Chama a função Bellman-Ford
    bellmanFord(arestas, V, arestas.size(), origem);

    return 0;
}
