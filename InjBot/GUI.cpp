#include <windows.h>
#include "GUI.h"
#include "Addresses.h"


#pragma region Prints
intptr_t PrintTextFunctionAddy = 0x122A90;

Print::Print(const char* TXT, int X, int Y, int R, int G, int B, int FONT) :
    Text(TXT), x(X), y(Y), r(R), g(G), b(B), font(FONT)
{
};

std::vector<Print*> prints = std::vector<Print*>();

void add_text(const char* text, int x, int y, int RGB_r, int RGB_g, int RGB_b, int font) {
    intptr_t funcAdr = Client::BaseAddress + 0xB4DD0;

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
    intptr_t FillerAdr = Client::BaseAddress + PrintTextFunctionAddy;
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

#pragma region ContextMenus
intptr_t ContextMenuCreateAddy = Client::BaseAddress + 0x52320;
std::vector<ContextMenuItem*> ContextMenuItems = std::vector<ContextMenuItem*>();

bool CustomMenu;

ContextMenuItem::ContextMenuItem(const char* txt, int eventid, const char* shortcut) :
    Text(txt), EventID(eventid), Shortcut(shortcut)
{
};

void CreateContextMenuItem(const char* ShortCut, const char* txt, int EventID)
{

    __asm {
        push ShortCut
        push txt
        push EventID
        mov ecx, esi
        call ContextMenuCreateAddy

    }
}

void print_context()
{
    intptr_t FillerAdr = Client::BaseAddress + HookAddress::HookContextFiller;

    __asm {
        MOV BYTE PTR DS : [ESI + 0x30] , 1 
    }
    for (ContextMenuItem* CMI : ContextMenuItems)
    {
        CreateContextMenuItem(CMI->Shortcut, CMI->Text, CMI->EventID);
    }
    __asm {
        CALL FillerAdr
    }
}

void add_context_item(std::string txt, int eventid, std::string shortcut)
{
    char* ca = new char[txt.size() + 1];
    std::copy(txt.begin(), txt.end(), ca);
    ca[txt.size()] = '\0';

    char* c1 = new char[shortcut.size() + 1];
    std::copy(shortcut.begin(), shortcut.end(), c1);
    c1[shortcut.size()] = '\0';

    ContextMenuItem* cmi = new ContextMenuItem(ca, eventid, c1);
    ContextMenuItems.push_back(cmi);
}

volatile void __declspec(naked) ContextHandlerSaveRegisters()
{
    __asm {
        PUSHFD
        PUSHAD
    }
    ContextHandler();
    if (!CustomMenu)
    {
        __asm {
            POPAD
            POPFD
            push ECX
            MOV ECX, EAX
            CALL DWORD PTR DS : [EDX + 0x70]
        }
    }
    else
    {
        __asm {
            POPAD
            POPFD
        }
    }
    __asm {
        ret
    }
}


void ContextHandler()
{
    CustomMenu = false;
    uint32_t pEventID = 0x1337;
    int EventID = 0;
    __asm {
        mov pEventID, EBP
    }
    EventID = *(int*)(pEventID + 0x30);
        switch (EventID) 
        {
        case 0x4000:
            add_print("Clicked First BOX :D", 40, 700, 155, 155, 255, 4);
            CustomMenu = true;
            break;
        case 0x4001:
            add_print("Clicked SECOND BOX :D", 40, 500, 155, 155, 255, 4);
            CustomMenu = true;
            break; 
        case 0x4002:

            break;
              default:
            break;
        }

    }



#pragma endregion ContextMenus


#pragma region CheckBoxes



void create_check_box(std::string text, bool Checked){
    int check = 0;
    if (Checked) check = 1;
    char* txt = (char*)":POG:";
    uint32_t createCheckBoxAdr = 0x47CFF0;
    uint32_t pMenu = 0x27AC960;
    __asm {
        push 50
        push 50
        push txt
        mov ecx, pMenu // pointer to gui object the checkbox should be created within.
        call createCheckBoxAdr
    }

}

#pragma endregion CheckBoxes

#pragma region OptionButtons
uint32_t edxV = 0;
void CreateButton() {
          std::string Text = "EBBot";
          int spriteid = 13;
          int sprite_id_pressed = 12;
        char* ca = new char[Text.size() + 1];
        std::copy(Text.begin(), Text.end(), ca);
        ca[Text.size()] = '\0';
        uint32_t functionadr = 0x47C650;
    __asm {

        push 0
        push 196
        push edxV
        push spriteid
        push sprite_id_pressed
        push ca
        push 0
        push 0
        CALL functionadr
    }
}
uint32_t jmpback = 0x491610;
volatile void __declspec(naked) hook_create_check_box() {
    __asm {
        mov edxV, edx
        pushfd
        pushad

    }
    CreateButton();
    __asm {
        popad
        popfd
        PUSH 0x4C
        call HookAddress::HookOptionsButtonCreate
       jmp jmpback
    }

}
#pragma endregion OptionButtons