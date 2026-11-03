#ifndef INVENTARIO_H
#define INVENTARIO_H
#include <string>
#include <list>
#include <map>

enum Raridade {
    Comum,
    Raro,
    Epico,
    Lendario,
    Mitico
};

struct Item {
    string nome_item;
    string nome_dono;
    string propriedade_magica;
    int id;
    Raridade raridade;
};

struct Aresta{
    int destino;
    int similaridade;
};

struct Grafo{
    map<int, Item> vertices;
    map<int, list<Aresta>> adjacencia;
};

Raridade classificarRaridade(int valor);
void inserirItem(list<Item> &inventario_provisorio, Item novo_item);
bool inserirVertice(Grafo &inventario, Item item);
bool existeItem(const Grafo &inventario, int id);
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade);
void exibirSimilaridadesBFS(const Grafo &inventario);
bool existeItemPorNome(const list<Item> &inventario_provisorio, const string &nome);

#endif
