/* func_ov106_020b8990 -- Ov106_DrawNoiseOverlay: draw the noise overlay for the frame.  Unless
 * a screen other than the top one is active (data_0204be04) with the other screen's flag set
 * (+0x60 of the noise state data_ov106_020b8b68), the scroll (+0x70) advances by 0x4000 and
 * wraps at 0x10000; then the overlay's geometry state is set (Ov023_SetupNoiseDraw 02089880)
 * and the twelve tiles drawn (Ov023_DrawNoiseQuad 02089ae0).
 * PROVENANCE: byte-identical twin of ov023's Ov023_DrawNoiseOverlay (func_ov023_02089c38), same code and
 * pool layout in the ov106 event scene; the ov023 source is the analysed one. */
typedef unsigned char  u8;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct Ov023NoiseState {
    Fx32Pair aTile[12];       /* 0x00 */
    int  aFlag[2];            /* 0x60 */
    int  aLight[2];           /* 0x68 */
    int  nScroll;             /* 0x70 */
} Ov023NoiseState;

extern void func_ov106_020b85d8(void);                              /* Ov023_SetupNoiseDraw */
extern void func_ov106_020b8838(Fx32Pair *pTile);                   /* Ov023_DrawNoiseQuad */
extern Ov023NoiseState *data_ov106_020b8b68;                        /* the noise overlay state */
extern u8   data_0204be04;                                          /* the published active screen */

void func_ov106_020b8990(void)
{
    int i;

    if (data_0204be04 == 0 || data_ov106_020b8b68->aFlag[data_0204be04 == 0] == 0) {
        data_ov106_020b8b68->nScroll += 0x4000;
        if (data_ov106_020b8b68->nScroll == 0x10000) {
            data_ov106_020b8b68->nScroll = 0;
        }
    }
    func_ov106_020b85d8();
    for (i = 0; i < 12; i++) {
        func_ov106_020b8838(&data_ov106_020b8b68->aTile[i]);
    }
}
