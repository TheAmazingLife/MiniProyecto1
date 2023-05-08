#pragma once

// La clase ListArrADT es una clase abstracta base para una lista implementada con un arreglo.
class ListArrADT {
  public:
    virtual void insert(int value, int index) = 0; // Inserta un valor en el índice especificado.
    virtual void insert_left(int value) = 0; // Inserta un valor al principio de la lista.
    virtual void insert_right(int value) = 0; // Inserta un valor al final de la lista.
    virtual void print() = 0; // Imprime el contenido de la lista.

    virtual int size() = 0; // Devuelve el número de elementos en la lista.
    virtual bool find(int value) = 0; // Busca un valor en la lista.
};
