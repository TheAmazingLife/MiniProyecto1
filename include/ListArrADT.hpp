#pragma once

class ListArrADT {
  public:
    virtual void insert(int value, int index) = 0;
    virtual void insert_left(int value) = 0;
    virtual void insert_right(int value) = 0;
    virtual void print() = 0;

    virtual int size() = 0;
    virtual bool find(int value) = 0;
};
