#pragma once
#include <windows.h>

class Client {
public:
	static intptr_t BaseAddress;
};

class HookAddress {
public:
	static intptr_t HookPrintAddy;
};

class Status {
public:
	static intptr_t OnlinePointer;
};

class Self {
public:
	static intptr_t LocalPlayer;
};

class Control {
public:
	static intptr_t RedSquare;
};