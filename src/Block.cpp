#include "./../include/Block.h"
#include <iostream>
using namespace std;

Block::Block(char symbol, int width, int height) {
    this->symbol = symbol;
    this->width = width;
    this->height = height;
}

void Block::print() {
    cout << "Symbol: " << this->symbol << endl;
    cout << "Width: " << this->width << endl;
    cout << "Height: " << this->height << endl;
}