#pragma once

#include "SummaryNode.hpp"

#include <vector>

class SummaryTree {
  private:
    std::vector<SummaryNode*> leaves; // Vector de SummaryNode

  public:
    // SummaryTree(std::vector<DataNode*>& dataNodes); // constructor
    
    void duplicateLeaves(); // no se como XD
    void insert(DataNode* data); // insertar un nodo dato
    SummaryNode* buildTree(); // crea un arbol a partir del vector de hojas
};
