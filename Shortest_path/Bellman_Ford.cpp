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
    for (int i = 0; i < V; ++i)
        cout << i << "\t\t" << dist[i] << endl;
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
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v])
                dist[v] = dist[u] + peso;
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
    int V = 5; // Número de vértices no grafo
    int E = 8; // Número de arestas no grafo

    // Lista de arestas do grafo
    vector<Aresta> arestas = {
        {0, 1, -1}, {0, 2, 4},
        {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1},
        {4, 3, -3}
    };

    int origem = 0; // Vértice de origem

    // Chama a função Bellman-Ford
    bellmanFord(arestas, V, E, origem);

    return 0;
}