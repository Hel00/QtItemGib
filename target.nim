import winim
import dksUtils

const bufSize = 256

var
    smName = "Global\\MyFileMappingObject"
    mapFileHandle: HANDLE
    pBuf: LPCSTR

mapFileHandle = OpenFileMapping(
    FILE_MAP_ALL_ACCESS,
    FALSE,
    smName
)

if mapFileHandle.int == 0:
    echo "Could not create file mapping object: ", GetLastError()

pBuf = cast[cstring](
    MapViewOfFile(
        mapFileHandle,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        bufSize
    )
)

if pBuf == NULL:
    echo "Could not map view of file: ", GetLastError()
    CloseHandle(mapFileHandle)

echo pBuf
MessageBox(0, cast[LPCWSTR](pBuf), "Process2", MB_OK);

var itemId = 0x00A87500

dksUtils.itemGib(
  cast[int64](mapItemMan),
  [1.int32, int32(itemId), 1, cast[int32](0xFFFFFFFF)],
  [0.int32, 0, 0, 0]
  )

UnmapViewOfFile(pBuf)
CloseHandle(mapFileHandle)
