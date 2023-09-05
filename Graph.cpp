//
// Created by Marcelo on 9/4/2023.
//
#include <iostream>
#include <cstring>
#include "Graph.h"

using namespace std;

Graph::Graph(int COLS, int ROWS, char blank, char blankColor) {
    this->blank = blank;
    this->blankColor = blankColor;

    this->COLS = COLS;
    this->ROWS = ROWS;
    //there are 12 characters per each pixel (for the escape codes)
    //and 1 extra character for the newline, for n rows, and 1
    //more character for the null terminator
    this->clearBuffer = new char[(COLS * 12 + 1) * ROWS + 1];
    this->writeBuffer = new char[(COLS * 12 + 1) * ROWS + 1];
    this->readBuffer = new char[(COLS * 12 + 1) * ROWS + 1];

    //If anything goes horribly wrong it will just terminate early
    memset(this->clearBuffer, '\0', (COLS * 12 + 1) * ROWS + 1);

    for(int y = 0; y < ROWS; y++) {
        this->clearBuffer[y*(COLS * 12 + 1) + COLS*12] = '\n';
        for(int x = 0; x < COLS; x++) {
            int idx = y * (COLS * 12 + 1) + x * 12;
            this->clearBuffer[idx] = '\033';
            this->clearBuffer[idx + 1] = '[';
            this->clearBuffer[idx + 2] = '3';
            this->clearBuffer[idx + 3] = '8';
            this->clearBuffer[idx + 4] = ';';
            this->clearBuffer[idx + 5] = '5';
            this->clearBuffer[idx + 6] = ';';
            this->clearBuffer[idx + 7] = '2';
            this->clearBuffer[idx + 8] = '3';
            this->clearBuffer[idx + 9] = '1';
            this->clearBuffer[idx + 10] = 'm';
            this->clearBuffer[idx + 11] = blank;
        }
    }
    this->clearBuffer[(COLS * 12 + 1) * ROWS] = '\0';

    //make read and write buffers the clear buffer by default
    memcpy(this->readBuffer, this->clearBuffer, (COLS * 12 + 1) * ROWS + 1);
    memcpy(this->writeBuffer, this->clearBuffer, (COLS * 12 + 1) * ROWS + 1);
}
Graph::~Graph() {
    delete[] this->clearBuffer;
    delete[] this->readBuffer;
    delete[] this->writeBuffer;
}

void Graph::plotPixel(char c, char rgb) {}
void Graph::plotPixel(char c, char r, char g, char b) {}
void Graph::clear() {}
void Graph::swapBuffers() {}
void Graph::display() {
    cout << "\033[H" << flush;
    cout << this->clearBuffer << flush;
}