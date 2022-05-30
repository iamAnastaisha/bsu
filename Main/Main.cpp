#include <stdio.h>
#include <windows.h>

#include <string>
#define BUFSIZE 4096

LPCSTR procP = "D:\\Ћаб рабы\\ќси\\ProcP\\Debug\\ProcP.exe";
LPCSTR procM = "D:\\Ћаб рабы\\ќси\\ProcM\\Debug\\ProcM.exe";
LPCSTR procA = "D:\\Ћаб рабы\\ќси\\ProcA\\Debug\\ProcA.exe";
LPCSTR procS = "D:\\Ћаб рабы\\ќси\\ProcS\\Debug\\ProcS.exe";

HANDLE g_hChildStd_IN_Rd1 = NULL;
HANDLE g_hChildStd_IN_Wr1 = NULL;
HANDLE g_hChildStd_OUT_Rd1 = NULL;
HANDLE g_hChildStd_OUT_Wr1 = NULL;

HANDLE g_hChildStd_IN_Rd2 = NULL;
HANDLE g_hChildStd_IN_Wr2 = NULL;
HANDLE g_hChildStd_OUT_Rd2 = NULL;
HANDLE g_hChildStd_OUT_Wr2 = NULL;

HANDLE g_hChildStd_IN_Rd3 = NULL;
HANDLE g_hChildStd_IN_Wr3 = NULL;
HANDLE g_hChildStd_OUT_Rd3 = NULL;
HANDLE g_hChildStd_OUT_Wr3 = NULL;

HANDLE g_hChildStd_IN_Rd4 = NULL;
HANDLE g_hChildStd_IN_Wr4 = NULL;
HANDLE g_hChildStd_OUT_Rd4 = NULL;
HANDLE g_hChildStd_OUT_Wr4 = NULL;

HANDLE g_hInputFile = NULL, pipe1 = NULL, pipe2 = NULL, pipe3 = NULL,
       pipe4 = NULL;

void CreateChildProcess(LPCSTR, HANDLE, HANDLE);
void WriteToPipe(HANDLE);
void FromPipeToPipe(HANDLE, HANDLE);
void ReadFromPipe(HANDLE);

