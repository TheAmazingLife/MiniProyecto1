#pragma once

#include "DataNode.hpp"

struct SummaryNode {
    int capacity;
    int sum;
    SummaryNode* childNodes[2];
    DataNode* dataNodes[2];

    SummaryNode(); // Constructor dependerá de cómo se implemente el árbol
};
