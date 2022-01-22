#include <Windows.h>

#include <stdio.h>

#include "fileop.h"
#include "wchar_util.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    wchar_t tmp[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, tmp, MAX_PATH)) {
        return 1;
    }
    std::string current_exe;
    if (!wchar_util::wstr_to_str(current_exe, tmp, CP_UTF8)) {
        return 1;
    }
    printf("%s\n", current_exe.c_str());
    std::string base_path = fileop::dirname(fileop::dirname(current_exe));
    std::string result = fileop::join(base_path, R"(ProjectX\Mirror2\Binaries\Win64\Mirror2_X-Win64-Shipping.exe)");
    if (fileop::exists(result)) {
        std::string basedir = fileop::dirname(result);
        std::wstring tmp, tmp2;
        if (!wchar_util::str_to_wstr(tmp, result, CP_UTF8) || !wchar_util::str_to_wstr(tmp2, basedir, CP_UTF8)) {
            return 1;
        }
        STARTUPINFOW si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        if (CreateProcessW(tmp.c_str(), nullptr, nullptr, nullptr, FALSE, 0, nullptr, tmp2.c_str(), &si, &pi)) {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            fprintf(stderr, "CreateProcess failed (%d).", GetLastError());
            return 1;
        }
    }
    return 0;
}
