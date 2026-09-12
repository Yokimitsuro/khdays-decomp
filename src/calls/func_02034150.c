typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct {
    int   pBuf0;
    int   pBuf1;
    int   nUnk8;
    short nUnkC;
    short nRefCount;
    int   nUnk10;
} ResEntry;

extern ResEntry *data_0204c238;
extern char data_02042a04[];
extern char data_02042a10[];

extern void  func_020343ec(void);
extern int   func_020342b4(int id);
extern int   func_02034258(int id);
extern void *func_02024ee8(const char *name, int mode);
extern void *func_0201ef9c(u32 addr, int mode);
extern int   func_02024fd4(void *p);

int func_02034150(int id, int mode)
{
    int packIndex;
    ResEntry *entry;
    void *h;
    void *h2;
    u32 flags;

    packIndex = id;
    if ((unsigned int)id > 0x15) packIndex = id - 1;
    if (mode > 0x10 || id >= 0x21) return 0;

    if (data_0204c238 == 0) func_020343ec();

    entry = &data_0204c238[id];
    entry->nRefCount = entry->nRefCount + 1;

    if (func_020342b4(id) != 0) return 1;

    func_02034258(id);

    entry->nUnk10 = mode;
    h = func_02024ee8(data_02042a04, mode);

    flags = (0x80000000 | ((((u32)h + 0x8000) & 0xfffffc) << 7)) | (0x1ff & packIndex);
    h2 = func_0201ef9c(flags, mode);

    func_02024fd4(h);

    if (h2 != 0) {
        entry->pBuf0 = (int)h2;
        entry->nUnkC = *(u32 *)h2;
        entry->nUnk8 = (int)((char *)h2 + 4);
    } else {
        func_02034258(id);
        return 0;
    }

    if (id <= 0x18) {
        h = func_02024ee8(data_02042a10, mode);
        if (id == 0x18) packIndex = packIndex - 1;

        flags = (0x80000000 | ((((u32)h + 0x8000) & 0xfffffc) << 7)) | (0x1ff & packIndex);
        h2 = func_0201ef9c(flags, mode);

        func_02024fd4(h);

        if (h2 != 0) {
            entry->pBuf1 = (int)h2;
        } else {
            func_02034258(id);
            return 0;
        }
    }
    return 1;
}
