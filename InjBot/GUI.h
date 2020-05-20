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

class ContextMenuItem{
public: 
    const char* Text;
    int EventID;
    const char* Shortcut;

    ContextMenuItem(const char* txt, int eventid, const char* shortcut);
};


void add_print(std::string msg, int X, int Y, int R, int G, int B, int FONT);
void add_context_item(std::string txt, int eventid, std::string shortcut);

int clear_prints();

void print_context();
void print_text();
void ContextHandler();

volatile void ContextHandlerSaveRegisters();