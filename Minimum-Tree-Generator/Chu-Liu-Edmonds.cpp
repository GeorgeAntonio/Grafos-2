#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino;
    double peso;

    Aresta(int o, int d, double p) : origem(o), destino(d), peso(p) {}
};

class GrafoDirecionado {
    int V; // Número de vértices
    vector<Aresta> arestas; // Lista de arestas

public:
    GrafoDirecionado(int V) : V(V) {}

    void adicionarAresta(int origem, int destino, double peso) {
        arestas.emplace_back(origem, destino, peso);
    }

    vector<Aresta> chuLiuEdmonds(int raiz) {
        vector<int> pai(V, -1);
        vector<double> menorCusto(V, numeric_limits<double>::infinity());
        vector<Aresta> arborescencia;

        for (const auto& aresta : arestas) {
            if (aresta.destino != raiz && aresta.peso < menorCusto[aresta.destino]) {
                menorCusto[aresta.destino] = aresta.peso;
                pai[aresta.destino] = aresta.origem;
            }
        }

        // Verificar ciclos
        vector<int> componente(V, -1);
        vector<bool> visitado(V, false);
        int numComponentes = 0;

        for (int v = 0; v < V; ++v) {
            if (v == raiz || componente[v] != -1) continue;

            int atual = v;
            while (atual != -1 && componente[atual] == -1 && !visitado[atual]) {
                visitado[atual] = true;
                atual = pai[atual];
            }

            if (atual != -1 && componente[atual] == -1) {
                int cicloInicio = atual;
                do {
                    componente[atual] = numComponentes;
                    atual = pai[atual];
                } while (atual != cicloInicio);

                numComponentes++;
            }

            atual = v;
            while (atual != -1 && componente[atual] == -1) {
                componente[atual] = numComponentes;
                atual = pai[atual];
            }
        }

        if (numComponentes == 0) {
            for (int v = 0; v < V; ++v) {
                if (pai[v] != -1)
                    arborescencia.emplace_back(pai[v], v, menorCusto[v]);
            }
            return arborescencia;
        }

        // Contração do ciclo
        vector<Aresta> novasArestas;
        unordered_map<int, double> ajustePeso;

        for (const auto& aresta : arestas) {
            int u = componente[aresta.origem];
            int v = componente[aresta.destino];
            if (u != v) {
                double novoPeso = aresta.peso - (aresta.destino == raiz ? 0 : menorCusto[aresta.destino]);
                novasArestas.emplace_back(u, v, novoPeso);
            }
        }

        GrafoDirecionado grafoContraido(numComponentes);
        for (const auto& aresta : novasArestas) {
            grafoContraido.adicionarAresta(aresta.origem, aresta.destino, aresta.peso);
        }

        auto contraidoArborescencia = grafoContraido.chuLiuEdmonds(raiz);
        for (const auto& aresta : contraidoArborescencia) {
            arborescencia.emplace_back(arestas[aresta.origem].origem, arestas[aresta.destino].destino, aresta.peso);
        }

        return arborescencia;
    }
};

int main() {
    int V = 6; // Número de vértices
    GrafoDirecionado g(V);

    // Exemplo baseado nos dados fornecidos
    g.adicionarAresta(0, 1, 5);
    g.adicionarAresta(0, 2, 3);
    g.adicionarAresta(1, 2, 2);
    g.adicionarAresta(2, 3, 8);
    g.adicionarAresta(3, 4, 7);
    g.adicionarAresta(4, 5, 6);
    g.adicionarAresta(5, 0, 4);

    int raiz = 0;
    auto resultado = g.chuLiuEdmonds(raiz);

    cout << "Arborescência de custo mínimo:\n";
    for (const auto& aresta : resultado) {
        cout << aresta.origem << " -> " << aresta.destino << " [Peso: " << aresta.peso << "]\n";
    }

    return 0;
}
