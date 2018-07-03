#include "./../include/ListSentinel.h"
#include <iostream>

using namespace std;

void secondTest() {
    List<char> * list = new List<char>;

    list->moveForwards();
    list->moveBackwards();

    list->add('a');
    list->add('b');
    // -> [a, b]

    list->moveForwards();
    // -> [a, *]

    cout << list->get();
    // -> b
    list->moveBackwards();
    // -> [*, b]
    cout << list->get();
    // -> a
    list->moveForwards();
    // -> [a, *]
    cout << list->get();
    // -> b
    cout << list->endOfList() << endl;
    // -> 1
    list->moveForwards();
    // -> [*, b]
    cout << list->get();
    // -> a
}

void firstTest() {
    List<char> * list = new List<char>;

    for(int itg = 0; itg < 1000; itg++) {
        list->add('a');
        list->clear();
    }

    for(int ith = 0; ith < 1000; ith++) {
        list->add('b');
    }

    for(int iti = 0; iti < 250; iti++)
        list->remove();

    delete list;
}

int main() {
    firstTest();

    secondTest();

    return 0;
}