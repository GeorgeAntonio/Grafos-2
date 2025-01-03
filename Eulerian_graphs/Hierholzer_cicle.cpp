#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Grafo {
    int V; // Número de vértices
    unordered_map<int, vector<int>> adj; // Lista de adjacência

public:
    // Construtor
    Grafo(int V) : V(V) {}

    // Adicionar aresta ao grafo
    void adicionarAresta(int origem, int destino) {
        adj[origem].push_back(destino);
        adj[destino].push_back(origem); // Grafo não direcionado
    }

    // Remover uma aresta
    void removerAresta(int origem, int destino) {
        auto it = find(adj[origem].begin(), adj[origem].end(), destino);
        if (it != adj[origem].end()) adj[origem].erase(it);

        it = find(adj[destino].begin(), adj[destino].end(), origem);
        if (it != adj[destino].end()) adj[destino].erase(it);
    }

    // Verificar se o grafo é Euleriano
    bool verificarEuleriano() {
        int verticesImpares = 0;
        for (const auto &par : adj) {
            if (par.second.size() % 2 != 0) {
                verticesImpares++;
            }
        }
        return verticesImpares == 0;
    }

    // Algoritmo de Hierholzer para encontrar o ciclo Euleriano
    vector<int> encontrarCicloEuleriano(int inicio) {
        vector<int> ciclo;
        if (!verificarEuleriano()) {
            cout << "O grafo não é Euleriano!" << endl;
            return ciclo;
        }

        stack<int> pilha;
        pilha.push(inicio);

        while (!pilha.empty()) {
            int atual = pilha.top();

            if (!adj[atual].empty()) {
                int vizinho = adj[atual].back();
                pilha.push(vizinho);
                removerAresta(atual, vizinho);
            } else {
                ciclo.push_back(atual);
                pilha.pop();
            }
        }

        reverse(ciclo.begin(), ciclo.end());
        return ciclo;
    }
};

int main() {
    int V = 12; // Número de vértices
    Grafo g(V);

    // Dados fornecidos (matriz de adjacência)
    int matriz[12][12] = {
        {0, 33, 27, 34, 65, 93, 145, 23, 37, 23, 38, 38},
        {33, 0, 28, 35, 42, 94, 172, 50, 64, 51, 47, 65},
        {27, 28, 0, 11, 69, 71, 166, 44, 57, 44, 72, 59},
        {34, 35, 11, 0, 71, 66, 174, 52, 66, 53, 73, 67},
        {65, 42, 69, 71, 0, 192, 114, 83, 97, 70, 43, 94},
        {93, 94, 71, 66, 192, 0, 235, 112, 126, 113, 133, 127},
        {145, 172, 166, 174, 114, 235, 0, 137, 124, 133, 151, 109},
        {23, 50, 44, 52, 83, 112, 137, 0, 14, 38, 61, 38},
        {37, 64, 57, 66, 97, 126, 124, 14, 0, 36, 67, 24},
        {23, 51, 44, 53, 70, 113, 133, 38, 36, 0, 31, 25},
        {38, 47, 72, 73, 43, 133, 151, 61, 67, 31, 0, 56},
        {38, 65, 59, 67, 94, 127, 109, 38, 24, 25, 56, 0}
    };

    // Adicionar arestas ao grafo
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (matriz[i][j] > 0) {
                g.adicionarAresta(i, j);
            }
        }
    }

    // Encontrar o ciclo Euleriano
    int inicio = 0;
    vector<int> cicloEuleriano = g.encontrarCicloEuleriano(inicio);

    if (!cicloEuleriano.empty()) {
        cout << "Ciclo Euleriano encontrado:\n";
        for (int vertice : cicloEuleriano) {
            cout << vertice + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
