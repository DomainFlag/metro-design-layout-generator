#ifndef LIST_SENTINEL
#define LIST_SENTINEL

#include <iostream>
#include <vector>
#include "./Block.h"

template <typename T>
struct Cell {
    T item;
    Cell<T> * next;
    Cell<T> * previous;
};

template <class T>
class List {
public:
    int length = 0;
    Cell<T> * sentinel = NULL;
    Cell<T> * first = NULL;
    Cell<T> * last = NULL;

    List();

    List(vector<T> & input);

    ~List();

    void clear();

    bool isEmpty() const;

    unsigned int size() const;

    T get() const;

    void print() const;

    Cell<T> * remove();

    void add(T item);

    void add(Cell<T> * cell);

    bool endOfList();

    void moveForwards();

    void moveBackwards();

    void moveAtFirst();

    void moveAtLast();
};

#endif