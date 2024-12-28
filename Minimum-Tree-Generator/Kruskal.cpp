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
            cout << aresta.origem + 1 << " -- " << aresta.destino + 1 << " [Peso: " << aresta.peso << "]\n";
        }
        cout << "Peso total da AGM: " << pesoTotal << endl;
    }
};

int main() {
    // Número de vértices
    int V = 12;
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

    // Executar o algoritmo de Kruskal
    g.kruskalAGM();

    return 0;
}