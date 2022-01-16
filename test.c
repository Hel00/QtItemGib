// COMPILE THIS SEPARATELY, NOT WITH CMAKE
// clang++ -O3 -shared test.c -o target.dll

#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <fstream>
#include <stdint.h>
#include <array>

#pragma comment(lib, "user32.lib")

#define BUF_SIZE 256
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");

BOOL WINAPI DllMain(HINSTANCE hinstDLL, // handle to DLL module
                    DWORD fdwReason,    // reason for calling function
                    LPVOID lpReserved)  // reserved
{
  // Perform actions based on the reason for calling.
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, // read/write access
                               FALSE,               // do not inherit the name
                               szName);             // name of mapping object

    if (hMapFile == NULL) {
      _tprintf(TEXT("Could not open file mapping object (%d).\n"),
               GetLastError());
      return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile,            // handle to map object
                                 FILE_MAP_ALL_ACCESS, // read/write permission
                                 0, 0, BUF_SIZE);

    if (pBuf == NULL) {
      _tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());

      CloseHandle(hMapFile);

      return 1;
    }

    MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
    printf("%s", pBuf);

    std::ofstream myfile;
    myfile.open("C:\\Users\\hel\\Documents\\Qt\\example.txt",
                std::fstream::out);
    myfile << pBuf << '\n';
    myfile.close();

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
    getch();
    return 0;
    break;
  }
  return TRUE; // Successful DLL_PROCESS_ATTACH.
}
