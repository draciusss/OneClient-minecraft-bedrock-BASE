#pragma region MyRegion

// dllmain.cpp : Defines the entry point for the DLL application.
bool isRunning = true; // isRunning bool for ejection/detachment
//Includes
#pragma region Includes & Macros

// C++ Includes
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <filesystem>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

// Module List
class Module;
std::vector<Module*> modules = std::vector<Module*>();
std::vector<std::string> categories;

// DirectX

// minhook
#include "Libs/minhook/Minhook.h"

// ImGui & Kiero
#include "Libs/kiero/kiero.h"
#include "Libs/imgui/imgui.h"
#include "Libs/imgui/impl/imgui_impl_win32.h"
#include "Libs/imgui/impl/imgui_impl_dx11.h"
#include "Libs/imgui/impl/imgui_impl_dx12.h"

// Maths
#include "Client/Utils/Math/Math.h"
#include "Client/Utils/Math/TextFormat.h"
#include "Client/Utils/Math/TextHolder.h"
#include "Client/Utils/Math/UIColor.h"
#include "Client/Utils/Math/Vector2.h"
#include "Client/Utils/Math/Vector3.h"
#include "Client/Utils/Math/Vector4.h"

// Utils
#include "Client/Utils/Utils.h"

// SDK
//#include "Base/SDK/Classes/Core/ClientInstance.h"

// Render Utils

// Globals
#include "Base/Globals/Global.h"

// Event

// Module

// Hooks
#include "Base/Hooks/FuncHook.h"
//#include "Base/DirectX/DirectXHook.h"

// ModuleAssistant

#pragma endregion

void InitializeClient() {
  //Utils::InitializeClientFolders(); // This is used to initialize clients folders.
  //InitializeMods(); // This is used to initialize modules & sort categories.
    //DirectXHook::Initialize(); // This is used to initialize dx11 & dx12 hooks
    InitializeHooks(); // This is used to initialize hooks to the proccess.
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded
        DisableThreadLibraryCalls(hModule);

        // Create a new thread to initialize the client on.
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitializeClient, hModule, 0, nullptr);

        // Create a new thread for ejection.
   //     CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ejectThread, hModule, 0, 0);   //use soon!#1
    }
    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        // Here is where to write code for when a dll detach.
        // We have that writen on ejectThread so no worries.
    }
    return TRUE;
}