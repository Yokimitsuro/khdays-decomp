/* func_ov025_020a8d50 -- Ov008_MissionListDestroy: tear the mission list
 * down.  Mode (+0x504) becomes 1, the list node (+0x80) is removed and
 * freed, the global int array c22c cleared while the entry gate (+0x40) is
 * set, the mission list (+0x4d4) destroyed, the two text caches (+0x4bc,
 * +0x4c8) released, the list's helper state reset (0206fcbc), the 3 x 6 row
 * surfaces (+0x84 / +0x1ec / +0x354, 0x3c each) drop their sub-buffers, the
 * six tag-tracker nodes of data_ov025_020b45a8 are disarmed in block 954c
 * and its element list cleared, widgets 4 / 5 of the context and 0x3d, 0x3e,
 * 0x3f, 1, 0x47, 0x48 of block 4a80 hidden, and the sub engine's BG1 / BG3
 * scroll registers zeroed.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT 6
#define TAG_COUNT 6

typedef struct TileSurface {
    u8 pad[0x3c];
} TileSurface;

typedef struct Ov008MissionList {
    u8  pad_000[0x40];
    int bEntryGate;           /* 0x040 */
    u8  pad_044[0x80 - 0x44];
    void *pListNode;          /* 0x080 */
    TileSurface aRowNameSurface[ROW_COUNT];   /* 0x084 */
    TileSurface aRowInfoSurface[ROW_COUNT];   /* 0x1ec */
    TileSurface aRowExtraSurface[ROW_COUNT];  /* 0x354 */
    u8  textCacheA[0xc];      /* 0x4bc */
    u8  textCacheB[0xc];      /* 0x4c8 */
    u8  missionList[0x504 - 0x4d4]; /* 0x4d4 */
    int nMode;                /* 0x504 */
} Ov008MissionList;

typedef struct Ov008TagTable {
    int aTag[TAG_COUNT];
} Ov008TagTable;

extern const Ov008TagTable data_ov025_020b45a8;
extern void func_ov025_02084b78(void *pNode);                             /* Ov008_ListRemoveAndFree */
extern void func_02030d10(int nFlag);                                     /* ClearGlobalArrayInt_c22c */
extern void func_ov025_0208a19c(void *pList);                             /* Ov008_DestroyMissionList */
extern void func_ov025_02089884(void *pCache);                            /* release a text cache */
extern void func_ov025_020a5260(Ov008MissionList *pList);                 /* Ov008_Set_fcbc */
extern void func_0202ffbc(void *pList);                                   /* FreeAllListNodeSubBuffers */
extern int  func_ov025_02084a64(void);                                    /* Ov008_GetCtxBlock954c */
extern int  func_ov025_0208969c(int nOwner, u32 nTag);                    /* ov008_FindActiveEntryByTag */
extern void func_ov025_020896fc(int nOwner, int nEntry, int bArmed);      /* SetTagTrackerNodeArmed */
extern void func_ov025_02089644(int *pBlock);                             /* ClearElementList */
extern int  func_ov025_02084a7c(void);                                    /* Ov008_GetContext */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern int  func_ov025_02084a8c(void);                                    /* Ov008_GetCtxBlock4a80 */

void func_ov025_020a8d50(Ov008MissionList *pList)
{
    Ov008TagTable tags;
    int i;
    int nOwner;
    int nCtx;
    volatile int *pScroll = (volatile int *)0x04001014;

    pList->nMode = 1;
    func_ov025_02084b78(pList->pListNode);
    if (pList->bEntryGate != 0) {
        func_02030d10(0);
    }
    func_ov025_0208a19c(pList->missionList);
    func_ov025_02089884(pList->textCacheA);
    func_ov025_02089884(pList->textCacheB);
    func_ov025_020a5260(pList);
    for (i = 0; i < ROW_COUNT; i++) {
        func_0202ffbc(&pList->aRowNameSurface[i]);
        func_0202ffbc(&pList->aRowInfoSurface[i]);
        func_0202ffbc(&pList->aRowExtraSurface[i]);
    }
    tags = data_ov025_020b45a8;
    nOwner = func_ov025_02084a64();
    for (i = 0; i < TAG_COUNT; i++) {
        func_ov025_020896fc(nOwner, func_ov025_0208969c(nOwner, (u16)tags.aTag[i]), 0);
    }
    func_ov025_02089644((int *)func_ov025_02084a64());
    nCtx = func_ov025_02084a7c();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 4), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 5), 0);
    nCtx = func_ov025_02084a8c();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x3d), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x3e), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x3f), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 1), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x47), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x48), 0);
    pScroll[0] = 0;
    pScroll[2] = 0;
}
