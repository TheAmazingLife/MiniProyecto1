#include "..\include\SummaryNode.hpp"

// Constructor para nivel 0
SummaryNode::SummaryNode(DataNode* dataNode1, DataNode* dataNode2) {
    this->dataL = dataNode1;
    this->dataR = dataNode2;
    this->summL = nullptr;
    this->summR = nullptr;
    this->usedCapacity = dataNode1->usedCapacity + dataNode2->usedCapacity;
    this->maxCapacity = dataNode1->maxCapacity + dataNode2->maxCapacity;
}

// Constructor para nivel > 0
SummaryNode::SummaryNode(SummaryNode* summNode1, SummaryNode* summNode2) {
    this->dataL = nullptr;
    this->dataR = nullptr;
    this->summL = summNode1;
    this->summR = summNode2;
    this->maxCapacity = summNode1->maxCapacity + summNode2->maxCapacity;
    this->usedCapacity = summNode1->usedCapacity + summNode2->usedCapacity;
}
