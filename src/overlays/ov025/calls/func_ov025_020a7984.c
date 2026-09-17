/* func_ov025_020a7984 -- Ov025_MissionList_LoadSubScreen: load the mission list's sub-screen
 * graphics.  Its background comes from archive member 0x14 (Ov008_PackSlotTag 02084d18) when
 * the language word (02024e5c) is 1, else from localised sub-file 6 (02084d50); the file
 * (0201ef9c, heap 0xe) gives the palette / character / screen cell (Res_LoadSpriteSet 02024c94):
 * the palette goes to the sub BG palette RAM (GXS_LoadBGPltt) and the characters to sub BG3
 * (GXS_LoadBG3Char), then the file is freed.  Members 0x10 and 0x11 load their CHAR blocks into
 * sub BG0 and BG2 (020a7940); outside language 1 localised sub-file 7, when present, adds its
 * characters at 0x2000 of both (020119d4, DC_FlushRange).  Cell 0 of the shared tag tracker
 * (02084a64) is invoked (Ov008_TagTracker_InvokeCallback 02089544) outside a page transition
 * (02084e38) -- and cell 1 too with touch enabled (+0x38) and no 9630 object (02084e08) -- else
 * cell 2; cell 4 always; VRAM slots 0x19..0x1b are marked used (02084964).  Sibling of the day
 * list's 020ae384. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008PaletteBlock   { u8 pad_0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;
typedef struct Ov008ScreenBlock    { u8 pad_0000[0x08]; u32 size; u8 data[1]; } Ov008ScreenBlock;
typedef struct Ov008ResourceCell {
    Ov008ScreenBlock    *screen;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock   *palette;
} Ov008ResourceCell;

typedef struct Ov008MissionList {
    u8   pad_000[0x38];
    int  bTouchEnabled;       /* 0x038 */
} Ov008MissionList;

typedef void (*Ov025CharLoader)(const void *pSrc, u32 nOffset, u32 nSize);

extern int   func_ov025_02084a64(void);                             /* Ov008_GetCtxBlock954c: the tag tracker */
extern int   func_02024e5c(void);                                   /* LoadGlobalShort_0204c1ec: the language */
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern u32   func_ov025_02084d50(int nSubFile);                     /* Ov008_PackLocalisedTag */
extern void *func_0201ef9c(u32 nTag, int nHeap);                    /* Res_Open */
extern void  func_02024c94(Ov008ResourceCell *pCell, void *pFile, int nScreen, int nChar, int nPalette); /* Res_LoadSpriteSet */
extern void  GXS_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG3Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG0Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG2Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_ov025_020a7940(u32 nTag, Ov025CharLoader pfnLoad); /* Ov025_LoadCharBlock */
extern void  func_020119d4(void *pFile, Ov008CharacterBlock **ppBlock); /* NNS_G2dGetUnpackedCharacterData */
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern int   func_ov025_02084e08(void);                             /* Ov008_GetCtxObject9630 */
extern void *func_ov025_020894b0(int nTracker, int nTag);           /* Ov008_TagTracker_FindCell */
extern void  func_ov025_02089544(int nTracker, void *pCell);        /* Ov008_TagTracker_InvokeCallback */
extern void  func_ov025_02084964(int nSlot);                        /* Ov008_MarkSlotUsed */

void func_ov025_020a7984(Ov008MissionList *pList)
{
    void *pFile;
    int nTracker;
    Ov008ResourceCell cell;
    int bDefaultLanguage;
    u32 nAltTag;
    void *pAltFile;
    Ov008CharacterBlock *pBlock;

    nTracker = func_ov025_02084a64();
    bDefaultLanguage = func_02024e5c() == 1;
    if (bDefaultLanguage) {
        pFile = func_0201ef9c(func_ov025_02084d18(0x14), 0xe);
    } else {
        pFile = func_0201ef9c(func_ov025_02084d50(6), 0xe);
    }
    func_02024c94(&cell, pFile, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GXS_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
    func_ov025_020a7940(func_ov025_02084d18(0x10), GXS_LoadBG0Char);
    func_ov025_020a7940(func_ov025_02084d18(0x11), GXS_LoadBG2Char);
    bDefaultLanguage = func_02024e5c() == 1;
    if (!bDefaultLanguage) {
        nAltTag = func_ov025_02084d50(7);
        if (nAltTag != 0) {
            pAltFile = func_0201ef9c(nAltTag, 0xe);
            func_020119d4(pAltFile, &pBlock);
            DC_FlushRange(pBlock->data, pBlock->size);
            GXS_LoadBG0Char(pBlock->data, 0x2000, pBlock->size);
            DC_FlushRange(pBlock->data, pBlock->size);
            GXS_LoadBG2Char(pBlock->data, 0x2000, pBlock->size);
            if (pAltFile != 0) {
                NNSi_FndFreeFromDefaultHeap(pAltFile);
            }
        }
    }
    if (func_ov025_02084e38() != 0) {
        func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 2));
    } else {
        func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 0));
        if (func_ov025_02084e08() == 0 && pList->bTouchEnabled != 0) {
            func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 1));
        }
    }
    func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 4));
    func_ov025_02084964(0x19);
    func_ov025_02084964(0x1a);
    func_ov025_02084964(0x1b);
}
