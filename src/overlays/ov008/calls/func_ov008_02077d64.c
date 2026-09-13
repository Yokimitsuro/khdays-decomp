/* func_ov008_02077d64 -- Ov008_MissionMenuDestroy: tear the mission menu
 * down.  During a transfer the global int array c22c is cleared first.  The
 * mission list (+0x548) is destroyed, the two text caches (+0x530, +0x53c)
 * released, the +0x174 block freed, resource slots 0x15, 0x19 and 0x1a
 * dereferenced; the five tag-tracker nodes named by data_ov008_0208fa38
 * (1, 2, 11, 12, 13, copied to the stack) are disarmed in context block 954c;
 * the five row lists (+0xc, stride 0x3c) drop their sub-buffers; block 954c's
 * element list is cleared; widgets 0x40 and 0x41 of block 4a80 are hidden;
 * the list node at +0x170 is removed and freed; and the sub engine's BG2 /
 * BG3 scroll registers are zeroed.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TAG_COUNT 5
#define WIDGET_A  0x40
#define WIDGET_B  0x41

typedef struct Ov008RowList {
    u8 pad[0x3c];
} Ov008RowList;

typedef struct Ov008MissionMenu {
    u8  pad_000[0xc];
    Ov008RowList aRowList[5]; /* 0x00c */
    u8  pad_138[0x150 - 0x138];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x170 - 0x154];
    void *pListNode;          /* 0x170 */
    u8  pad_174[0x530 - 0x174];
    u8  textCacheA[0xc];      /* 0x530 */
    u8  textCacheB[0xc];      /* 0x53c */
    u8  missionList[4];       /* 0x548 */
} Ov008MissionMenu;

typedef struct Ov008TagTable {
    int aTag[TAG_COUNT];
} Ov008TagTable;

extern const Ov008TagTable data_ov008_0208fa38;
extern void func_02030d10(int nFlag);                                   /* ClearGlobalArrayInt_c22c */
extern void func_ov008_0205658c(void *pList);                           /* Ov008_DestroyMissionList */
extern void func_ov008_02055c74(void *pCache);                          /* release a text cache */
extern void func_ov008_0207447c(Ov008MissionMenu *pMenu);               /* free the +0x174 block */
extern void func_ov008_020510f8(int nSlot);                             /* Ov008_DecRefSlot */
extern int  func_ov008_02050c3c(void);                                  /* Ov008_GetCtxBlock954c */
extern int  func_ov008_02055a8c(int nOwner, u32 nTag);                  /* ov008_FindActiveEntryByTag */
extern void func_ov008_02055aec(int nOwner, int nEntry, int bArmed);    /* SetTagTrackerNodeArmed */
extern void func_0202ffbc(void *pList);                                 /* FreeAllListNodeSubBuffers */
extern void func_ov008_02055a34(int *pBlock);                           /* ClearElementList */
extern int  func_ov008_02050c64(void);                                  /* Ov008_GetCtxBlock4a80 */
extern void *func_ov008_02054788(int nCtx, int nId);                    /* FindEntryById */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */
extern void func_ov008_02050d50(void *pNode);                           /* Ov008_ListRemoveAndFree */

void func_ov008_02077d64(Ov008MissionMenu *pMenu)
{
    Ov008TagTable tags;
    int i;
    int nOwner;
    int nCtx;
    volatile int *pScroll = (volatile int *)0x04001018;

    if (pMenu->bTransfer != 0) {
        func_02030d10(0);
    }
    func_ov008_0205658c(pMenu->missionList);
    func_ov008_02055c74(pMenu->textCacheA);
    func_ov008_02055c74(pMenu->textCacheB);
    func_ov008_0207447c(pMenu);
    func_ov008_020510f8(0x15);
    func_ov008_020510f8(0x19);
    func_ov008_020510f8(0x1a);
    tags = data_ov008_0208fa38;
    nOwner = func_ov008_02050c3c();
    for (i = 0; i < TAG_COUNT; i++) {
        func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, (u16)tags.aTag[i]), 0);
    }
    func_0202ffbc(&pMenu->aRowList[0]);
    func_0202ffbc(&pMenu->aRowList[1]);
    func_0202ffbc(&pMenu->aRowList[2]);
    func_0202ffbc(&pMenu->aRowList[3]);
    func_0202ffbc(&pMenu->aRowList[4]);
    func_ov008_02055a34((int *)func_ov008_02050c3c());
    nCtx = func_ov008_02050c64();
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_A), 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_B), 0);
    func_ov008_02050d50(pMenu->pListNode);
    pScroll[0] = 0;
    pScroll[1] = 0;
}
