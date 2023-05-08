#pragma once

// Nodo Data que almacena un arreglo de tamaño máximo `maxCapacity`.
struct DataNode {
    int maxCapacity; // El tamaño máximo del arreglo `array`.
    int usedCapacity; // El número de elementos actualmente almacenados en el arreglo `array`.
    DataNode *next, *previous; // `next` El nodo siguiente en la lista enlazada. `prev` El nodo anterior en la lista enlazada.
    int* array; // Un puntero al arreglo de enteros, inicializado con tamaño `maxCapacity`.

    /**
     * @brief Constructor que inicializa un nuevo nodo de datos.
     * 
     * @param capacity El tamaño máximo del arreglo `array`.
     * @param next El nodo siguiente en la lista enlazada.
     * @param prev El nodo anterior en la lista enlazada.
     */
    DataNode(int capacity, DataNode* next = nullptr, DataNode* prev = nullptr);
    ~DataNode();
};
