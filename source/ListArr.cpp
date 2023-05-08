#include "..\include\ListArr.hpp"

#include <iostream>

//* Métodos públicos
ListArr::ListArr(int dataCap) : dataMaxCapacity(dataCap) {
    head = new DataNode(dataMaxCapacity);
    tail = new DataNode(dataMaxCapacity);
    head->next = tail;
    tail->previous = head;
    dataNodes_count = 2;

    summaryRoot = new SummaryNode(head, tail);
    summaryNodes.push_back(summaryRoot);
}

ListArr::~ListArr() {
    // TODO: Eliminar todos los nodos

}

void ListArr::insert(int v, int index) {
    // Comprobar si el indice es valido
    if (index < 0 || index > summaryRoot->usedCapacity) {
        std::cout << "Index out of bounds" << std::endl;
        return;
    }

    // Comprobar si se necesita expandir la capacidad de ListArr
    if (summaryRoot->usedCapacity == summaryRoot->MaxCapacity) {
        
    }
}

void ListArr::insert_left(int v) {
    
}

void ListArr::insert_right(int v) {
    
}

void ListArr::print() {
    std::cout << "ListArr: " << std::endl;

    DataNode* current = head;
    while (current != nullptr) {
        std::cout << "[";
        for (int i = 0; i < current->usedCapacity; i++) {
            std::cout << current->array[i];
            if (i < current->usedCapacity - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        current = current->next;
    }
    std::cout << std::endl;
}

int ListArr::size() {
    return summaryRoot->usedCapacity;
}

bool ListArr::find(int v) {
    DataNode* current = head;
    while (current != nullptr) {
        for (int i = 0; i < current->usedCapacity; i++) {
            if (current->array[i] == v) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

//* Métodos privados
void ListArr::expandListArr() {
    dataNodes_count *= 2; // duplicar la cantidad de nodos de datos

    // Agregar los nuevos nodos de datos
    for (int i = 0; i < dataNodes_count/2; i++) {
        DataNode* newDataNode = new DataNode(dataMaxCapacity);
        newDataNode->previous = tail;
        tail->next = newDataNode;
        tail = newDataNode;
    }

    // Agregar los nuevos nodos de resumen
    
}
