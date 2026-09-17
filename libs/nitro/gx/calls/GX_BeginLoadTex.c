/* NitroSDK gx_load3d.c: GX_BeginLoadTex -- release the texture banks to LCDC and record, from
 * sTexStartAddrTable, the LCDC addresses of the (up to two) blocks the bank mask maps to and the
 * size of the first one. The symbol map calls GX_ResetBankForTex "SNDi_UnlockMutex". */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int GXVRamTex;

extern GXVRamTex SNDi_UnlockMutex(void);   /* GX_ResetBankForTex */
#define GX_ResetBankForTex SNDi_UnlockMutex

/* gx_load3d.c's texture start table (data_02041428): blk1 / blk2 / szBlk1, each >> 12. */
extern const struct {
    u16 blk1;
    u16 blk2;
    u16 szBlk1;
} data_02041428[16];
#define sTexStartAddrTable data_02041428

/* gx_load3d.c statics, one .bss block (data_0204470c): the texture / texture-palette upload state. */
extern struct {
    u32 pad0;                     /* 0x00 */
    u32 sTexLCDCBlk1;             /* 0x04 */
    u32 sTexPlttLCDCBlk;          /* 0x08 */
    int sTexPltt;                 /* 0x0c */
    u32 pad10;                    /* 0x10 */
    GXVRamTex sTex;               /* 0x14 */
    u32 sTexLCDCBlk2;             /* 0x18 */
    u32 sSzTexBlk1;               /* 0x1c */
} data_0204470c;
#define sTexLCDCBlk1 data_0204470c.sTexLCDCBlk1
#define sTex data_0204470c.sTex
#define sTexLCDCBlk2 data_0204470c.sTexLCDCBlk2
#define sSzTexBlk1 data_0204470c.sSzTexBlk1

void GX_BeginLoadTex(void)
{
    sTex = GX_ResetBankForTex();

    sTexLCDCBlk1 = (u32)(sTexStartAddrTable[sTex].blk1 << 12);
    sTexLCDCBlk2 = (u32)(sTexStartAddrTable[sTex].blk2 << 12);
    sSzTexBlk1 = (u32)(sTexStartAddrTable[sTex].szBlk1 << 12);
}
