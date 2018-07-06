#include "./../include/ListSentinel.h"
#include "./../include/Block.h"
#include <vector>
#include <iostream>

using namespace std;

template <class T> List<T>::List() {}

template <class T> List<T>::List(vector<T> & input) {
    for(unsigned int itg = 0; itg < input.size(); itg++) {
        this->add(input[itg]);
    }
}

template <class T> List<T>::~List() {
    this->clear();
};

template <class T> void List<T>::clear() {
    Cell<T> * cell = this->first;

    if(cell == NULL)
        return;
    do {
        Cell<T> * cycle = cell->next;
        delete cell;

        cell->next = NULL;
        cell->previous = NULL;
        cell = NULL;

        cell = cycle;
    } while(cell->next != NULL);

    this->first = NULL;
    this->last = NULL;
    this->sentinel = NULL;

    this->length = 0;
}

template <class T> bool List<T>::isEmpty() const {
	return this->length == 0;
};

template <class T> unsigned int List<T>::size() const {
	return this->length;
};

template <class T> Cell<T> * List<T>::remove() {
    if(this->isEmpty())
        return NULL;

    if(this->length == 1) {
        Cell<T> * result = this->sentinel;

        this->sentinel->next = NULL;
        this->sentinel->previous = NULL;
        this->sentinel = NULL;

        this->length--;

        return result;
    } else {
        this->sentinel->previous->next = this->sentinel->next;
        this->sentinel->next->previous = this->sentinel->previous;

        Cell<T> * prov = this->sentinel->previous;
        Cell<T> * result = this->sentinel;

        this->sentinel->next = NULL;
        this->sentinel->previous = NULL;
        this->sentinel = NULL;

        this->sentinel = prov;

        this->length--;

        return result;
    }
};

template <class T> T List<T>::get() const {
    return this->sentinel->item;
};

template <class T> void List<T>::print() const {
    Cell<T> * cell = this->first;

    if(cell == NULL)
        return;

    do {
        cout << cell->item << " ";
        cell = cell->next;
    } while(cell != this->first);

    cout << endl;
};

template <class T> void List<T>::add(T item) {
    Cell<T> * cell = new Cell<T>;
    cell->item = item;

    if(this->isEmpty()) {
        this->first = cell;
        this->last = cell;
        this->sentinel = cell;

        cell->next = this->last;
        cell->previous = this->first;
    } else {
        Cell<T> * prov = this->sentinel->next;

        this->sentinel->next = cell;
        cell->previous = this->sentinel;

        prov->previous = cell;
        cell->next = prov;

        this->sentinel = cell;
    }

    this->length++;
};

template <class T> void List<T>::add(Cell<T> * cell) {
    if(this->isEmpty()) {
        this->first = cell;
        this->last = cell;
        this->sentinel = cell;

        cell->next = this->last;
        cell->previous = this->first;
    } else {
        Cell<T> * prov = this->sentinel->next;

        this->sentinel->next = cell;
        cell->previous = this->sentinel;

        prov->previous = cell;
        cell->next = prov;

        this->sentinel = cell;
    }

    this->length++;
};

template <class T> bool List<T>::endOfList() {
    return (this->sentinel == this->first || this->sentinel == this->last);
}

template <class T> void List<T>::moveForwards() {
    if(this->sentinel != NULL)
        this->sentinel = this->sentinel->next;
}

template <class T> void List<T>::moveBackwards() {
    if(this->sentinel != NULL)
        this->sentinel = this->sentinel->previous;
}

template <class T> void List<T>::moveAtFirst() {
    if(this->isEmpty())
        return;

    this->sentinel = this->first;
}

template <class T> void List<T>::moveAtLast() {
    if(this->isEmpty())
        return;

    this->sentinel = this->last;
}

template class List<char>;
template class List<Block *>;