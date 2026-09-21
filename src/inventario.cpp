// Arquivo para criar as funcionalidades do menu (funções do 1 ao 8)
#include "inventario.h"
#include <string>
#include <iostream>
#include <list>
#include <queue>
#include <set>

using namespace std;

Raridade classificarRaridade(int valor) {
    if(valor >= 100) {
        return Raridade::Mitico;
    }
    if(valor >= 85) {
        return Raridade::Lendario;
    }
    if(valor >= 60) {
        return Raridade::Epico;
    }
    if(valor >= 30) {
        return Raridade::Raro;
    }
    
    return Raridade::Comum;
}

// Funcao 1 - Inserir Item
// Criado usando apenas uma lista pois o grafo será implementado na EP3

void inserirItem(list<Item> &inventario_provisorio, Item novo_item) {
    inventario_provisorio.push_back(novo_item);
}

// Funcao 2 - Cadastrar similaridade (grafo ponderado com lista de adjacência)

bool existeItem(const Grafo &inventario, int id){
    return inventario.vertices.count(id) > 0;
}

// Insere o item como vértice do grafo
bool inserirVertice(Grafo &inventario, Item item){
    if(existeItem(inventario, item.id)){
        return false;
    }

    inventario.vertices[item.id] = item;
    inventario.adjacencia[item.id];
    return true;
}

static void adicionarAresta(Grafo &inventario, int origem, int destino, int similaridade){
    for(Aresta &aresta : inventario.adjacencia[origem]){
        if(aresta.destino == destino){
            aresta.similaridade = similaridade;
            return;
        }
    }

    inventario.adjacencia[origem].push_back({destino, similaridade});
}

// Grafo não direcionado: aresta nos dois sentidos
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade){
    if(id1 == id2 || !existeItem(inventario, id1) || !existeItem(inventario, id2)){
        return false;
    }

    adicionarAresta(inventario, id1, id2, similaridade);
    adicionarAresta(inventario, id2, id1, similaridade);
    return true;
}

// BFS seguindo o código da aula
static void buscaEmLargura(const Grafo &inventario, int s, set<int> &marcados){
    queue<int> F;
    set<int> emF;

    marcados.insert(s);
    F.push(s);
    emF.insert(s);

    while(!F.empty()){
        int v = F.front();

        for(const Aresta &aresta : inventario.adjacencia.at(v)){
            int w = aresta.destino;

            if(!marcados.count(w)){
                cout << inventario.vertices.at(v).nome_item << " (" << v << ") -- " << inventario.vertices.at(w).nome_item << " (" << w << ") | S = " << aresta.similaridade << endl;
                marcados.insert(w);
                F.push(w);
                emF.insert(w);
            }
            else if(emF.count(w)){
                cout << inventario.vertices.at(v).nome_item << " (" << v << ") -- " << inventario.vertices.at(w).nome_item << " (" << w << ") | S = " << aresta.similaridade << endl;
            }
        }

        F.pop();
        emF.erase(v);
    }
}

// Percorre todos os componentes do grafo com BFS
void exibirSimilaridadesBFS(const Grafo &inventario){
    set<int> marcados;

    for(const auto &par : inventario.vertices){
        if(!marcados.count(par.first)){
            buscaEmLargura(inventario, par.first, marcados);
        }
    }
}