#include "target.h"

typedef void (__fastcall *helTest)(long long a, int b[], int c[]);

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved )
{
    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:

            HANDLE processHandle = GetCurrentProcess();

            /*int64_t base=0x144752300;
            int64_t offsets[] = {0};
            int64_t mapItemManVal = getOffset(processHandle, base, offsets);

            std::ofstream myfile;
            myfile.open ("C:\\Users\\hel\\Documents\\Qt\\example.txt", std::fstream::out);
            myfile << mapItemManVal << '\n';
            myfile.close();*/


            int64_t mapItemManVal = 2855691744;
            int itemDurability[]  = {1, 0x00A87500, 1, static_cast<int>(0xFFFFFFFF)};
            int itemDescription[] = {0, 0, 0, 0};

            (helTest)(140688804439520, itemDurability, itemDescription);

            break;
    }
    return TRUE;
}

/*
button.label = itemId
dksUtils.itemGib(
  cast[int64](mapItemMan),
  [1.int32, fromHex[int32](itemId), 1, cast[int32](0xFFFFFFFF)],
  [0.int32, 0, 0, 0]
  )
*/
