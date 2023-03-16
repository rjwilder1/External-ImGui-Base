#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <tchar.h>
#include <utility>
#include <iostream>
#include <Psapi.h>
#include <dwmapi.h>
#include <tlhelp32.h>

#include "offsets.h"
#include "Overlay.h"
#include "memory.h"
#include "processinfo.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")