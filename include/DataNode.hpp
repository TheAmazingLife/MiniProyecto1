#pragma once

// Nodo Data que almacena un arreglo de tamaño máximo `maxCapacity`.
struct DataNode {
    int maxCapacity; // El tamaño máximo del arreglo `array`.
    int usedCapacity; // El número de elementos actualmente almacenados en el arreglo `array`.
    DataNode *previous, *next; // `next` El nodo siguiente en la lista enlazada. `prev` El nodo anterior en la lista enlazada.
    int* array; // Un puntero al arreglo de enteros, inicializado con tamaño `maxCapacity`.

    DataNode(int capacity, DataNode* prev = nullptr, DataNode* next = nullptr);
    ~DataNode();
};
