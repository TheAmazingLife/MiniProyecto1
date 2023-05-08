#pragma once

struct DataNode {
    int maxCapacity; // tamaño b
    int usedCapacity;
    DataNode *next, *previous;
    int* array; // inicializado en "b", = new array(b)

    DataNode(int capacity, DataNode* next = nullptr, DataNode* prev = nullptr);
};
