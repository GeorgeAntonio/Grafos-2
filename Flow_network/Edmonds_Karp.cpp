#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAX_NODES = 100; // Número máximo de nós no grafo

// Matriz de capacidade entre nós
vector<vector<int>> capacity(MAX_NODES, vector<int>(MAX_NODES, 0));

// Matriz de fluxo atual entre nós
vector<vector<int>> flow(MAX_NODES, vector<int>(MAX_NODES, 0));

// Vetor para armazenar os pais dos nós no caminho aumentante encontrado
vector<int> parent(MAX_NODES);

// Função para realizar a busca em largura (BFS) para encontrar um caminho aumentante
bool bfs(int source, int sink, int num_nodes) {
    vector<bool> visited(num_nodes, false); // Vetor para verificar quais nós foram visitados
    queue<int> q; // Fila para realizar a BFS
    q.push(source); // Começa a BFS a partir do nó de origem
    visited[source] = true; // Marca o nó de origem como visitado
    parent[source] = -1; // O nó de origem não tem pai

    // Loop para explorar todos os nós conectados
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Verifica os vizinhos do nó atual
        for (int neighbor = 0; neighbor < num_nodes; ++neighbor) {
            // Se o nó vizinho não foi visitado e tem capacidade residual > 0
            if (!visited[neighbor] && capacity[current][neighbor] - flow[current][neighbor] > 0) {
                q.push(neighbor); // Enfileira o nó vizinho
                parent[neighbor] = current; // Define o nó atual como pai
                visited[neighbor] = true; // Marca o vizinho como visitado

                // Se o destino for encontrado, retorna verdadeiro
                if (neighbor == sink) {
                    return true;
                }
            }
        }
    }
    return false; // Retorna falso se não houver caminho do source para o sink
}

// Função para calcular o fluxo máximo usando o algoritmo de Edmonds-Karp
int edmonds_karp(int source, int sink, int num_nodes) {
    int max_flow = 0; // Inicializa o fluxo máximo como 0

    // Enquanto houver um caminho aumentante
    while (bfs(source, sink, num_nodes)) {
        int path_flow = INT_MAX; // Capacidade mínima ao longo do caminho aumentante

        // Encontra a capacidade residual mínima ao longo do caminho
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
        }

        // Atualiza as capacidades residuais e o fluxo ao longo do caminho
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow; // Aumenta o fluxo na direção direta
            flow[v][u] -= path_flow; // Diminui o fluxo na direção reversa
        }

        // Adiciona o fluxo do caminho ao fluxo máximo
        max_flow += path_flow;
    }

    return max_flow; // Retorna o fluxo máximo encontrado
}

int main() {
    int num_nodes = 6; // Número de nós no grafo

    // Inicializar a matriz de capacidades (exemplo do grafo)
    capacity[0][1] = 10; // Capacidade de 0 para 1
    capacity[0][2] = 10; // Capacidade de 0 para 2
    capacity[1][2] = 2;  // Capacidade de 1 para 2
    capacity[1][3] = 4;  // Capacidade de 1 para 3
    capacity[1][4] = 8;  // Capacidade de 1 para 4
    capacity[2][4] = 9;  // Capacidade de 2 para 4
    capacity[3][5] = 10; // Capacidade de 3 para 5
    capacity[4][3] = 6;  // Capacidade de 4 para 3
    capacity[4][5] = 10; // Capacidade de 4 para 5

    int source = 0; // Nó de origem
    int sink = 5;   // Nó de destino

    // Calcula e exibe o fluxo máximo
    cout << "O fluxo máximo de " << source << " para " << sink << " é " << edmonds_karp(source, sink, num_nodes) << "." << endl;

    return 0;
}
