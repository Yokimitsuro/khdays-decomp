/* main .rodata pointer tables, 0x02041fd4-0x0204208c.
 *
 * 4 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void func_02024030(void);
extern void func_0202405c(void);
extern void func_02024088(void);
extern void func_020240bc(void);
extern void func_020240f0(void);
extern void func_0202411c(void);
extern void func_02024148(void);
extern int G2S_GetBG0ScrPtr;
extern int G2S_GetBG1ScrPtr;
extern int G2S_GetBG2ScrPtr;
extern int G2S_GetBG3ScrPtr;
extern int G2_GetBG0ScrPtr;
extern int G2_GetBG1ScrPtr;
extern int G2_GetBG2ScrPtr;
extern int G2_GetBG3ScrPtr;
extern int GXS_LoadBG0Char;
extern int GXS_LoadBG0Scr;
extern int GXS_LoadBG1Char;
extern int GXS_LoadBG1Scr;
extern int GXS_LoadBG2Char;
extern int GXS_LoadBG2Scr;
extern int GXS_LoadBG3Char;
extern int GXS_LoadBG3Scr;
extern int GXS_LoadBGPltt;
extern int GX_LoadBG0Char;
extern int GX_LoadBG0Scr;
extern int GX_LoadBG1Char;
extern int GX_LoadBG1Scr;
extern int GX_LoadBG2Char;
extern int GX_LoadBG2Scr;
extern int GX_LoadBG3Char;
extern int GX_LoadBG3Scr;
extern int GX_LoadBGPltt;

void *const data_02041fd4[1] = {

    &G2_GetBG0ScrPtr,

};

void *const data_02041fd8[1] = {

    &GX_LoadBG0Scr,

};

void *const data_02041fdc[1] = {

    &GX_LoadBG0Char,

};

void *const data_02041fe0[43] = {

    &GX_LoadBGPltt,

    (void *)func_02024148,

    0,

    &G2_GetBG1ScrPtr,

    &GX_LoadBG1Scr,

    &GX_LoadBG1Char,

    &GX_LoadBGPltt,

    0,

    (void *)func_0202411c,

    &G2_GetBG2ScrPtr,

    &GX_LoadBG2Scr,

    &GX_LoadBG2Char,

    &GX_LoadBGPltt,

    0,

    (void *)func_020240f0,

    &G2_GetBG3ScrPtr,

    &GX_LoadBG3Scr,

    &GX_LoadBG3Char,

    &GX_LoadBGPltt,

    (void *)func_020240bc,

    0,

    &G2S_GetBG0ScrPtr,

    &GXS_LoadBG0Scr,

    &GXS_LoadBG0Char,

    &GXS_LoadBGPltt,

    (void *)func_02024088,

    0,

    &G2S_GetBG1ScrPtr,

    &GXS_LoadBG1Scr,

    &GXS_LoadBG1Char,

    &GXS_LoadBGPltt,

    0,

    (void *)func_0202405c,

    &G2S_GetBG2ScrPtr,

    &GXS_LoadBG2Scr,

    &GXS_LoadBG2Char,

    &GXS_LoadBGPltt,

    0,

    (void *)func_02024030,

    &G2S_GetBG3ScrPtr,

    &GXS_LoadBG3Scr,

    &GXS_LoadBG3Char,

    &GXS_LoadBGPltt,

};
