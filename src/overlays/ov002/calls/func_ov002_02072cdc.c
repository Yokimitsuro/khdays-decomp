/*
 * Puts the entry table back to empty.
 *
 * The held token goes to none, the two blocks that need wiping are cleared -
 * one to zero, one to the empty id - and the scalar block between them is
 * zeroed a field at a time, with the sub-table reset dropped in the middle
 * where the original makes its call. Then the slot arrays are filled with
 * their empty markers, bytes and ids together, and each of the four rows is
 * marked unused.
 *
 * The second cleared region overlaps the last row, so both cleared blocks are
 * addressed by offset rather than through a field.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002Row {
    s8 nKind;
    char pad01[9];
} Ov002Row;

typedef struct Ov002Ctx {
    char pad00[0x11];
    u8 nFlag11;
    char pad12[6];
    int nToken18;
    char pad1c[0x20];
    char pad3c[8];
    int n44;
    u8 b48;
    u8 b49;
    char pad4a[2];
    int n4c;
    u8 b50;
    u8 b51;
    u8 b52;
    u8 b53;
    u8 b54;
    u8 aBytes[8];
    char pad5d[1];
    u16 aHalves[8];
    char pad6e[8];
    Ov002Row aRows[4];
} Ov002Ctx;

extern Ov002Ctx *data_ov002_0207fa14;

extern void INITi_CpuClear32_0x01ff86fc(u32 nValue, void *pDest, u32 nSize);
extern void MIi_CpuClear16(u16 nValue, void *pDest, u32 nSize);
extern void func_ov002_020743e4(void);

void func_ov002_02072cdc(void)
{
    Ov002Ctx *pCtx;
    int i;
    int j;

    pCtx = data_ov002_0207fa14;
    pCtx->nToken18 = -1;
    INITi_CpuClear32_0x01ff86fc(0, pCtx->pad1c, 0x20);
    MIi_CpuClear16(0xffff, pCtx->pad3c, 8);

    pCtx->n44 = 0;
    pCtx->b48 = 0;
    pCtx->b49 = 0;
    pCtx->n4c = 0;
    pCtx->b50 = 0;
    pCtx->b51 = 0;
    func_ov002_020743e4();
    pCtx->b52 = 0;
    pCtx->b53 = 0;
    pCtx->b54 = 0;
    INITi_CpuClear32_0x01ff86fc(0, (char *)pCtx + 0x9c, 0x28);
    pCtx->nFlag11 = 0;

    for (i = 0; i < 8; i++) {
        pCtx->aHalves[i] = 0xffff;
        pCtx->aBytes[i] = 0xff;
    }

    for (j = 0; j < 4; j++) {
        pCtx->aRows[j].nKind = -1;
    }
}
