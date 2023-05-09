#include "..\include\SummaryNode.hpp"

// Constructor para nivel 0
SummaryNode::SummaryNode(DataNode* dataNode1, DataNode* dataNode2) {
    this->dataLeft = dataNode1;
    this->dataRight = dataNode2;
    this->summLeft = nullptr;
    this->summRight = nullptr;
    this->usedCapacity = dataNode1->usedCapacity + dataNode2->usedCapacity;
    this->maxCapacity = dataNode1->maxCapacity + dataNode2->maxCapacity;
}

// Constructor para nivel > 0
SummaryNode::SummaryNode(SummaryNode* summNode1, SummaryNode* summNode2) {
    this->dataLeft = nullptr;
    this->dataRight = nullptr;
    this->summLeft = summNode1;
    this->summRight = summNode2;
    this->maxCapacity = summNode1->maxCapacity + summNode2->maxCapacity;
    this->usedCapacity = summNode1->usedCapacity + summNode2->usedCapacity;
}
