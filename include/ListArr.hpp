#pragma once

#include "ListArrADT.hpp"
#include "DataNode.hpp"
#include "SummaryNode.hpp"

#include <vector>

class ListArr : public ListArrADT {
  private:
    int dataMaxCapacity;

    DataNode* head;
    DataNode* tail;
    int dataNodes_count;

    SummaryNode* summaryRoot;
    std::vector<SummaryNode*> summaryNodes;

    //* Estructuras auxiliares

    void expandListArr();

  public:
    ListArr(int dataCap = 1);
    ~ListArr();

    void insert(int value, int index);
    void insert_left(int value);
    void insert_right(int value);
    void print();

    int size();
    bool find(int value);
};
