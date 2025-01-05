#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Definindo um valor muito grande para representar INF
#define INF INT_MAX

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino, peso;
};

// Função para imprimir a solução
void imprimirSolucao(const vector<int>& dist, int V) {
    cout << "Distância do vértice origem para cada vértice:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vértice " << i + 1 << ": ";
        if (dist[i] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
}

// Função que implementa o algoritmo de Bellman-Ford
void bellmanFord(const vector<Aresta>& arestas, int V, int E, int origem) {
    // Inicializa a distância de todos os vértices como infinito
    vector<int> dist(V, INF);
    dist[origem] = 0;

    // Relaxa todas as arestas V-1 vezes
    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& aresta : arestas) {
            int u = aresta.origem;
            int v = aresta.destino;
            int peso = aresta.peso;

            // Verifica se o caminho pelo vértice atual é menor
            if (dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    // Verifica se há ciclos de peso negativo
    for (const auto& aresta : arestas) {
        int u = aresta.origem;
        int v = aresta.destino;
        int peso = aresta.peso;

        if (dist[u] != INF && dist[u] + peso < dist[v]) {
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

    // Matriz de adjacência do grafo
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
        {INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, INF, INF, 1, INF, INF},
        {INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, 18},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF, 2, 5},
        {INF, INF, INF, INF, INF, INF, INF, INF, 2, INF, INF, INF, INF, INF, INF, INF, 20, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}
    };

    // Converte a matriz de adjacência em uma lista de arestas
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matriz[i][j] > 0 && matriz[i][j] != INF) {
                arestas.push_back({i, j, matriz[i][j]});
            }
        }
    }

    int origem = 0; // Vértice de origem (indexado como 0)

    // Chama a função Bellman-Ford
    bellmanFord(arestas, V, arestas.size(), origem);

    return 0;
}
