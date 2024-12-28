#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

// Número de vértices no grafo
#define V 6

// Função para realizar uma busca em largura (BFS) e encontrar um caminho aumentante
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    // Cria um array de visitados e marca todos os vértices como não visitados
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Cria uma fila, enfileira o nó de origem e marca-o como visitado
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Loop de BFS
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // Se encontramos um caminho para o vértice destino, retorna verdadeiro
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // Se não encontramos um caminho para o vértice destino, retorna falso
    return false;
}

// Função para retornar o fluxo máximo do grafo usando o algoritmo de Ford-Fulkerson
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    // Cria um grafo residual e inicializa o grafo residual com as capacidades do grafo original
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];  // Array para armazenar o caminho aumentante

    int max_flow = 0;  // Não há fluxo inicialmente

    // Aumenta o fluxo enquanto houver um caminho aumentante do vértice origem ao vértice destino
    while (bfs(rGraph, s, t, parent)) {
        // Encontra a capacidade residual mínima ao longo do caminho aumentante encontrado pela BFS
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Atualiza as capacidades residuais dos arcos e arcos reversos ao longo do caminho
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Adiciona o fluxo do caminho ao fluxo total
        max_flow += path_flow;
    }

    // Retorna o fluxo máximo
    return max_flow;
}

int main() {
    // Grafo de exemplo
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    // Calcula o fluxo máximo do vértice 0 ao vértice 5
    cout << "O fluxo máximo é " << fordFulkerson(graph, 0, 5) << endl;

    return 0;
}