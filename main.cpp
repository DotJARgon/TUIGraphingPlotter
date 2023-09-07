#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>


using namespace std;

const int WIDTH = 80;
const int HEIGHT = 24;

double* a0 = new double[WIDTH];
double* a1 = new double[WIDTH];

char* buffer = new char[(WIDTH + 1) * HEIGHT + 1];


void clear() {
    cout << "\033[H" << flush;
}

void createGraphs(double t) {
    for(int i = 0; i < WIDTH; i++) {
        a0[i] = (sin(t + i * 2*M_PI / WIDTH)) + (cos(t + i * 2*M_PI / 11.8518518519));
        a1[i] = (cos(t + i * 4*M_PI / WIDTH)) + (cos(t + i * 2*M_PI / 17.7777777778));
    }
}

void rescale(double* a, int size) {
    double max_v = -INFINITY;
    double min_v = INFINITY;
    for(int i = 0; i < size; i++) {
        max_v = max(max_v, a[i]);
        min_v = min(min_v, a[i]);
    }
    double scale = 1.0 / (max_v - min_v);
    for(int i = 0; i < size; i++) {
        a[i] = ((a[i] - min_v) * scale) * HEIGHT;
    }
}

void setPixel(char c, int x, int y) {
    buffer[y * (WIDTH + 1) + x] = c;
}

void fillVLine(char c, int x, int y, int l) {
    if(l < 0) {
        for(int i = 0; i < abs(l); i++) {
            if(y - i >= 0) setPixel(c, x, y - i);
        }
    }
    else {
        for(int i = 0; i < l; i++) {
            if(y + i < HEIGHT) setPixel(c, x, y + i);
        }
    }
}

void plotGraph2(double* a, double* b, int size, char color_a, char color_b, char color_c) {
    for(int i = 0; i < size - 1; i++) {
        char c_a = color_a;
        char c_b = color_b;

        int ay0 = a[i];
        int ay1 = a[i+1];

        int al = ay1-ay0;

        if(al >= 0) al++;
        else al--;

        if(ay0 > ay1) {
            ay0 = ay1;
            al = -al;
        }

        int by0 = b[i];
        int by1 = b[i+1];

        int bl = by1-by0;

        if(bl >= 0) bl++;
        else bl--;

        if(by0 > by1) {
            by0 = by1;
            bl = -bl;
        }


        if(by0 < ay0) {
            swap(ay0, by0);
            swap(ay1, by1);
            swap(al, bl);
            swap(c_a, c_b);
        }

        int d0 = by0 - ay0;

        fillVLine(c_a, i, ay0, min(al, d0));

        if(by0 <= ay0 + al) {
            int d1 = (ay0 + al) - by0;
            fillVLine(color_c, i, by0, min(bl, d1));
            if(ay0 + al >= by0 + bl) {
                int d2 = (ay0 + al) - (by0 + bl);
                fillVLine(c_a, i, by0 + bl, d2);
            }
            else {
                int d2 = (by0 + bl) - (ay0 + al);
                fillVLine(c_b, i, ay0 + al, d2);
            }
        }
        else {
            fillVLine(c_b, i, by0, bl);
        }
    }
}

void plotGraph(double* a, int size, char c) {
    for(int i = 0; i < size - 1; i++) {
        double ay0 = a[i];
        double ay1 = a[i+1];

        double al = ay1-ay0;

        if(al >= 0) al++;
        else al--;

        if(ay0 > ay1) {
            ay0 = ay1;
            al = -al;
        }

        fillVLine(c, i, ay0, al);
    }
}

void initBuffer() {
    memset(buffer, ' ', (WIDTH+1)*HEIGHT);
    for(int i = 0; i < HEIGHT; i++) {
        setPixel('\n', WIDTH, i);
    }
    //null char
    buffer[HEIGHT*(WIDTH+1)] = 0;
}

void displayBuffer() {
    cout << buffer << endl;
}

int main() {
    double t = 0.0;
    while(true) {
        clear();
        createGraphs(t);
        rescale(a0, WIDTH);
        rescale(a1, WIDTH);
        initBuffer();
        plotGraph2(a0, a1, WIDTH, '-', '_', '=');
        t += 0.001;
        displayBuffer();
    }
    return 0;
}
