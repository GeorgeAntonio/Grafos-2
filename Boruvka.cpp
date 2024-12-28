#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino, peso;

    Aresta(int o, int d, int p) : origem(o), destino(d), peso(p) {}
};

// Classe para representar um grafo
class Grafo {
    int V; // Número de vértices
    vector<Aresta> arestas; // Lista de arestas

public:
    // Construtor
    Grafo(int V) : V(V) {}

    // Adicionar aresta ao grafo
    void adicionarAresta(int origem, int destino, int peso) {
        arestas.push_back(Aresta(origem, destino, peso));
    }

    // Algoritmo de Boruvka para encontrar a Árvore Geradora Mínima (AGM)
    void boruvkaAGM() {
        vector<int> componente(V); // Componentes conectadas
        vector<int> pesoMinimo(V, numeric_limits<int>::max());
        vector<int> menorAresta(V, -1);
        
        // Inicializar os componentes
        for (int i = 0; i < V; i++)
            componente[i] = i;

        int numComponentes = V;
        int pesoTotal = 0;

        cout << "Arestas na Árvore Geradora Mínima:\n";

        // Enquanto houver mais de uma componente
        while (numComponentes > 1) {
            // Resetar as menores arestas
            fill(pesoMinimo.begin(), pesoMinimo.end(), numeric_limits<int>::max());
            fill(menorAresta.begin(), menorAresta.end(), -1);

            // Encontrar a menor aresta para cada componente
            for (int i = 0; i < arestas.size(); i++) {
                int u = arestas[i].origem;
                int v = arestas[i].destino;
                int peso = arestas[i].peso;

                int compU = componente[u];
                int compV = componente[v];

                if (compU != compV) {
                    if (peso < pesoMinimo[compU]) {
                        pesoMinimo[compU] = peso;
                        menorAresta[compU] = i;
                    }
                    if (peso < pesoMinimo[compV]) {
                        pesoMinimo[compV] = peso;
                        menorAresta[compV] = i;
                    }
                }
            }

            // Adicionar as menores arestas às componentes
            for (int i = 0; i < V; i++) {
                if (menorAresta[i] != -1) {
                    int u = arestas[menorAresta[i]].origem;
                    int v = arestas[menorAresta[i]].destino;
                    int peso = arestas[menorAresta[i]].peso;

                    int compU = componente[u];
                    int compV = componente[v];

                    if (compU != compV) {
                        cout << u << " -- " << v << " [Peso: " << peso << "]\n";
                        pesoTotal += peso;

                        // Unir os componentes
                        for (int j = 0; j < V; j++) {
                            if (componente[j] == compV)
                                componente[j] = compU;
                        }
                        numComponentes--;
                    }
                }
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

    // Executar o algoritmo de Boruvka
    g.boruvkaAGM();

    return 0;
}
