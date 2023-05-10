#include "..\include\DataNode.hpp"

// Construye un nuevo DataNode con la capacidad dada, nodo siguiente y nodo anterior.
DataNode::DataNode(int cap, DataNode* prev, DataNode* next)
                : maxCapacity(cap), previous(prev), next(next) {
    this->array = new int[maxCapacity];
    // for (int i = 0; i < maxCapacity; i++) {
    //     array[i] = 0;
    // }
    
    this->usedCapacity = 0;
}

// Destructor de la clase DataNode.
DataNode::~DataNode() {
    delete[] array;
}