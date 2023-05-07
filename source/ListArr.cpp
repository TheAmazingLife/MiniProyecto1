#include "..\include\ListArr.hpp"

#include <iostream>

ListArr::ListArr(int dataCap) : dataCapacity(dataCap) {
    this->head = nullptr;
    this->tail = nullptr;
    this->summaryRoot = nullptr;
}

ListArr::~ListArr() {
    // TODO: Eliminar todos los nodos
}

void ListArr::insert(int v, int index) {

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
        for (int i = 0; i < current->size; i++) {
            std::cout << current->array[i];
            if (i < current->size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        current = current->next;
    }
    std::cout << std::endl;
}

int ListArr::size() {
    return summaryRoot->sum;
}

bool ListArr::find(int v) {
    DataNode* current = head;
    while (current != nullptr) {
        for (int i = 0; i < current->size; i++) {
            if (current->array[i] == v) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}
