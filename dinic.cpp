#include <iostream>                         // fluxo de dados
#include <cstring>                          // utilizacao do memset
#include <queue>                            // utilizacao da estrutura de dados fila
#include <climits>                          // utlizacao do max_int

#define maxn 10

using namespace std;


int g[maxn][maxn];                          // Grafo representado por matriz de adjacencia
int level[maxn];                            // vetor de niveis
int n;                                      // quantidade de vertices no grafo

/*
    Busca em largura
    Realizada no grafo para montar o grafo de niveis
*/
bool breadthFirstSearch(int s, int t) {

    memset(level, -1, sizeof level);        // inicia todos os niveis como -1
    queue<int> q;                           // cria uma fila para armazenar os vertices da busca em largura
    q.push(s);                              // enfileira o source
    level[s] = 0;                           // inicia o nivel de s como nivel 0

    // Aqui e feita a busca em largura no grafo
    while (!q.empty()) {                    
        int u = q.front();                  // pega o primeiro vertice na fila
        q.pop();                            // retira o vertice
        // percorre a adjacencia do vertice atual
        for (int v = 0; v < n; v++) {
            // se ainda nao foi visitado e existe adjacencia
            if (level[v] < 0 && g[u][v]) {
                level[v] = level[u] + 1;    // seta o nivel da adjacencia como o nivel do vertice atual + 1
                q.push(v);                  // enfileira a adjacencia
            }
        }
    }

    return level[t] < 0 ? false : true;     // se encontrou caminho para o target retorna true, do contrario retorna false

}

/*
    Busca em profundidade
    Realizada por meio do grafo de niveis, buscando um caminho de aumento
*/
int depthFirstSearch(int u, int t, int flow) {
    if (u == t) return flow;                        // se chegou no target retorna o fluxo que chegou ate ele

    // percorre a adjacencia do vertice atual
    for (int v = 0; v < n; v++) {
        // se o nivel da adjacencia for exatamente o nivel do vertice atual + 1 pode-se mandar o fluxo pra ele
        if (level[v] == level[u]+1 && g[u][v]) {
            int f = min(flow, g[u][v]);     // o fluxo que passa por esse caminho e o minimo entre o que passa por essa aresta e o fluxo que esta chegando
            int gargalo = depthFirstSearch(v, t, f);     // chama a busca para este novo vertice
            // se o gargalo foi maior que 0, foi possivel passar algum fluxo pelo caminho
            if (gargalo > 0) {              
                g[u][v] -= gargalo;         // subtrai o fluxo que foi passado da aresta atual
                g[v][u] += gargalo;         // aumenta o fluxo na aresta de residuos
                return gargalo;             // retorna o fluxo que foi passado por este caminho, afinal a dfs tenta achar um caminho por vez
            }
        }
    }

    return 0;
}

/*
    Fluxo Maximo
    Responsavel por calcular o fluxo maximo do source para o target
*/
int dinicFlow(int s, int t) {
    int flow = 0;                       // inicializa o fluxo maximo com 0
    
    // enquanto houver caminho para o target, realiza a busca em largura para montar o grafo de niveis
    while (breadthFirstSearch(s, t)) {
        // enquanto houverem caminhos de aumento no grafo de niveis, realiza a busca em profundidade
        while (int gargalo = depthFirstSearch(s, t, INT_MAX)) {
            flow += gargalo;
        }
    }

    return flow;
}

int main (int argc, char *argv[]) {

    // Modelagem

    return 0;
}
