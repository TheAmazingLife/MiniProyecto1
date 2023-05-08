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
    std::vector<SummaryNode*> vectorSummaryNodes; /**< Un vector que contiene todos los SummaryNode en la estructura */

    // ? en vez de usar `leaves` usar `vectorSummaryNodes`
    // std::vector<SummaryNode*> leaves; /**< Vector de punteros a summary nodes que representa las hojas del árbol */

    //* Estructuras auxiliares

    // TODO: Función auxiliar para expandir ListArr cuando se alcanza la capacidad actual
    void expandListArr();

    ///// TODO: Metodo destructor de vector `leaves`
    ///// ? Metodo tal vez innecesario ya que no se eliminan los Nodos Summary solo se actualizan
    //// void deleteSumm();

    // Construye un árbol apartir de un vector de SummaryNodes ordenados.
    // Retorna un Puntero a la raiz del arbol
    // TODO: hacer que luego de duplicar se actualice el nodo `summaryRoot`
    //// SummaryNode* buildTree();

    // Insertar un nodo de datos en el arbol como una hoja
    // TODO: comprobar funcionamiento
    //// void insertSumm(SummaryNode* data); // ! INNECESARIO

    // * Generador de summaryRoot
    SummaryNode* buildTree();
  public:
    // Constructor, `dataCap` La capacidad máxima para cada DataNode
    ListArr(int dataCap = 1);
    // TODO: Destructor para la clase ListArr
    ~ListArr();

    void insert(int value, int index); // TODO: Inserta un valor en el índice especificado en la lista
    void insert_left(int value); // TODO: Inserta un valor en el extremo izquierdo de la lista
    void insert_right(int value); // TODO: Inserta un valor en el extremo derecho de la lista
    void print(); // Imprime los valores en la lista

    int size(); // Devuelve el número de elementos en la lista
    bool find(int value); // Busca un valor en la lista, Verdadero si se encuentra el valor, falso en caso contrario
};