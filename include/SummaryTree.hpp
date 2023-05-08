#pragma once

#include "SummaryNode.hpp"


#include <vector>

class SummaryTree {
  private:
    std::vector<SummaryNode*> leaves; /**< Vector de punteros a summary nodes que representa las hojas del árbol */
    // ! Posible solucion es pasar como parametro leaves o implementar la funcion buildTree en ListArr
  public:
    ~SummaryTree();
    SummaryNode* buildTree(); // Construye un árbol de summary nodes a partir de un vector de summary nodes ordenados.
    void duplicateLeaves(); // TODO: hacer el metodo
    void insert(DataNode* data); // Inserta un nuevo nodo de datos en el árbol.
};
