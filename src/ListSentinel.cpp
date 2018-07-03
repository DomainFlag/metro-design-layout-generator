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
        cout << "Deleted:" << cell->item << endl;
        delete cell;

        cell->next = NULL;
        cell->previous = NULL;
        cell = NULL;

        cell = cycle;
    } while(cell->next != NULL);

    cout << "Deleted successfully: " << this->length << " elements."<< endl;

    this->first = NULL;
    this->last = NULL;
    this->sentinel = NULL;

    this->length = 0;
}

template <class T> bool List<T>::isEmpty() const {
	return (this->first == NULL && this->last == NULL && this->sentinel == NULL);
};

template <class T> unsigned int List<T>::size() const {
	return this->length;
};

template <class T> void List<T>::remove() {
    if(this->sentinel == NULL)
        return;

    if(this->sentinel == this->first && this->sentinel == this->last) {
        this->first = NULL;
        this->last = NULL;

        this->length--;

        delete this->sentinel;
        this->sentinel->next = NULL;
        this->sentinel->previous = NULL;
        this->sentinel = NULL;

        return;
    }

    this->sentinel->previous->next = this->sentinel->next;
    this->sentinel->next->previous = this->sentinel->previous;

    if(this->sentinel == this->first)
        this->first = this->sentinel->next;
    else if(this->sentinel == this->last)
        this->last = this->sentinel->previous;

    Cell<T> * cell = this->sentinel->next;

    delete this->sentinel;
    this->length--;
    this->sentinel->next = NULL;
    this->sentinel->previous = NULL;
    this->sentinel = NULL;

    this->sentinel = cell;
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

        cell->next = this->last;
        cell->previous = this->first;

        this->sentinel = cell;
    } else {
        this->first->previous = cell;
        this->last->next = cell;

        cell->next = this->first;
        cell->previous = this->last;

        this->last = cell;
    }

    this->length++;
};

template <class T> bool List<T>::endOfList() {
    return (this->sentinel == this->first || this->sentinel == this->last);
}

template <class T> bool List<T>::moveForwards() {
    if(this->isEmpty())
        return false;

    if(this->sentinel->next == this->first)
        return false;
    else {
        this->sentinel = this->sentinel->next;
    }

    return true;
}

template <class T> bool List<T>::moveBackwards() {
    if(this->isEmpty())
        return false;

    if(this->sentinel->previous == this->last)
        return false;
    else {
        this->sentinel = this->sentinel->previous;
    }

    return true;
}

template class List<char>;
template class List<Block *>;