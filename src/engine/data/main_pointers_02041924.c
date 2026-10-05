/* main .rodata pointer tables, 0x02041924-0x020419c4.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void AllocatorAllocForSDKHeap(void);
extern void AllocatorFreeForSDKHeap(void);
extern void Gfd_LoadTex(void);
extern void Gfd_LoadTexPltt(void);
extern void DoTransfer2dObjExtPlttMain(void);
extern void DoTransfer2dBGExtPlttMain(void);
extern void Gfd_LoadSubObjExtPltt(void);
extern void Gfd_LoadSubBgExtPltt(void);
extern void AllocatorAllocForExpHeap(void);
extern void AllocatorFreeForExpHeap(void);
extern void GXS_LoadBG0Char(void);
extern void GXS_LoadBG0Scr(void);
extern void GXS_LoadBG1Char(void);
extern void GXS_LoadBG1Scr(void);
extern void GXS_LoadBG2Char(void);
extern void GXS_LoadBG2Scr(void);
extern void GXS_LoadBG3Char(void);
extern void GXS_LoadBG3Scr(void);
extern void GXS_LoadBGPltt(void);
extern void GXS_LoadOAM(void);
extern void GXS_LoadOBJ(void);
extern void GXS_LoadOBJPltt(void);
extern void GX_LoadBG0Char(void);
extern void GX_LoadBG0Scr(void);
extern void GX_LoadBG1Char(void);
extern void GX_LoadBG1Scr(void);
extern void GX_LoadBG2Char(void);
extern void GX_LoadBG2Scr(void);
extern void GX_LoadBG3Char(void);
extern void GX_LoadBG3Scr(void);
extern void GX_LoadBGPltt(void);
extern void GX_LoadOAM(void);
extern void GX_LoadOBJ(void);
extern void GX_LoadOBJPltt(void);

void *const data_02041924[4] = {

    &AllocatorAllocForExpHeap,

    &AllocatorFreeForExpHeap,

    (void *)AllocatorAllocForSDKHeap,

    (void *)AllocatorFreeForSDKHeap,

};

void *const data_02041934[36] = {

    (void *)Gfd_LoadTex,

    (void *)Gfd_LoadTexPltt,

    0,

    0,

    &GX_LoadBG0Char,

    &GX_LoadBG1Char,

    &GX_LoadBG2Char,

    &GX_LoadBG3Char,

    &GX_LoadBG0Scr,

    &GX_LoadBG1Scr,

    &GX_LoadBG2Scr,

    &GX_LoadBG3Scr,

    0,

    0,

    &GX_LoadOBJPltt,

    &GX_LoadBGPltt,

    (void *)DoTransfer2dObjExtPlttMain,

    (void *)DoTransfer2dBGExtPlttMain,

    &GX_LoadOAM,

    &GX_LoadOBJ,

    &GXS_LoadBG0Char,

    &GXS_LoadBG1Char,

    &GXS_LoadBG2Char,

    &GXS_LoadBG3Char,

    &GXS_LoadBG0Scr,

    &GXS_LoadBG1Scr,

    &GXS_LoadBG2Scr,

    &GXS_LoadBG3Scr,

    0,

    0,

    &GXS_LoadOBJPltt,

    &GXS_LoadBGPltt,

    (void *)Gfd_LoadSubObjExtPltt,

    (void *)Gfd_LoadSubBgExtPltt,

    &GXS_LoadOAM,

    &GXS_LoadOBJ,

};
