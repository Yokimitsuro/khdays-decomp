/* MobiClip: open the movie player.
 *
 * Takes the heap's current root as the player object, publishes it, clears the
 * flag halfwords and the fade state, wipes the working block, loads the shared
 * resource and the player's BG palette into both engines, registers the entry
 * table, then opens the stream and records whether Start was already held.
 *
 * The stream id is built the same way on both paths: the sector goes into the
 * top of the word with bit 31 set, and the length shares the low bits.
 *
 * The opening is written as chained assignments (publish = player = root heap,
 * flags = state = 0): that is what schedules the publish-pointer load ahead of
 * the zero and the registry table ahead of the constant 3, as the ROM does
 * (found with decomp-permuter).
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct MobiClipPlayer {
    u16 wState;                 /* 0x0000 */
    u16 wFlags;                 /* 0x0002 */
    char aStream[0x194];        /* 0x0004 */
    char aWork[0x8400];         /* 0x0198 */
    char pad8598[0x5a4];        /* 0x8598 */
    int *pWorkEnd;              /* 0x85a4 */
    char pad85a8[0x598];
    char aResource[0xc];        /* 0x8b40 */
    char pad8b4c[0x8c];
    char pad8bd8[0];
};

struct MobiClipOpenArgs {
    int nSector;                /* 0x00 */
    int bSubScreen;             /* 0x04 */
    char szPath[1];             /* 0x08 */
};

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void func_0202f7fc(void *dst, void *src);
extern void GX_LoadBGPltt(const void *src, int offset, int size);
extern void GXS_LoadBGPltt(const void *src, int offset, int size);
extern void func_02020aa8(int slot, void *table);
extern void func_ov002_0206d834(int index, char *out);
extern int func_ov002_0206d86c(void);
extern int func_02024fe8(int sector, const char *path);
extern void func_02020c7c(void *stream, int id, void *path, void *work);
extern void func_ov024_02082f04(void);

extern void *data_ov024_02093a20[];
extern char data_ov024_02093958[];
extern u16 data_ov024_02093918[];
extern void *data_ov024_02093974[];

#define REG_KEYINPUT   ((volatile u16 *)0x04000130)
#define REG_EXTKEYIN   ((volatile u16 *)0x027fffa8)
#define KEY_MASK       0x2fff
#define SECTOR_MASK    0x00fffffc

void *func_ov024_02082a78(struct MobiClipOpenArgs *args)
{
    char szPath[0x80];
    char *player;
    int nLength;
    int nSector;
    int nId;
    char *pPath;
    u16 wHeld;

    data_ov024_02093a20[1] = player = (char *)NNSi_FndGetCurrentRootHeap();
    *(u16 *)(player + 2) = *(u16 *)player = 0;
    *(int *)(player + 0x8be8) = -1;
    *(int *)(player + 0x8bdc) = 0;
    *(int *)(player + 0x8bd8) = 0;
    *(u8 *)(player + 0x8be0) = 0;
    MI_CpuFill8(player + 0x8598, 0, 0x5a4);
    func_0202f7fc(player + 0x8b40, data_ov024_02093958);
    GX_LoadBGPltt(data_ov024_02093918, 0x1a0, 0x40);
    GXS_LoadBGPltt(data_ov024_02093918, 0x1a0, 0x40);
    *(char **)(player + 0x85a4) = player + 0x8b4c;
    func_02020aa8(3, data_ov024_02093974);

    if (args->nSector == 0) {
        func_ov002_0206d834(0, szPath);
        *(int *)(player + 0x8a24) = func_ov002_0206d86c();
        nSector = func_ov002_0206d86c();
        nLength = func_02024fe8(func_ov002_0206d86c(), szPath);
        nSector = (nSector + 0x8000) & SECTOR_MASK;
        nLength = nLength & (SECTOR_MASK >> 15);
        nId = nSector << 7 | 0x80000000 | nLength;
        pPath = args->szPath;
    } else {
        nLength = func_02024fe8(args->nSector, args->szPath);
        nSector = (args->nSector + 0x8000) & SECTOR_MASK;
        nLength = nLength & (SECTOR_MASK >> 15);
        nId = nSector << 7 | 0x80000000 | nLength;
        pPath = 0;
    }
    func_02020c7c(player + 4, nId, pPath, player + 0x8598);

    if (args->bSubScreen != 0) {
        *(u16 *)(player + 2) |= 8;
    }
    *(u16 *)(player + 2) |= 1;
    *(u8 *)(player + 0x8be1) = 0;
    wHeld = (u16)(((*REG_KEYINPUT | *REG_EXTKEYIN) ^ KEY_MASK) & KEY_MASK);
    *(int *)(player + 0x8bec) = wHeld & 8;
    data_ov024_02093a20[0] = 0;
    return (void *)&func_ov024_02082f04;
}
