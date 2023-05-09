#pragma once

#include "ListArrADT.hpp"
#include "DataNode.hpp"
#include "SummaryNode.hpp"

#include <vector>

/* Implementacion de una lista usando una estructura de arreglo */
class ListArr : public ListArrADT {
  private:
    int dataMaxCapacity; /**< La capacidad máxima para cada DataNode */
    DataNode* dataHead; /**< Un puntero a la cabeza de la lista */
    int dataNodes_count; /**< El número de DataNodes en la lista */
    DataNode* dataTail; /**< Un puntero a la cola de la lista */
    SummaryNode* summaryRoot; /**< Un puntero a la raíz de la estructura resumen */

    // * Funciones auxiliares
    void resize(); // Expande la lista en un factor de 2
    void updateSummaryNodes(SummaryNode* currentNodo); // Actualiza el valor de los nodos
    void shiftDataToRight(DataNode* refData, int index); // Desplaza a la derecha todos los valores en el árbol resumen
    SummaryNode* buildTree(std::vector<SummaryNode*> &vectorSummaryNodes); // Construye un árbol apartir de un vector de SummaryNodes ordenados.

  public:
    ListArr(int dataCap = 1); // Constructor, `dataCap` La capacidad máxima para cada DataNode
    ~ListArr();

    void insert(int value, int index); // Inserta un valor en el índice especificado en la lista
    void insert_left(int value); // Inserta un valor en el extremo izquierdo de la lista
    void insert_right(int value); // Inserta un valor en el extremo derecho de la lista

    void print(); // Imprime los valores en la lista
    int size(); // Devuelve el número de elementos en la lista
    bool find(int value); // Busca un valor en la lista, Verdadero si se encuentra el valor, falso en caso contrario

    void printSummaries(); // Imprime los valores en los nodos del árbol resumen
};
