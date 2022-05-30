#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

#define BUFSIZE 4096

int main() {
  CHAR chBuf[BUFSIZE];
  DWORD dwRead, dwWritten;
  HANDLE hStdin, hStdout;

  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  if ((hStdout == INVALID_HANDLE_VALUE) || (hStdin == INVALID_HANDLE_VALUE))
    ExitProcess(1);

  printf("\n ** This is a message from the child process P. ** \n");
  for (;;) {
    if (!ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL) || dwRead == 0) break;
    std::string input(chBuf), output;
    while (!input.empty()) {
      auto end = find(input.begin(), input.end(), ' ');
      std::string tmp = input.substr(0, end - input.begin());
      if (end == input.end()) break;
      end++;
      input.erase(input.begin(), end);
      int num = std::stoi(tmp, nullptr, 30);
      output.append(std::to_string(num * num * num) + " ");
    }
    if (!WriteFile(hStdout, output.c_str(), dwRead, &dwWritten, NULL)) break;
  }
  system("pause");
  return 0;
}