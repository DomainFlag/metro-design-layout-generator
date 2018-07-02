#ifndef LIST_SENTINEL
#define LIST_SENTINEL

template <typename T>
struct Cell {
    T * item;
    Cell<T> * next;
    Cell<T> * previous;
};

template <class T>
class List {
public:
    int length = 0;
    Cell<T> * sentinel;
    Cell<T> * first;
    Cell<T> * last;

    List();

    ~List();

    void clear();

    bool isEmpty() const;

    unsigned int size() const;

    T at(unsigned int index) const;

    void remove();

    void insert(T item);

    void moveForwards();

    void moveBackwards();

};

#endif