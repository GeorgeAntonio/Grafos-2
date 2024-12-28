#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Estrutura para representar uma aresta com peso
struct Aresta {
    int destino, peso;

    Aresta(int d, int p) : destino(d), peso(p) {}
};

// Classe para representar um grafo usando listas de adjacências
class Grafo {
    int V; // Número de vértices
    vector<vector<Aresta>> adj; // Lista de adjacências

public:
    // Construtor
    Grafo(int V) : V(V), adj(V) {}

    // Adicionar aresta ao grafo
    void adicionarAresta(int origem, int destino, int peso) {
        adj[origem].emplace_back(destino, peso);
        adj[destino].emplace_back(origem, peso); // Grafo não direcionado
    }

    // Algoritmo de Prim para encontrar a Árvore Geradora Mínima (AGM)
    void primAGM() {
        vector<bool> incluidoNaAGM(V, false); // Marca os vértices incluídos na AGM
        vector<int> chave(V, numeric_limits<int>::max()); // Menor peso da aresta conectando cada vértice
        vector<int> pai(V, -1); // Armazena a árvore

        // Fila de prioridade (peso, vértice)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        // Começar pelo vértice 0
        chave[0] = 0;
        pq.emplace(0, 0);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Ignorar se já foi incluído na AGM
            if (incluidoNaAGM[u])
                continue;

            incluidoNaAGM[u] = true;

            // Explorar os vizinhos do vértice u
            for (const auto &aresta : adj[u]) {
                int v = aresta.destino;
                int peso = aresta.peso;

                if (!incluidoNaAGM[v] && peso < chave[v]) {
                    chave[v] = peso;
                    pai[v] = u;
                    pq.emplace(chave[v], v);
                }
            }
        }

        // Exibir a AGM e o peso total
        int pesoTotal = 0;
        cout << "Arestas na Árvore Geradora Mínima:\n";
        for (int i = 1; i < V; ++i) {
            if (pai[i] != -1) {
                cout << pai[i] + 1 << " -- " << i + 1 << " [Peso: " << chave[i] << "]\n";
                pesoTotal += chave[i];
            }
        }
        cout << "Peso total da AGM: " << pesoTotal << endl;
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
            if (matriz[i][j] != 0) {
                g.adicionarAresta(i, j, matriz[i][j]);
            }
        }
    }

    // Executar o algoritmo de Prim
    g.primAGM();

    return 0;
}
