#include "Addresses.h"

#pragma region Client
intptr_t Client::BaseAddress = (intptr_t)GetModuleHandle(NULL);
#pragma endregion Client

#pragma region Hooks
intptr_t HookAddress::HookPrintAddy = 0x5A34A;
intptr_t HookAddress::HookContextAdd = Client::BaseAddress + 0x53288; 
intptr_t HookAddress::HookContextMenuSwitch = Client::BaseAddress + 0xC5BD7; 

intptr_t HookAddress::HookOptionsButtonCreate = Client::BaseAddress + 0x1719E2;

intptr_t HookAddress::HookContextFiller = 0x5FC80;

#pragma endregion Hooks

#pragma region Status
intptr_t Status::OnlinePointer = 0x29459E0;
#pragma endregion Status

#pragma region Self
intptr_t Self::LocalPlayer = 0x23FE40;
#pragma endregion Self

#pragma region Controls
intptr_t Control::RedSquare = 0x23FE64;
intptr_t Control::ContextMenuSwitch = Client::BaseAddress + 0x4E960;
#pragma endregion Controls