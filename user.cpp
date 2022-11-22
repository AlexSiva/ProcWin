#include <windows.h>
#include <tlhelp32.h>
#include <winbase.h>
#include <iostream>
#include <string>
#include <vector>

int main() {
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, 18564);
  char szHANDLE[100];
  sprintf_s(szHANDLE, "%d", hProcess);
  SetEnvironmentVariableA("PROC_TO_KILL", szHANDLE);
  std::string str = "--name Telegram.exe";
  char *input = (char *)str.c_str();
  STARTUPINFOA si = {sizeof(si)};
  PROCESS_INFORMATION piProcess;
  if (CreateProcessA("D:/programming/killer/build/Debug/killer.exe", input,
                    nullptr, nullptr, FALSE, 0, NULL, NULL, &si,
                    &piProcess)) {
    WaitForSingleObject(piProcess.hProcess, INFINITE);
    CloseHandle(piProcess.hThread);
    CloseHandle(piProcess.hProcess);
  }
  SetEnvironmentVariableA("PROC_TO_KILL", nullptr);
}
