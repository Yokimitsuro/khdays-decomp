/* func_ov011_0205c074 -- switch the scene into mode 2 and rebuild its display for it.
 *
 * Points the scene at a six-entry table, resets the cursor, kicks the mode-1 handler,
 * throws away the old work buffer and loads its replacement out of the archive, then
 * reprogrammes both engines: clear the layer-enable bits, zero the BG2 and BG3 offsets on
 * both, and set each engine's mode field -- 0x19 on the main, 0x11 on the sub. Finally
 * the scrolled bit is cleared, as it is on every mode change.
 *
 * The archive handle is the usual NitroSDK idiom: round the archive base up past 0x8000,
 * keep the 24 bits that address a file, shift into place and tag the low nibble with the
 * file's index. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011Scene {
    u8    pad_00000[4];
    int   nMode;
    u8    pad_00008[4];
    u32   nArchiveBase;
    u8    pad_00010[4];
    void *pBuffer;
    u8    pad_00018[0x23abd - 0x18];
    u8    bFlags;
    u8    pad_23abe[0x23ac8 - 0x23abe];
    u16   wA;
    u16   wB;
    const void *pTable;
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern const u8 data_ov011_0205dd10[];
extern u8 data_ov011_0205e930[];

extern void  func_02000fb4(int nMode, u8 *pName);
extern void  NNSi_FndFreeFromDefaultHeap(void *p);
extern void *func_0201ef9c(u32 nHandle, int nHeap);

void func_ov011_0205c074(void)
{
    data_ov011_0205e960.pScene->nMode = 2;
    data_ov011_0205e960.pScene->pTable = data_ov011_0205dd10;
    data_ov011_0205e960.pScene->wB = 6;
    data_ov011_0205e960.pScene->wA = 0;
    func_02000fb4(1, data_ov011_0205e930);
    NNSi_FndFreeFromDefaultHeap(data_ov011_0205e960.pScene->pBuffer);
    data_ov011_0205e960.pScene->pBuffer = func_0201ef9c(
        ((data_ov011_0205e960.pScene->nArchiveBase + 0x8000 & 0xfffffc) << 7)
            | 0x80000004, 0xe);
    *(volatile u32 *)0x04000000 &= ~0xe000;
    *(volatile u32 *)0x04001000 &= ~0xe000;
    *(volatile u32 *)0x04000018 = 0;
    *(volatile u32 *)0x0400001c = 0;
    *(volatile u32 *)0x04001018 = 0;
    *(volatile u32 *)0x0400101c = 0;
    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & ~0x1f00) | 0x1900;
    *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0x1f00) | 0x1100;
    data_ov011_0205e960.pScene->bFlags &= ~1;
}
