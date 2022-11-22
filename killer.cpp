#include <windows.h>
#include <Tlhelp32.h>
#include <process.h>
#include <winbase.h>
#include <cstring>
#include <iostream>
#include <string>

void killID(int id) {
  HANDLE proc = OpenProcess(PROCESS_TERMINATE, FALSE, id);
  if (proc != nullptr) {
    TerminateProcess(proc, 0);
    CloseHandle(proc);
  }
}

bool weirdEquals(const std::wstring& str, const char* c) {
  std::string c_str(c);
  if (str.size() < c_str.size()) {
    return false;
  }
  return std::equal(c_str.begin(), c_str.end(), str.begin());
}

void killName(const char* name) {
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
  PROCESSENTRY32 processEntry;
  processEntry.dwSize = sizeof(processEntry);
  BOOL check = Process32First(snapshot, &processEntry);
  while (check) {
    if (weirdEquals(processEntry.szExeFile, name)) {
      HANDLE proc = OpenProcess(PROCESS_TERMINATE, 0, processEntry.th32ProcessID);
      if (proc != nullptr) {
        TerminateProcess(proc, 0);
        CloseHandle(proc);
      }
    }
    check = Process32Next(snapshot, &processEntry);
  }
  CloseHandle(snapshot);
}

 int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--name") == 0) {
      killName(argv[i + 1]);
    } else if (strcmp(argv[i], "--id") == 0) {
      killID(std::atoi(argv[i + 1]));
    }
  }
  return 0;
} 