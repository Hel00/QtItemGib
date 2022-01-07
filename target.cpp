#include "target.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved )
{
    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:
            std::ofstream myfile;
            myfile.open ("C:\\Users\\hel\\Documents\\Qt\\example.txt", std::fstream::out);
            myfile << "Writing this to a file.\n";
            myfile.close();
            break;
    }
    return TRUE;
}
