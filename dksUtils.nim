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
