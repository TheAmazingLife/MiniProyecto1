#include "..\include\DataNode.hpp"

DataNode::DataNode(int cap, DataNode* n) : capacity(cap), next(n) {
    this->array = new int[capacity];
    this->size = 0;
}

DataNode::~DataNode() {
    delete[] array;
}