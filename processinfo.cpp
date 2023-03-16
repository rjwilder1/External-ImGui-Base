#include "processinfo.h"
#include <Windows.h>

DWORD pid = NULL;
uintptr_t moduleaddress = NULL;
HANDLE handle = NULL;
const char* processname = "ac_client.exe";
bool ShowMenu = true;

uintptr_t LocalPlayer = NULL;

bool UnlimitedAmmo = false;
bool Sink = false;
