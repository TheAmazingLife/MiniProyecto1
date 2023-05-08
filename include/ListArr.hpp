#pragma once

#include "ListArrADT.hpp"
#include "DataNode.hpp"
#include "SummaryNode.hpp"

#include <vector>

/* Implementacion de una lista usando una estructura de arreglo */
class ListArr : public ListArrADT {
  private:
    int dataMaxCapacity; /**< La capacidad máxima para cada DataNode */

    DataNode* head; /**< Un puntero a la cabeza de la lista */
    DataNode* tail; /**< Un puntero a la cola de la lista */
    int dataNodes_count; /**< El número de DataNodes en la lista */

    SummaryNode* summaryRoot; /**< Un puntero a la raíz de la estructura resumen */
    std::vector<SummaryNode*> summaryNodes; /**< Un vector que contiene todos los SummaryNodes en la estructura */

    //* Estructuras auxiliares

    //Función auxiliar para expandir ListArr cuando se alcanza la capacidad actual
    void expandListArr();

  public:
    // Constructor, `dataCap` La capacidad máxima para cada DataNode
    ListArr(int dataCap = 1);
    // Destructor para la clase ListArr
    ~ListArr();

    void insert(int value, int index); // Inserta un valor en el índice especificado en la lista
    void insert_left(int value); // Inserta un valor en el extremo izquierdo de la lista
    void insert_right(int value); // Inserta un valor en el extremo derecho de la lista
    void print(); // Imprime los valores en la lista

    int size(); // Devuelve el número de elementos en la lista
    bool find(int value); // Busca un valor en la lista, Verdadero si se encuentra el valor, falso en caso contrario
};