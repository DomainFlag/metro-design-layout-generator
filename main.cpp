#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Photo {
public:
    int width, height;
    char symbol;

    Photo(char symbol, int width, int height) {
        this->symbol = symbol;
        this->width = width;
        this->height = height;
    }

    void print() {
        cout << "Symbol: " << this->symbol << endl;
        cout << "Width: " << this->width << endl;
        cout << "Height: " << this->height << endl;
    }
};

class Metro {
public:
    vector<Photo> input;
    vector<vector<char> > output;
    int width, height = 0;
    int maxWidth = 0;

    Metro(vector<Photo> data, int width) {
        this->input = data;
        this->width = width;

        for(int it = 0; it < this->input.size(); it++)
            maxWidth += this->input[it].width;
    }

    bool checkBounds() {
        if(this->width >= this->maxWidth || this->width == 0 || this->height == 0)
            return true;


        bool flag = false;
        bool boundary = false;

        if(this->output[0][this->width-1] != '0') {
            flag = true;
        }

        for(int g = 1; g < this->height; g++)
            if(this->output[g][this->width-1] == '0')
                if(flag) boundary = true;
            else {
                if(boundary || !flag)
                    return false;
            }

        return true;
    }

    bool checkPhoto(Photo & photo, int width, int height) {
        int maxWidth = photo.width+width;
        int maxHeight = photo.height+height;

        if(maxWidth > this->width || maxHeight > this->height)
            return false;

        for(int g = height; g < maxHeight; g++)
            for(int h = width; h < maxWidth; h++)
                if(this->output[g][h] != '0')
                    return false;

        return true;
    }

    void fillPhoto(Photo & photo, int width, int height) {
        int maxWidth = photo.width+width;
        int maxHeight = photo.height+height;

        for(int g = height; g < maxHeight; g++)
            for(int h = width; h < maxWidth; h++)
                this->output[g][h] = photo.symbol;
    }

    void unfillPhoto(Photo & photo, int width, int height) {
        int maxWidth = photo.width+width;
        int maxHeight = photo.height+height;

        for(int g = height; g < maxHeight; g++)
            for(int h = width; h < maxWidth; h++)
                this->output[g][h] = '0';
    }

    void expand() {
        for(int g = 0; g < this->width; g++)
            for(int h = 0; h < this->height; h++)
                this->output[h][g] = '0';

        this->height++;
        this->output.resize(this->height, vector<char>(this->width, '0'));
    };

    void print() {
        for(unsigned int g = 0; g < output.size(); g++) {
            for(unsigned int h = 0; h < output[g].size(); h++) {
                cout << output[g][h];
            }
            cout << endl;
        }
        cout << endl;
    }

    void getSize() {
        cout << "Input size: " << this->input.size() << endl;
        cout << "Output size: " << this->output.size() << endl;
    }
};

vector<Photo> readInputFile(const string fileName) {
    fstream file(fileName.c_str());
    vector<Photo> data;

    if(file.is_open()) {
        cout << "Opened for reading content" << endl;

        string line;
        unsigned int width = 0, height = 0;
        char symbol = 'a';
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
                data.push_back(Photo(symbol, width, height));
                symbol++;
                width = 0;
                height = 0;
            }
        }

        // For the last block(Photo)
        if(width != 0 || height != 0) {
            data.push_back(Photo(symbol, width, height));
        }
    }

    return data;
}

bool fillMetro(Metro & metro, vector<Photo> input) {
    if(input.empty())
        return true;

    for(int it = input.size()-1; it >= 0; it--) {
        Photo photo = input[it];

        for(int g = 0; g < metro.width; g++) {
            for(int h = 0; h < metro.height; h++) {

                if(metro.checkPhoto(input[it], g, h)) {
                    metro.fillPhoto(input[it], g, h);

                    if(!metro.checkBounds()) {
                        metro.unfillPhoto(photo, g, h);
                    } else {
                        input.erase(input.begin()+it);
                        if(!fillMetro(metro, input)) {
                            metro.unfillPhoto(photo, g, h);

                            input.insert(input.begin()+it, photo);
                        } else return true;
                    }
                };
            }
        }
    }

    return false;
}

void createMetro(Metro & metro) {
    while(!fillMetro(metro, metro.input)) {
        metro.expand();
    };

    metro.print();
}

int main() {
    vector<Photo> photos = readInputFile("input.txt");
    Metro metro(photos, 5);
    createMetro(metro);

    return 0;
}