//
// Created by Marcelo on 9/4/2023.
//

#ifndef LOWRESPLOTTER_GRAPH_H
#define LOWRESPLOTTER_GRAPH_H


class Graph {
private:
    char blank;
    char blankColor;
    char* clearBuffer;
    char* writeBuffer;
    char* readBuffer;
    int COLS, ROWS;
public:
    Graph(int COLS, int ROWS, char blank = 219, char blankColor = 231);
    ~Graph();

    void plotPixel(char c, char rgb);
    void plotPixel(char c, char r, char g, char b);
    void clear();
    void swapBuffers();
    void display();
};


#endif //LOWRESPLOTTER_GRAPH_H