int main() {
  SECURITY_ATTRIBUTES saAttr1, saAttr2, saAttr3, saAttr4;

  printf("\n->Start of parent execution.\n");

  saAttr1.nLength = saAttr2.nLength = saAttr3.nLength = saAttr4.nLength =
      sizeof(SECURITY_ATTRIBUTES);
  saAttr1.bInheritHandle = saAttr2.bInheritHandle = saAttr3.bInheritHandle =
      saAttr4.bInheritHandle = TRUE;
  saAttr1.lpSecurityDescriptor = saAttr2.lpSecurityDescriptor =
      saAttr3.lpSecurityDescriptor = saAttr4.lpSecurityDescriptor = NULL;

  if (!CreatePipe(&g_hChildStd_OUT_Rd1, &g_hChildStd_OUT_Wr1, &saAttr1, 0))
    printf("StdoutRd CreatePipe");
  if (!SetHandleInformation(g_hChildStd_OUT_Rd1, HANDLE_FLAG_INHERIT, 0))
    printf("Stdout SetHandleInformation");
  if (!CreatePipe(&g_hChildStd_IN_Rd1, &g_hChildStd_IN_Wr1, &saAttr1, 0))
    printf("Stdin CreatePipe");
  if (!SetHandleInformation(g_hChildStd_IN_Wr1, HANDLE_FLAG_INHERIT, 0))
    printf("Stdin SetHandleInformation");
  g_hInputFile =
      CreateFileA("in.txt", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  pipe1 = CreateFileA("\\\\.\\pipe\\$Pipe1$", PIPE_ACCESS_INBOUND,
                      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL, NULL);
  pipe2 = CreateFileA("\\\\.\\pipe\\$Pipe2$", PIPE_ACCESS_INBOUND,
                      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL, NULL);
  pipe3 = CreateFileA("\\\\.\\pipe\\$Pipe3$", PIPE_ACCESS_INBOUND,
                      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL, NULL);
  pipe4 = CreateFileA("\\\\.\\pipe\\$Pipe4$", PIPE_ACCESS_INBOUND,
                      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL, NULL);

  if (g_hInputFile == INVALID_HANDLE_VALUE) printf("CreateFile");

  CreateChildProcess(procP, g_hChildStd_OUT_Wr1, g_hChildStd_IN_Rd1);

  WriteToPipe(g_hChildStd_IN_Wr1);

  ReadFromPipe(g_hChildStd_OUT_Rd1);

  if (!CreatePipe(&g_hChildStd_OUT_Rd2, &g_hChildStd_OUT_Wr2, &saAttr2, 0))
    printf("StdoutRd CreatePipe");
  if (!SetHandleInformation(g_hChildStd_OUT_Rd2, HANDLE_FLAG_INHERIT, 0))
    printf("Stdout SetHandleInformation");
  if (!CreatePipe(&g_hChildStd_IN_Rd2, &g_hChildStd_IN_Wr2, &saAttr2, 0))
    printf("Stdin CreatePipe");
  if (!SetHandleInformation(g_hChildStd_IN_Wr2, HANDLE_FLAG_INHERIT, 0))
    printf("Stdin SetHandleInformation");

  CreateChildProcess(procM, g_hChildStd_OUT_Wr2, g_hChildStd_IN_Rd2);

  FromPipeToPipe(g_hChildStd_OUT_Rd1, g_hChildStd_IN_Wr2);

  ReadFromPipe(g_hChildStd_OUT_Rd2);

  if (!CreatePipe(&g_hChildStd_OUT_Rd3, &g_hChildStd_OUT_Wr3, &saAttr3, 0))
    printf("StdoutRd CreatePipe");
  if (!SetHandleInformation(g_hChildStd_OUT_Rd3, HANDLE_FLAG_INHERIT, 0))
    printf("Stdout SetHandleInformation");
  if (!CreatePipe(&g_hChildStd_IN_Rd3, &g_hChildStd_IN_Wr3, &saAttr3, 0))
    printf("Stdin CreatePipe");
  if (!SetHandleInformation(g_hChildStd_IN_Wr3, HANDLE_FLAG_INHERIT, 0))
    printf("Stdin SetHandleInformation");

  CreateChildProcess(procA, g_hChildStd_OUT_Wr3, g_hChildStd_IN_Rd3);

  FromPipeToPipe(g_hChildStd_OUT_Rd2, g_hChildStd_IN_Wr3);

  ReadFromPipe(g_hChildStd_OUT_Rd3);

  if (!CreatePipe(&g_hChildStd_OUT_Rd4, &g_hChildStd_OUT_Wr4, &saAttr4, 0))
    printf("StdoutRd CreatePipe");
  if (!SetHandleInformation(g_hChildStd_OUT_Rd4, HANDLE_FLAG_INHERIT, 0))
    printf("Stdout SetHandleInformation");
  if (!CreatePipe(&g_hChildStd_IN_Rd4, &g_hChildStd_IN_Wr4, &saAttr4, 0))
    printf("Stdin CreatePipe");
  if (!SetHandleInformation(g_hChildStd_IN_Wr4, HANDLE_FLAG_INHERIT, 0))
    printf("Stdin SetHandleInformation");

  CreateChildProcess(procS, g_hChildStd_OUT_Wr4, g_hChildStd_IN_Rd4);

  FromPipeToPipe(g_hChildStd_OUT_Rd3, g_hChildStd_IN_Wr4);

  printf("\n->Contents of child process STDOUT:\n\n");
  ReadFromPipe(g_hChildStd_OUT_Rd4);

  printf("\n->End of parent execution.\n");
  return 0;
}

void CreateChildProcess(LPCSTR proc_name, HANDLE g_hChildStd_OUT_Wr,
                        HANDLE g_hChildStd_IN_Rd) {
  PROCESS_INFORMATION piProcInfo;
  STARTUPINFOA siStartInfo;

  ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdError = g_hChildStd_OUT_Wr;
  siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
  siStartInfo.hStdInput = g_hChildStd_IN_Rd;
  siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

  if (!CreateProcessA(proc_name, NULL, NULL, NULL, TRUE, 0, NULL, NULL,
                      &siStartInfo, &piProcInfo))
    printf("CreateProcess");

  else {
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    CloseHandle(g_hChildStd_OUT_Wr);
    CloseHandle(g_hChildStd_IN_Rd);
  }
}

void WriteToPipe(HANDLE g_hChildStd_IN_Wr) {
  DWORD dwRead, dwWritten;
  CHAR chBuf[BUFSIZE];
  for (;;) {
    if (!ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL) || dwRead == 0)
      break;
    if (!WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL)) break;
  }
  if (!CloseHandle(g_hChildStd_IN_Wr)) printf("StdInWr CloseHandle");
}

void FromPipeToPipe(HANDLE g_hChildStd_OUT_Rd, HANDLE g_hChildStd_IN_Wr) {
  DWORD dwRead, dwWritten;
  CHAR chBuf[BUFSIZE];
  for (;;) {
    if (!ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL) ||
        dwRead == 0)
      break;
    if (!WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL)) break;
  }
  if (!CloseHandle(g_hChildStd_IN_Wr)) printf("StdInWr CloseHandle");
  if (!CloseHandle(g_hChildStd_OUT_Rd)) printf("StdIOutRd CloseHandle");
}

void ReadFromPipe(HANDLE g_hChildStd_OUT_Rd) {
  DWORD dwRead, dwWritten;
  CHAR chBuf[BUFSIZE];
  HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  for (;;) {
    if (!ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL) ||
        dwRead == 0)
      break;
    if (!WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, NULL)) break;
  }
}