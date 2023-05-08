#include "..\include\SummaryNode.hpp"

// Constructor para nivel 0
SummaryNode::SummaryNode(DataNode* dataNode1, DataNode* dataNode2) {
    this->DataNodeL = dataNode1;
    this->DataNodeR = dataNode2;
    this->SummNodeL = nullptr;
    this->SummNodeR = nullptr;
    this->usedCapacity = dataNode1->usedCapacity + dataNode2->usedCapacity;
    this->MaxCapacity = dataNode1->maxCapacity + dataNode2->maxCapacity;
}

// Constructor para nivel > 0
SummaryNode::SummaryNode(SummaryNode* summNode1, SummaryNode* summNode2) {
    this->DataNodeL = nullptr;
    this->DataNodeR = nullptr;
    this->SummNodeL = summNode1;
    this->SummNodeR = summNode2;
    this->MaxCapacity = summNode1->MaxCapacity + summNode2->MaxCapacity;
    this->usedCapacity = summNode1->usedCapacity + summNode2->usedCapacity;
}
