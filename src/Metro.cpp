#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/ListSentinel.h"
#include "./../include/Block.h"
using namespace std;

class Container {
public:
    int width, height;
    char ** container;
    int usedSpace = 0;

    Container(int width, int height) {
        this->width = width;
        this->height = height;

        inflate();
    }

    ~Container() {
        remove();
    }

    void remove() {
        if(this->container == NULL)
            return;

        for(int itg = 0; itg < this->height; itg++)
            delete [] this->container[itg];

        delete [] this->container;

        this->container = NULL;
    }

    void inflate() {
        this->container = new char * [this->height];
        for(int itg = 0; itg < this->height; itg++) {
            this->container[itg] = new char[this->width];
            memset(this->container[itg], '0', this->width);
        }
    }

    void expand() {
        this->remove();

        this->height += 1;
        inflate();
    }

    bool checkBlock(Block * block, int width, int height) {
        int widthMax = block->width+width;
        int maxHeight = block->height+height;

        if(widthMax > this->width || maxHeight > this->height)
            return false;

        for(int g = height; g < maxHeight; g++)
            for(int h = width; h < widthMax; h++)
                if(this->container[g][h] != '0')
                    return false;

        return true;
    }

    void fillBlock(Block * block, int width, int height) {
        int widthMax = block->width+width;
        int maxHeight = block->height+height;

        for(int g = height; g < maxHeight; g++)
            for(int h = width; h < widthMax; h++)
                this->container[g][h] = block->symbol;

        this->usedSpace += block->width*block->height;
    }

    void unfillBlock(Block * block, int width, int height) {
        int widthMax = block->width+width;
        int maxHeight = block->height+height;

        for(int g = height; g < maxHeight; g++)
            for(int h = width; h < widthMax; h++)
                this->container[g][h] = '0';

        this->usedSpace -= block->width*block->height;
    }

    void print() {
        for(int h = 0; h < this->height; h++) {
            for(int g = 0; g < this->width; g++) {
                cout << this->container[h][g];
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Metro {
public:
    vector<Block> input;
    Container * container;
    List<Block *> * blocks;

    int width, height = 0;
    int space;

    Metro(string fileName, int widthMax = 5) {
        readFile(fileName, widthMax);

        this->fillBlocks();
        this->fillContainer();
    }

    void fillContainer() {
        this->container = new Container(this->width, this->height);
        this->space = this->width*this->height;
    }

    void fillBlocks() {
        this->blocks = new List<Block *>();
        for(unsigned int itg = 0; itg < this->input.size(); itg++) {
            this->blocks->add(&input[itg]);
        }
    }

    void readFile(string fileName, int widthMax) {
        fstream file(("./tests/" + fileName).c_str());

        if(file.is_open()) {
            cout << "Opened for reading content" << endl;

            unsigned int width = 0, height = 0, widthBlocksMax = 0;
            char symbol = 'a';
            string line;
            while(getline(file, line)) {
                if(!line.empty()) {
                    if(width != 0 && width != line.size()) {
                        cout << "Illegal format of input, every block needs to be rectangular form" << endl;
                        exit(0);
                    } else if(width == 0) {
                        width = line.size();
                    }

                    height++;
                } else {
                    this->input.push_back(Block(symbol, width, height));
                    widthBlocksMax += width;

                    width = 0, height = 0;
                    symbol++;
                }
            }

            // For the last block(Block)
            if(width != 0 || height != 0) {
                this->input.push_back(Block(symbol, width, height));
                widthBlocksMax += width;
            }

            // In case the blocks are not sufficient to fill the container with a full row of blocks
            this->width = min((int) widthBlocksMax, widthMax);
        }
    }

    void size() {
        cout << "Container size: " << "w:" << this->width << " " << "h:" << this->height << endl;
    }

    bool isThereFreeSpace() {
        return (this->space-this->container->usedSpace-this->blocks->length) >= 0;
    }
};

bool fillMetro(Metro & metro) {
    if(metro.blocks->isEmpty())
        return true;

    while(metro.blocks->moveForwards()) {
        Block * block = metro.blocks->get();
        metro.blocks->remove();

        for(int g = 0; g < metro.width; g++) {
            for(int h = 0; h < metro.height; h++) {

                if(metro.container->checkBlock(block, g, h)) {
                    metro.blocks->remove();
                    metro.container->fillBlock(block, g, h);

                    if(!fillMetro(metro)) {
                        metro.blocks->add(block);
                        metro.container->unfillBlock(block, g, h);
                    } else return true;
                };
            }
        }
    }

    return false;
}

void createMetro(Metro & metro) {
    cout << metro.blocks->isEmpty() << endl;
    while(!fillMetro(metro)) {
        metro.container->expand();
    };

    metro.container->print();
}

int getMaxBlocks(vector<Block> & blocks) {
    int acc = 0;
    for(unsigned int it = 0; it < blocks.size(); it++)
        acc += blocks[it].width;

    return acc;
}

int main() {
    Metro metro("input.txt");
    createMetro(metro);

    return 0;
}