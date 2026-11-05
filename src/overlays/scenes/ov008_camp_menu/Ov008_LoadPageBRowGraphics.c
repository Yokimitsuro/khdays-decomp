/* Ov008_LoadPageBRowGraphics -- Ov008_LoadPageBRowGraphics: upload the sub-screen
 * graphics of page B's current row.  The row's entry word comes from the
 * ov025 list at +0x200 (row +0x1e8); bit 16 of it selects the second archive
 * handle (+0x34) over the first (+0x30), and its low 9 bits are the member id.
 * The archive file is loaded (heap 0xe), relocated, and its palette (member 0),
 * character (member 1) and screen (member 6) blocks are uploaded to the sub
 * engine's BG palette, BG1 characters and BG1 screen; then the file is closed
 * and freed.
 */

#include "nitro/types.h"
#include "game/archive.h"

#define ENTRY_ALT_ARCHIVE 0x10000
#define ENTRY_MEMBER_MASK 0x1ff
#define ARCHIVE_ID(hArchive, nMember) \
    (ARCHIVE_HANDLE((hArchive), nMember))

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

extern Ov008PageB *Ov008_GetPageB(void);                          /* Ov008_GetPageB */
extern u32   Ov025_Res_GetEntryOffset(void *pList, int nRow);                /* list entry word */
extern void *Archive_LoadFile(u32 nArchiveId, int nHeap);                  /* Archive_LoadFile */
extern void  Obj_RelocateSections(void *pFile, int bEnableDispatch);           /* Obj_RelocateSections */
extern int   Archive_GetMember(void *pFile, int nMember, int nSub);         /* Archive_GetMember */
extern int   NNS_G2dGetUnpackedPaletteData(int hMember, Ov008PaletteBlock **ppBlock);   /* GetResourceSubBlock_PLTT */
extern int   GetResourceSubBlock_CHAR(int hMember, Ov008CharacterBlock **ppBlock); /* GetResourceSubBlock_CHAR */
extern int   NNS_G2dGetUnpackedScreenData(int hMember, Ov008ScreenBlock **ppBlock);    /* findResourceNRCS */
extern void  GXS_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG1Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG1Scr(const void *pSrc, u32 nOffset, u32 nSize);
extern void  ResGroup_Release(void *pFile);                                /* close the archive file */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);

void Ov008_LoadPageBRowGraphics(void)
{
    Ov008PageB *pPage;
    void *pFile;
    u32 nEntry;
    Ov008CharacterBlock *pCharacter;
    Ov008ScreenBlock *pScreen;
    Ov008PaletteBlock *pPalette;

    pPage = Ov008_GetPageB();
    nEntry = Ov025_Res_GetEntryOffset(pPage->list, (unsigned short)pPage->nRow);
    if (nEntry & ENTRY_ALT_ARCHIVE) {
        pFile = Archive_LoadFile(ARCHIVE_ID(pPage->hArchiveAlt, nEntry & ENTRY_MEMBER_MASK), 0xe);
    } else {
        pFile = Archive_LoadFile(ARCHIVE_ID(pPage->hArchive, nEntry & ENTRY_MEMBER_MASK), 0xe);
    }
    Obj_RelocateSections(pFile, 1);
    NNS_G2dGetUnpackedPaletteData(Archive_GetMember(pFile, 0, 0), &pPalette);
    GetResourceSubBlock_CHAR(Archive_GetMember(pFile, 1, 0), &pCharacter);
    NNS_G2dGetUnpackedScreenData(Archive_GetMember(pFile, 6, 0), &pScreen);
    GXS_LoadBGPltt(pPalette->pData, 0, pPalette->nSize);
    GXS_LoadBG1Char(pCharacter->pData, 0, pCharacter->nSize);
    GXS_LoadBG1Scr(pScreen->aData, 0, pScreen->nSize);
    ResGroup_Release(pFile);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
}
