#pragma once
#include <vector>
#include <string>

class Print {

public:
    const char* Text;
    int x;
    int y;
    int r;
    int g;
    int b;
    int font;

    Print(const char* TXT, int X, int Y, int R, int G, int B, int FONT);
};

void add_print(std::string msg, int X, int Y, int R, int G, int B, int FONT);

int clear_prints();

void print_text();


