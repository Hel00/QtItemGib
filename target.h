#ifndef TARGET_H
#define TARGET_H

#include <Windows.h>
#include <fstream>
#include <stdint.h>
#include <array>

//#define itemGibA(mapItemManager, itemDurability, itemDescription) ((inaat (*)())0xdeadbeef)(mapItemManager, itemDurability, itemDescription)

int (__fastcall *itemGib)(int64_t, int[], int[]) = (int (*)(int64_t, int[], int[]))0x144752300;

int64_t getOffset(HANDLE handle, int64_t base, int64_t address[])
{
    int64_t addrs;

    ReadProcessMemory(handle, LPCVOID(base), &addrs, 8, 0);
    for (int i = 0; i < sizeof(address); i++)
    {
        ReadProcessMemory(handle, LPCVOID(addrs + address[i]), &addrs, sizeof(addrs), 0);
    }

    return addrs;
}

#endif // TARGET_H

/*
import winim

proc getOffset*(processHandle: HANDLE, offsets: seq[int64]): int64 =
  var
    value: int64
  for i in 0 .. offsets.len - 1:
    discard ReadProcessMemory(processHandle, cast[LPVOID](value + offsets[i]), LPVOID(addr(value)), SIZE_T(sizeof(value)), nil)
  return value

type
    ItemGibProc* = proc(mapItemManager: int64, itemDurability: array[4, int32], ItemDescription: array[4, int32]) {.fastcall.}

let
    processHandle: HANDLE = GetCurrentProcess()
    mapItemMan* = getOffset(processHandle, @[cast[int64](0x144752300)])
    itemGib* = cast[ItemGibProc](0x1407BBA70)
*/
