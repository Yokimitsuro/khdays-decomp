/* Loads a message database (text bank) by id: counts a reference, and unless already loaded, loads
 * its text pack (and, for the lower ids, its second pack) from the packed archives into the table
 * entry; returns whether it succeeded. */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

typedef struct {
    int   pBuf0;
    int   pBuf1;
    int   nUnk8;
    short nUnkC;
    short nRefCount;
    int   nUnk10;
} ResEntry;

extern ResEntry *data_0204c238;
extern char gDbDbPath[];
extern char gDbDbPath_2[];

extern void *Msg_OpenContainerAndReadHeader(const char *name, int mode);
extern void *Archive_LoadFile(u32 addr, int mode);

int MsgDb_LoadDb(int id, int mode)
{
    int packIndex;
    ResEntry *entry;
    void *h;
    void *h2;
    u32 flags;

    packIndex = id;
    if ((unsigned int)id > 0x15) packIndex = id - 1;
    if (mode > 0x10 || id >= 0x21) return 0;

    if (data_0204c238 == 0) MsgDb_InitTable();

    entry = &data_0204c238[id];
    entry->nRefCount = entry->nRefCount + 1;

    if (MsgDb_IsLoaded(id) != 0) return 1;

    ResSlot_Release_2(id);

    entry->nUnk10 = mode;
    h = Msg_OpenContainerAndReadHeader(gDbDbPath, mode);

    flags = ARCHIVE_HANDLE(h, 0x1ff & packIndex);
    h2 = Archive_LoadFile(flags, mode);

    ZeroHalfThenFree(h);

    if (h2 != 0) {
        entry->pBuf0 = (int)h2;
        entry->nUnkC = *(u32 *)h2;
        entry->nUnk8 = (int)((char *)h2 + 4);
    } else {
        ResSlot_Release_2(id);
        return 0;
    }

    if (id <= 0x18) {
        h = Msg_OpenContainerAndReadHeader(gDbDbPath_2, mode);
        if (id == 0x18) packIndex = packIndex - 1;

        flags = ARCHIVE_HANDLE(h, 0x1ff & packIndex);
        h2 = Archive_LoadFile(flags, mode);

        ZeroHalfThenFree(h);

        if (h2 != 0) {
            entry->pBuf1 = (int)h2;
        } else {
            ResSlot_Release_2(id);
            return 0;
        }
    }
    return 1;
}
