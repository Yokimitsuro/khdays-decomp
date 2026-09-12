/* func_ov008_020785cc -- Ov008_LoadPageBRowGraphics: upload the sub-screen
 * graphics of page B's current row.  The row's entry word comes from the
 * ov025 list at +0x200 (row +0x1e8); bit 16 of it selects the second archive
 * handle (+0x34) over the first (+0x30), and its low 9 bits are the member id.
 * The archive file is loaded (heap 0xe), relocated, and its palette (member 0),
 * character (member 1) and screen (member 6) blocks are uploaded to the sub
 * engine's BG palette, BG1 characters and BG1 screen; then the file is closed
 * and freed.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define ENTRY_ALT_ARCHIVE 0x10000
#define ENTRY_MEMBER_MASK 0x1ff
#define ARCHIVE_ID(hArchive, nMember) \
    ((((hArchive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (nMember))

typedef struct Ov008PageB {
    u8  pad_000[0x30];
    int hArchive;             /* 0x030 */
    int hArchiveAlt;          /* 0x034 */
    u8  pad_038[0x1e8 - 0x38];
    int nRow;                 /* 0x1e8 */
    u8  pad_1ec[0x200 - 0x1ec];
    u8  list[4];              /* 0x200: ov025 list */
} Ov008PageB;

typedef struct Ov008PaletteBlock   { u8 pad_00[0x08]; u32 nSize; void *pData; } Ov008PaletteBlock;
typedef struct Ov008CharacterBlock { u8 pad_00[0x10]; u32 nSize; void *pData; } Ov008CharacterBlock;
typedef struct Ov008ScreenBlock    { u8 pad_00[0x08]; u32 nSize; u8 aData[1]; } Ov008ScreenBlock;

extern Ov008PageB *func_ov008_02050cec(void);                          /* Ov008_GetPageB */
extern u32   func_ov025_020b0858(void *pList, int nRow);                /* list entry word */
extern void *func_0201ef9c(u32 nArchiveId, int nHeap);                  /* Archive_LoadFile */
extern void  func_02025464(void *pFile, int bEnableDispatch);           /* Obj_RelocateSections */
extern int   func_020255d4(void *pFile, int nMember, int nSub);         /* Archive_GetMember */
extern int   func_02011a20(int hMember, Ov008PaletteBlock **ppBlock);   /* GetResourceSubBlock_PLTT */
extern int   func_02011988(int hMember, Ov008CharacterBlock **ppBlock); /* GetResourceSubBlock_CHAR */
extern int   func_02011a6c(int hMember, Ov008ScreenBlock **ppBlock);    /* findResourceNRCS */
extern void  GXS_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG1Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG1Scr(const void *pSrc, u32 nOffset, u32 nSize);
extern void  func_0202552c(void *pFile);                                /* close the archive file */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);

void func_ov008_020785cc(void)
{
    Ov008PageB *pPage;
    void *pFile;
    u32 nEntry;
    Ov008CharacterBlock *pCharacter;
    Ov008ScreenBlock *pScreen;
    Ov008PaletteBlock *pPalette;

    pPage = func_ov008_02050cec();
    nEntry = func_ov025_020b0858(pPage->list, (unsigned short)pPage->nRow);
    if (nEntry & ENTRY_ALT_ARCHIVE) {
        pFile = func_0201ef9c(ARCHIVE_ID(pPage->hArchiveAlt, nEntry & ENTRY_MEMBER_MASK), 0xe);
    } else {
        pFile = func_0201ef9c(ARCHIVE_ID(pPage->hArchive, nEntry & ENTRY_MEMBER_MASK), 0xe);
    }
    func_02025464(pFile, 1);
    func_02011a20(func_020255d4(pFile, 0, 0), &pPalette);
    func_02011988(func_020255d4(pFile, 1, 0), &pCharacter);
    func_02011a6c(func_020255d4(pFile, 6, 0), &pScreen);
    GXS_LoadBGPltt(pPalette->pData, 0, pPalette->nSize);
    GXS_LoadBG1Char(pCharacter->pData, 0, pCharacter->nSize);
    GXS_LoadBG1Scr(pScreen->aData, 0, pScreen->nSize);
    func_0202552c(pFile);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
}
