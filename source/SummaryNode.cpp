#include "..\include\SummaryNode.hpp"

SummaryNode::SummaryNode() {
    this->capacity = 0;
    this->sum = 0;
    this->childNodes[0] = nullptr;
    this->childNodes[1] = nullptr;
    this->dataNodes[0] = nullptr;
    this->dataNodes[1] = nullptr;
}
