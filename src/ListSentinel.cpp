#include "./../include/ListSentinel.h"
#include <iostream>

template <class T>
List<T>::List() {}

template <class T>
List<T>::~List() {
    while(this->sentinel->next != NULL) {
        Cell<T> * cell = this->sentinel->next;
        delete this->sentinel;
        this->sentinel = NULL;
        this->sentinel = cell;
    }

    this->first = NULL;
    this->last = NULL;
    this->sentinel = NULL;
};

template <class T>
void List<T>::clear() {
    while(this->sentinel->next != NULL) {
        Cell<T> * cell = this->sentinel->next;
        delete this->sentinel;
        this->sentinel = NULL;
        this->sentinel = cell;
    }

    this->first = NULL;
    this->last = NULL;
    this->sentinel = NULL;
}

template <class T>
bool List<T>::isEmpty() const {
	return this->prem == NULL && this->last == NULL && this->sentinel == NULL;
};

template <class T>
unsigned int List<T>::size() const {
	return size;
};

template <class T>
void List<T>::remove() {
    this->sentinel->previous->next = this->sentinel->next;
    this->sentinel->next->previous = this->sentinel->previous;

    if(this->sentinel == this->first)
        this->first = this->sentinel->next;
    else if(this->sentinel == this->last)
        this->last = this->sentinel->previous;

    Cell<T> * cell = this->sentinel->next;
    delete this->sentinel;
    this->sentinel = cell;
};

template <class T>
T List<T>::at(unsigned int index) const {
    return this->sentinel->item;
};

template <class T>
void List<T>::insert(T item) {
    Cell<T> * cell = new Cell<T>;
    cell->item = item;
    cell->previous = this->sentinel->previous;
    cell->next = this->sentinel->next;

    if(this->sentinel == this->first || this->sentinel == this->last) {
        this->first = cell;
        this->last = cell;
    }
};

template <class T>
void List<T>::moveForwards() {
    this->sentinel = this->sentinel->next;
}

template <class T>
void List<T>::moveBackwards() {
    this->sentinel = this->sentinel->previous;
}