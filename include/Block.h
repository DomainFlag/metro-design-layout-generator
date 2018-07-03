#ifndef BLOCK
#define BLOCK

#include <iostream>
using namespace std;

class Block {
public:
    int width, height;
    char symbol;

    Block(char symbol, int width, int height);

    void print();
};

#endif