#include "..\include\DataNode.hpp"

DataNode::DataNode(int cap, DataNode* next, DataNode* prev) : maxCapacity(cap), next(next), previous(prev) {
    this->array = new int[maxCapacity];
    this->usedCapacity = 0;
}

DataNode::~DataNode() {
    delete[] array;
}
