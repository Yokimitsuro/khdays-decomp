/* main .rodata pointer tables, 0x02041fd4-0x0204208c.
 *
 * 4 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void PackDisplayReg0x400100e(void);
extern void PackDisplayReg0x400100c(void);
extern void Bg_WriteSubBg1Cnt(void);
extern void Bg_WriteSubBg0Cnt(void);
extern void PackDisplayReg0x400000e(void);
extern void PackDisplayReg0x400000c(void);
extern void Bg_WriteMainBg1Cnt(void);
extern void G2S_GetBG0ScrPtr(void);
extern void G2S_GetBG1ScrPtr(void);
extern void G2S_GetBG2ScrPtr(void);
extern void G2S_GetBG3ScrPtr(void);
extern void G2_GetBG0ScrPtr(void);
extern void G2_GetBG1ScrPtr(void);
extern void G2_GetBG2ScrPtr(void);
extern void G2_GetBG3ScrPtr(void);
extern void GXS_LoadBG0Char(void);
extern void GXS_LoadBG0Scr(void);
extern void GXS_LoadBG1Char(void);
extern void GXS_LoadBG1Scr(void);
extern void GXS_LoadBG2Char(void);
extern void GXS_LoadBG2Scr(void);
extern void GXS_LoadBG3Char(void);
extern void GXS_LoadBG3Scr(void);
extern void GXS_LoadBGPltt(void);
extern void GX_LoadBG0Char(void);
extern void GX_LoadBG0Scr(void);
extern void GX_LoadBG1Char(void);
extern void GX_LoadBG1Scr(void);
extern void GX_LoadBG2Char(void);
extern void GX_LoadBG2Scr(void);
extern void GX_LoadBG3Char(void);
extern void GX_LoadBG3Scr(void);
extern void GX_LoadBGPltt(void);

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

    (void *)Bg_WriteMainBg1Cnt,

    0,

    &G2_GetBG1ScrPtr,

    &GX_LoadBG1Scr,

    &GX_LoadBG1Char,

    &GX_LoadBGPltt,

    0,

    (void *)PackDisplayReg0x400000c,

    &G2_GetBG2ScrPtr,

    &GX_LoadBG2Scr,

    &GX_LoadBG2Char,

    &GX_LoadBGPltt,

    0,

    (void *)PackDisplayReg0x400000e,

    &G2_GetBG3ScrPtr,

    &GX_LoadBG3Scr,

    &GX_LoadBG3Char,

    &GX_LoadBGPltt,

    (void *)Bg_WriteSubBg0Cnt,

    0,

    &G2S_GetBG0ScrPtr,

    &GXS_LoadBG0Scr,

    &GXS_LoadBG0Char,

    &GXS_LoadBGPltt,

    (void *)Bg_WriteSubBg1Cnt,

    0,

    &G2S_GetBG1ScrPtr,

    &GXS_LoadBG1Scr,

    &GXS_LoadBG1Char,

    &GXS_LoadBGPltt,

    0,

    (void *)PackDisplayReg0x400100c,

    &G2S_GetBG2ScrPtr,

    &GXS_LoadBG2Scr,

    &GXS_LoadBG2Char,

    &GXS_LoadBGPltt,

    0,

    (void *)PackDisplayReg0x400100e,

    &G2S_GetBG3ScrPtr,

    &GXS_LoadBG3Scr,

    &GXS_LoadBG3Char,

    &GXS_LoadBGPltt,

};
