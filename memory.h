#pragma once
#include <Windows.h>

class Memory {
public:
    bool OpenProcess(const char* processName); // Function to open the process by its name
    DWORD GetProcessId(const char* processName); // As before
    uintptr_t GetBaseAddress(DWORD Pid, const char* processName);
    HANDLE GetProcessHandle() const;
    //std::string RandomString(int len);



    template<typename T>
    bool Write(SIZE_T address, T val);

private:
    DWORD processId;
    HANDLE processHandle;
};



