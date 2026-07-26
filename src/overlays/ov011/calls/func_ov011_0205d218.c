/* func_ov011_0205d218 -- push the scene's scroll values into the BG offset registers.
 *
 * BG1 on both engines gets a slow vertical scroll derived from a counter divided by 100;
 * BG2 and BG3 get their own x/y pairs, each written to two registers. A BG offset
 * register is one 32-bit write holding two 9-bit fields, horizontal low and vertical high,
 * which is why 0x01ff0000 sits in a register for the whole function -- mwcc reuses it for
 * the low field too by reading it back shifted right sixteen.
 *
 * The counter's contribution is written `(v << 24) >> 8`, not `(u8)v << 16`. The two are
 * the same value, but mwcc compiles the cast to `and #0xff` plus a shift, while the ROM
 * truncates with the shift pair. Every other line of the function is identical either way. */
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef signed short   s16;

typedef struct Ov011Scene {
    u8  pad_00000[0x10948];
    s16 nBg2X;
    s16 nBg2Y;
    u8  pad_1094c[0x21288 - 0x1094c];
    s16 nBg3X;
    s16 nBg3Y;
    u8  pad_2128c[0x23aac - 0x2128c];
    int nScrollTicks;
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;

void func_ov011_0205d218(void)
{
    *(volatile u32 *)0x04000014 =
        ((u32)(data_ov011_0205e960.pScene->nScrollTicks / 100) << 24 >> 8) & 0x01ff0000;
    *(volatile u32 *)0x04001014 =
        ((u32)(data_ov011_0205e960.pScene->nScrollTicks / 100) << 24 >> 8) & 0x01ff0000;
    *(volatile u32 *)0x04000018 =
        (data_ov011_0205e960.pScene->nBg2X & 0x1ff)
        | ((u32)data_ov011_0205e960.pScene->nBg2Y << 16 & 0x01ff0000);
    *(volatile u32 *)0x0400001c =
        (data_ov011_0205e960.pScene->nBg2X & 0x1ff)
        | ((u32)data_ov011_0205e960.pScene->nBg2Y << 16 & 0x01ff0000);
    *(volatile u32 *)0x04001018 =
        (data_ov011_0205e960.pScene->nBg3X & 0x1ff)
        | ((u32)data_ov011_0205e960.pScene->nBg3Y << 16 & 0x01ff0000);
    *(volatile u32 *)0x0400101c =
        (data_ov011_0205e960.pScene->nBg3X & 0x1ff)
        | ((u32)data_ov011_0205e960.pScene->nBg3Y << 16 & 0x01ff0000);
}
