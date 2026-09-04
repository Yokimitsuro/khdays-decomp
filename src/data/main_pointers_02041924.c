/* main .rodata pointer tables, 0x02041924-0x020419c4.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void func_02010da0(void);
extern void func_02010dbc(void);
extern void func_020113a4(void);
extern void func_020113d0(void);
extern void func_020113fc(void);
extern void func_02011428(void);
extern void func_02011454(void);
extern void func_02011480(void);
extern int AllocatorAllocForExpHeap;
extern int AllocatorFreeForExpHeap;
extern int GXS_LoadBG0Char;
extern int GXS_LoadBG0Scr;
extern int GXS_LoadBG1Char;
extern int GXS_LoadBG1Scr;
extern int GXS_LoadBG2Char;
extern int GXS_LoadBG2Scr;
extern int GXS_LoadBG3Char;
extern int GXS_LoadBG3Scr;
extern int GXS_LoadBGPltt;
extern int GXS_LoadOAM;
extern int GXS_LoadOBJ;
extern int GXS_LoadOBJPltt;
extern int GX_LoadBG0Char;
extern int GX_LoadBG0Scr;
extern int GX_LoadBG1Char;
extern int GX_LoadBG1Scr;
extern int GX_LoadBG2Char;
extern int GX_LoadBG2Scr;
extern int GX_LoadBG3Char;
extern int GX_LoadBG3Scr;
extern int GX_LoadBGPltt;
extern int GX_LoadOAM;
extern int GX_LoadOBJ;
extern int GX_LoadOBJPltt;

void *const data_02041924[4] = {

    &AllocatorAllocForExpHeap,

    &AllocatorFreeForExpHeap,

    (void *)func_02010da0,

    (void *)func_02010dbc,

};

void *const data_02041934[36] = {

    (void *)func_020113a4,

    (void *)func_020113d0,

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

    (void *)func_020113fc,

    (void *)func_02011428,

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

    (void *)func_02011454,

    (void *)func_02011480,

    &GXS_LoadOAM,

    &GXS_LoadOBJ,

};
