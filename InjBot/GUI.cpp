#include "pch.h"
#include <vector>
#include "GUI.h"
#include <string>

intptr_t PrintTextFunctionAddy = 0x122A90;

intptr_t BaseAdr = (intptr_t)GetModuleHandle(NULL);

#pragma region Prints

Print::Print(const char* TXT, int X, int Y, int R, int G, int B, int FONT)
    {
        this->Text = TXT;
        this->x = X;
        this->y = Y;
        this->r = R;
        this->g = G;
        this->b = B;
        this->font = FONT;
    }

std::vector<Print*> prints = std::vector<Print*>();


void add_text(const char* text, int x, int y, int RGB_r, int RGB_g, int RGB_b, int font) {
    intptr_t funcAdr = BaseAdr + 0xB4DD0;

    __asm {
        MOV EDX, text
        PUSH 0
        PUSH text
        push RGB_b
        push RGB_g
        push RGB_r
        push font
        push y
        push x
        push 1
        call funcAdr
        add esp, 0x24;
    }
}


void print_text()
{
    intptr_t FillerAdr = BaseAdr + PrintTextFunctionAddy;
    if (prints.size() > 0)
    {
        for (Print* print : prints)
        {
            add_text(print->Text, print->x, print->y, print->r, print->g, print->b, print->font);
        }
    }
    __asm {
        CALL FillerAdr
    }
}


void add_print(std::string msg, int X, int Y, int R, int G, int B, int FONT)
{

    char* ca = new char[msg.size() + 1];
    std::copy(msg.begin(), msg.end(), ca);
    ca[msg.size()] = '\0';

    Print* p = new Print(ca, X, Y, R, G, B, FONT);
    prints.push_back(p);
}

int clear_prints()
{
    int amount = prints.size();
    prints.clear();

    return amount;
    prints.shrink_to_fit();

}

#pragma endregion Prints

void send_green_text(std::string msg)
{
    //int length = msg.length();
   // const char* txt1 = msg.c_str();
    char* txt = (char*)"Cops Outside";
    uint32_t adr = BaseAdr + 0x14AF50;

    __asm {
        MOV ESI, 15
        PUSH txt
        PUSH 15
        CALL adr
        ADD ESP, 0x8
    }

}
