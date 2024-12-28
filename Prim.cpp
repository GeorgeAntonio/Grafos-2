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
                cout << pai[i] << " -- " << i << " [Peso: " << chave[i] << "]\n";
                pesoTotal += chave[i];
            }
        }
        cout << "Peso total da AGM: " << pesoTotal << endl;
    }
};

int main() {
    // Exemplo de uso
    int V = 12; // Número de vértices
    Grafo g(V);

    // Adicionar arestas ao grafo (baseado nos dados fornecidos)
    g.adicionarAresta(0, 1, 33);
    g.adicionarAresta(0, 2, 27);
    g.adicionarAresta(0, 3, 34);
    g.adicionarAresta(1, 2, 28);
    g.adicionarAresta(1, 3, 35);
    g.adicionarAresta(2, 3, 11);
    g.adicionarAresta(2, 4, 69);
    g.adicionarAresta(3, 4, 71);
    // Adicionar outras arestas conforme necessário...

    // Executar o algoritmo de Prim
    g.primAGM();

    return 0;
}
