#include <iostream>
#include <cstdio>
#include "shobjidl_core.h"

void change(int monitorIndex, const std::wstring& wallpaper) {
    CoInitialize(nullptr);

    LPWSTR monitorID = nullptr;

    IDesktopWallpaper* p;
    if(SUCCEEDED(CoCreateInstance(__uuidof(DesktopWallpaper), nullptr, CLSCTX_LOCAL_SERVER, __uuidof(IDesktopWallpaper), (void**)&p))) {
        p->GetMonitorDevicePathAt(monitorIndex, &monitorID);
        p->SetWallpaper(monitorID, wallpaper.c_str());
        p->Release();
    }

    CoUninitialize();
}

int main (){
    std::wstring wallpaper1 = L"D:\\wallpaper\\wallpaper1.jpg";
    std::wstring wallpaper2 = L"D:\\wallpaper\\wallpaper2.jpg";
    std::wstring currentWallpaper = wallpaper2;

    printf("start register hotkey\n");
    if (RegisterHotKey(nullptr,1,MOD_ALT | MOD_WIN | MOD_NOREPEAT,0x43)) {
        printf("register hotkey success\n");
    } else {
        printf("register hotkey error\n");
        return 1;
    }

    MSG msg = {nullptr};
    while (GetMessage(&msg, nullptr, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            currentWallpaper = currentWallpaper == wallpaper2 ? wallpaper1 : wallpaper2;
            printf("change wallpaper %ws\n", currentWallpaper.c_str());
            change(1, currentWallpaper);
        }
    }

    return 0;
}
