// memory.cpp
#include "memory.h"
#include <TlHelp32.h>
#include <iostream>

bool Memory::OpenProcess(const char* processName) {
    processId = GetProcessId(processName);
    if (processId == 0) {
        return false;
    }

    processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    return processHandle != NULL;
}

HANDLE Memory::GetProcessHandle() const {
    return processHandle;
}

DWORD Memory::GetProcessId(const char* processName) {
    std::cout << "Attempting to get process ID of: " << processName << std::endl;
    DWORD processId = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnapshot, &processEntry)) {
            do {
                if (_stricmp(processEntry.szExeFile, processName) == 0) {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &processEntry));
        }
        CloseHandle(hSnapshot);
    }
    std::cout << "Got process ID: " << processId << std::endl;
    return processId;
}

template<typename T>
bool Memory::Write(SIZE_T address, T val) {
    return WriteProcessMemory(processHandle, (LPVOID)address, (LPCVOID)&val, sizeof(T), NULL);
}

uintptr_t Memory::GetBaseAddress(DWORD Pid, const char* processName) {
    std::cout << "Attempting to get Base Address of: " << processName << "(" << Pid << ")" << std::endl;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Pid);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, processName)) {
                    CloseHandle(hSnap);
                    std::cout << "Got base address: 0x" << std::hex << (uintptr_t)modEntry.modBaseAddr << std::endl;
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    return 0;
}
