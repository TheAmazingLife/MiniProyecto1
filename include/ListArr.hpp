#pragma once

#include "ListArrADT.hpp"
#include "DataNode.hpp"
#include "SummaryNode.hpp"

class ListArr : public ListArrADT {
  private:
    int dataCapacity;
    DataNode* head;
    DataNode* tail;

    SummaryNode* summaryRoot;

    //* Estructuras auxiliares

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
