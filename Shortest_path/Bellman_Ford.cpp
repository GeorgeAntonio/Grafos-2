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
        {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 15, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 8, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 18},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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
