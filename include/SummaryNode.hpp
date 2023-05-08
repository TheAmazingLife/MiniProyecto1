#pragma once

#include "DataNode.hpp"

// Estructura que representa un nodo resumenn en el arbol.
struct SummaryNode {
    int MaxCapacity; /**< Tamaño máximo de los arreglos. */
    int usedCapacity; /**< Capacidad usada. */

    SummaryNode *SummNodeL, *SummNodeR; /**< Punteros a los nodos resumen izquierdo y derecho. */
    DataNode *DataNodeL, *DataNodeR; /**< Punteros a los nodos de datos izquierdo y derecho. */
    
    // Constructor para nivel Hoja 0.
    SummaryNode(DataNode* data1, DataNode* data2);

    // Constructor para nivel > 0.
    SummaryNode(SummaryNode* sum1, SummaryNode* sum2);
};
