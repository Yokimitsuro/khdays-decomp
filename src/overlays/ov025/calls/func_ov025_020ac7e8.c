/* func_ov025_020ac7e8 -- Ov008_LoadMissionMenuGraphics: upload the mission
 * menu's sub-screen graphics (twin of 02072418).  The background archive is member 0x14 of the
 * slot table when global short 0204c1ec is 1, else sub-file 6; its sprite set
 * (palette + character) goes to the sub engine's BG palette and BG3
 * characters.  Members 0x10 / 0x11 are streamed to BG0 / BG2 characters
 * (0207714c); unless the global short is 1, sub-file 7 (when present) is also
 * flushed and uploaded at character offset 0x2000 of BG0 and BG2.  Finally the
 * tag-tracker callbacks of tags 3 and 6 in block 954c fire and resource slots
 * 0x19, 0x1a and 0x1b are marked used.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define HEAP_FILE     0xe
#define CHAR_OFFSET   0x2000
#define MODE_ALT      1

typedef struct Ov008PaletteBlock   { u8 pad_00[0x08]; u32 nSize; void *pData; } Ov008PaletteBlock;
typedef struct Ov008CharacterBlock { u8 pad_00[0x10]; u32 nSize; void *pData; } Ov008CharacterBlock;

typedef struct SpriteResSet {
    void *pScreen;
    Ov008CharacterBlock *pChar;
    Ov008PaletteBlock *pPalette;
} SpriteResSet;

typedef void (*BgCharLoader)(const void *pSrc, u32 nOffset, u32 nSize);

extern void *func_ov025_02084a64(void);                                  /* Ov008_GetCtxBlock954c */
extern int   func_02024e5c(void);                                        /* LoadGlobalShort_0204c1ec */
extern u32   func_ov025_02084d18(int nMember);                           /* Ov008_PackSlotTag */
extern u32   func_ov025_02084d50(int nSubfile);                          /* sub-file archive id */
extern void *func_0201ef9c(u32 nArchiveId, int nHeap);                   /* Archive_LoadFile */
extern void  func_02024c94(SpriteResSet *pSet, void *pFile, int nScreen, int nChar, int nPalette); /* Res_LoadSpriteSet */
extern void  GXS_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG3Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG0Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG2Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_ov025_020ac7a4(u32 nArchiveId, BgCharLoader pLoad);   /* stream a character block */
extern void  func_020119d4(void *pFile, Ov008CharacterBlock **ppBlock); /* GetResourceSubBlock_CHAR2 */
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void *func_ov025_020894b0(void *pOwner, int nTag);                /* ov008_FindEntryByTag */
extern void  func_ov025_02089544(void *pOwner, void *pEntry);            /* Ov008_TagTracker_InvokeCallback */
extern void  func_ov025_02084964(int nSlot);                             /* Ov008_MarkSlotUsed */

void func_ov025_020ac7e8(void)
{
    void *pOwner;
    void *pFile;
    SpriteResSet set;
    Ov008CharacterBlock *pChar;
    int bAlt;
    u32 nId;

    bAlt = func_02024e5c() == MODE_ALT;
    if (bAlt) {
        pFile = func_0201ef9c(func_ov025_02084d18(0x14), HEAP_FILE);
    } else {
        pFile = func_0201ef9c(func_ov025_02084d50(6), HEAP_FILE);
    }
    func_02024c94(&set, pFile, 0, 0, 0);
    GXS_LoadBGPltt(set.pPalette->pData, 0, set.pPalette->nSize);
    GXS_LoadBG3Char(set.pChar->pData, 0, set.pChar->nSize);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
    pOwner = func_ov025_02084a64();
    func_ov025_020ac7a4(func_ov025_02084d18(0x10), GXS_LoadBG0Char);
    func_ov025_020ac7a4(func_ov025_02084d18(0x11), GXS_LoadBG2Char);
    bAlt = func_02024e5c() == MODE_ALT;
    if (!bAlt) {
        nId = func_ov025_02084d50(7);
        if (nId != 0) {
            pFile = func_0201ef9c(nId, HEAP_FILE);
            func_020119d4(pFile, &pChar);
            DC_FlushRange(pChar->pData, pChar->nSize);
            GXS_LoadBG0Char(pChar->pData, CHAR_OFFSET, pChar->nSize);
            DC_FlushRange(pChar->pData, pChar->nSize);
            GXS_LoadBG2Char(pChar->pData, CHAR_OFFSET, pChar->nSize);
            if (pFile != 0) {
                NNSi_FndFreeFromDefaultHeap(pFile);
            }
        }
    }
    func_ov025_02089544(pOwner, func_ov025_020894b0(pOwner, 3));
    func_ov025_02089544(pOwner, func_ov025_020894b0(pOwner, 6));
    func_ov025_02084964(0x19);
    func_ov025_02084964(0x1a);
    func_ov025_02084964(0x1b);
}
