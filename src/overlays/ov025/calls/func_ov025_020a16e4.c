/* func_ov025_020a16e4 -- Ov008_ScrollMenu_SetupEntries: bind the scrolling menu's sprites in the
 * 4a80 block (02084a8c).  The layout template data_ov025_020b4380 takes archive member 0x28 as
 * its resource (Ov008_PackSlotTag 02084d18; 020883f8), resource 2 by index is attached
 * (02084d94 / 02088410) and the 0x42 entries of member 0x29 loaded (0208832c); entry 0x51 goes
 * to mode 3 (02088a38), entry 0x2b is offset to y 0xf (<< 12) from its position (02088544 /
 * 02088564), entry 0x4a shows the cell of game-state field 0x40a (2 bits; 020888b0 / 02088928),
 * the positions of entries 0x29 / 0x51 are kept as the cursor bases (+0x20c / +0x214), entry
 * 0x80 shown (0208884c) and entries 0x2b / 0x2c get the callbacks 020a3eac / 020a3edc
 * (02088420) -- with sub-item set 1 pushed on both (020887c0) while the sub LCD is off (POWCNT1
 * bit 15).  The four panel entries of data_ov025_020b4370 give the positions +0x21c. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

typedef struct Ov008LayoutTemplate {
    u32  words[4];
} Ov008LayoutTemplate;

typedef struct Ov025PanelIds {
    int  aId[4];
} Ov025PanelIds;

typedef struct Ov008ScrollMenu {
    u8   pad_000[0x20c];
    UiLayoutPos cursorBaseA;  /* 0x20c: base of widget 0x29 */
    UiLayoutPos cursorBaseB;  /* 0x214: base of widget 0x51 */
    UiLayoutPos aPos[4];      /* 0x21c: the four panel positions */
} Ov008ScrollMenu;

static volatile u16 *const REG_POWCNT1 = (volatile u16 *)0x04000304;

extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern void  func_ov025_020883f8(int nCtx, Ov008LayoutTemplate *pLayout); /* Ov008_SetLayout */
extern void *func_ov025_02084d94(int nIndex);                       /* Ov025_ResourceByIndex */
extern void  func_ov025_02088410(int nCtx, void *pResource);        /* Ov025_SetEntryResource */
extern void  func_ov025_0208832c(int nCtx, u32 nTag, int nCount);   /* Ov008_LoadBlockProcessAndFree */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_02088a38(int nCtx, void *pEntry, int nValue); /* Ov008_SetEntryMode */
extern UiLayoutPos *func_ov025_02088544(int nCtx, void *pEntry);    /* Ov008_GetEntryPos */
extern void  func_ov025_02088564(int nCtx, void *pEntry, UiLayoutPos *pOffset); /* Ov025_SetEntryOffset */
extern void  func_ov025_020888b0(int nCtx, void *pEntry);           /* Ov025_ReleaseTwoSlots */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nCell); /* Ov025_SetEntryCell */
extern void  MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_02088420(int nCtx, int nId, void *pCallback); /* Ov008_ResolveEntryStoreWord */
extern void  func_ov025_020a3eac(void);
extern void  func_ov025_020a3edc(void);
extern void  func_ov025_020887c0(int nCtx, void *pEntry, int nSet); /* Ov008_PushSubitemSet */
extern const Ov025PanelIds data_ov025_020b4370;                      /* the four panel entry ids */
extern Ov008LayoutTemplate data_ov025_020b4380;

void func_ov025_020a16e4(Ov008ScrollMenu *pMenu)
{
    Ov025PanelIds ids;
    Ov008LayoutTemplate layout;
    int nCtx;
    void *pEntry;
    UiLayoutPos *pPos;
    UiLayoutPos offset;
    int i;
    UiLayoutPos *pDst;

    ids = data_ov025_020b4370;
    layout = data_ov025_020b4380;
    nCtx = func_ov025_02084a8c();
    layout.words[0] = func_ov025_02084d18(0x28);
    func_ov025_020883f8(nCtx, &layout);
    func_ov025_02088410(nCtx, func_ov025_02084d94(2));
    func_ov025_0208832c(nCtx, func_ov025_02084d18(0x29), 0x42);
    func_ov025_02088a38(nCtx, func_ov025_0208843c(nCtx, 0x51), 3);
    pPos = func_ov025_02088544(nCtx, func_ov025_0208843c(nCtx, 0x2b));
    offset.x = 0;
    offset.y = 0xf0000 - pPos->y;
    func_ov025_02088564(nCtx, func_ov025_0208843c(nCtx, 0x2b), &offset);
    pEntry = func_ov025_0208843c(nCtx, 0x4a);
    func_ov025_020888b0(nCtx, pEntry);
    func_ov025_02088928(nCtx, pEntry, (u16)func_020235d0(0x40a, 2));
    MI_CpuCopy8(func_ov025_02088544(nCtx, func_ov025_0208843c(nCtx, 0x29)), &pMenu->cursorBaseA, 8);
    MI_CpuCopy8(func_ov025_02088544(nCtx, func_ov025_0208843c(nCtx, 0x51)), &pMenu->cursorBaseB, 8);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x80), 1);
    func_ov025_02088420(nCtx, 0x2b, func_ov025_020a3eac);
    func_ov025_02088420(nCtx, 0x2c, func_ov025_020a3edc);
    if ((*REG_POWCNT1 & 0x8000) >> 15 == 0) {
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 0x2b), 1);
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 0x2c), 1);
    }
    pDst = pMenu->aPos;
    for (i = 0; i < 4; i++) {
        MI_CpuCopy8(func_ov025_02088544(nCtx, func_ov025_0208843c(nCtx, ids.aId[i])), pDst, 8);
        pDst++;
    }
}
