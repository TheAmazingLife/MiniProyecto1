#pragma once

#include "DataNode.hpp"

struct SummaryNode {
    int MaxCapacity; // tamaño máximo b
    int usedCapacity; // capacidad usada (extra: tiene el valor de cap[0] + cap[1], capacidad sumadas :(

    SummaryNode *SummNodeL, *SummNodeR;
    DataNode *DataNodeL, *DataNodeR;
    
    SummaryNode(DataNode* data1, DataNode* data2); // Nivel Hoja 0
    SummaryNode(SummaryNode* sum1, SummaryNode* sum2); // Nivel > 0
};
