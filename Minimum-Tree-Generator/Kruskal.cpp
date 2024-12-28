#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino, peso;

    // Construtor
    Aresta(int o, int d, int p) : origem(o), destino(d), peso(p) {}
};

// Comparador para ordenar as arestas pelo peso
bool compararPesos(const Aresta &a, const Aresta &b) {
    return a.peso < b.peso;
}

// Classe para representar um grafo com o algoritmo de Kruskal
class Grafo {
    int V; // Número de vértices
    vector<Aresta> arestas; // Lista de arestas

    // Função auxiliar para encontrar o representante do conjunto (Union-Find)
    int encontrarRepresentante(vector<int> &pai, int v) {
        if (pai[v] != v)
            pai[v] = encontrarRepresentante(pai, pai[v]); // Caminho comprimido
        return pai[v];
    }

    // Função auxiliar para unir dois subconjuntos (Union-Find)
    void unirConjuntos(vector<int> &pai, vector<int> &rank, int u, int v) {
        int raizU = encontrarRepresentante(pai, u);
        int raizV = encontrarRepresentante(pai, v);

        if (rank[raizU] < rank[raizV]) {
            pai[raizU] = raizV;
        } else if (rank[raizU] > rank[raizV]) {
            pai[raizV] = raizU;
        } else {
            pai[raizV] = raizU;
            rank[raizU]++;
        }
    }

public:
    // Construtor
    Grafo(int V) : V(V) {}

    // Adicionar aresta ao grafo
    void adicionarAresta(int origem, int destino, int peso) {
        arestas.push_back(Aresta(origem, destino, peso));
    }

    // Algoritmo de Kruskal para encontrar a Árvore Geradora Mínima (AGM)
    void kruskalAGM() {
        // Ordenar as arestas pelo peso
        sort(arestas.begin(), arestas.end(), compararPesos);

        vector<int> pai(V);
        vector<int> rank(V, 0);

        // Inicializar cada vértice como seu próprio pai
        for (int i = 0; i < V; i++)
            pai[i] = i;

        vector<Aresta> agm; // Lista de arestas da Árvore Geradora Mínima
        int pesoTotal = 0;

        // Processar as arestas ordenadas
        for (const auto &aresta : arestas) {
            int raizU = encontrarRepresentante(pai, aresta.origem);
            int raizV = encontrarRepresentante(pai, aresta.destino);

            // Incluir a aresta se não formar ciclo
            if (raizU != raizV) {
                agm.push_back(aresta);
                pesoTotal += aresta.peso;
                unirConjuntos(pai, rank, raizU, raizV);
            }
        }

        // Exibir a AGM e o peso total
        cout << "Arestas na Árvore Geradora Mínima:\n";
        for (const auto &aresta : agm) {
            cout << aresta.origem << " -- " << aresta.destino << " [Peso: " << aresta.peso << "]\n";
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

    // Executar o algoritmo de Kruskal
    g.kruskalAGM();

    return 0;
}
