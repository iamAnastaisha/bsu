#include<iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <iomanip>
#include<winbase.h>

LPCSTR kill_path = "D:\\Ћаб рабы\\ќси\\Killer\\Debug\\Killer.exe";

void printProcesses() {
  std::cout << "///////////////////////////////////\n";
  PROCESSENTRY32 pe = {0};
  pe.dwSize = sizeof(PROCESSENTRY32);
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  Process32First(hSnap, &pe);
  std::cout << std::setw(10) << std::left << "ID" << std::left
            << "PROCESS_NAME\n";
  do {
    std::wcout << std::setw(10) << pe.th32ProcessID << std::left << pe.szExeFile
               << '\n';
  } while (Process32Next(hSnap, &pe));

  CloseHandle(hSnap);
  std::cout << "///////////////////////////////////\n";
}

void kill(std::string str) {
  std::string str_ = str;
  char* proc = (char*)str.c_str();
  STARTUPINFOA si = {0};
  PROCESS_INFORMATION pi = {0};
  if (CreateProcessA(kill_path, proc, NULL, NULL, FALSE, 0, NULL, NULL, &si,
                     &pi)) {
    WaitForSingleObject(pi.hProcess, INFINITE);
  }
}

  int main() {
  printProcesses();
  SetEnvironmentVariableA("PROC_TO_KILL", "Telegram,firefox,Totalcmd");
  kill("");
  _putenv("PROC_TO_KILL");
  std::string command;
  std::cout << "\nYou may:\nprint\nkill\nexit\n\n";
  std::cin >> command;
  while (command != "exit") {
    if (command == "print")
      printProcesses();
    else if (command == "kill") {
      std::string command_str;
      std::cin >> command_str;
      kill(command_str);
    } else
      std::cout << "!WRONG COMMAND!\n";
    std::cout << "\nYou may:\nprint\nkill\nexit\n\n";
    std::cin >> command;
  }
  return 0;
}