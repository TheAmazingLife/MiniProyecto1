#pragma once

struct DataNode {
    int capacity;
    DataNode* next;
    int* array;
    int size;

    DataNode(int capacity, DataNode* next = nullptr);
};
