/* func_ov023_02089c38 -- Ov023_DrawNoiseOverlay: draw the noise overlay for the frame.  Unless
 * a screen other than the top one is active (data_0204be04) with the other screen's flag set
 * (+0x60 of the noise state data_ov023_0208a7c0), the scroll (+0x70) advances by 0x4000 and
 * wraps at 0x10000; then the overlay's geometry state is set (Ov023_SetupNoiseDraw 02089880)
 * and the twelve tiles drawn (Ov023_DrawNoiseQuad 02089ae0). */
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

extern void func_ov023_02089880(void);                              /* Ov023_SetupNoiseDraw */
extern void func_ov023_02089ae0(Fx32Pair *pTile);                   /* Ov023_DrawNoiseQuad */
extern Ov023NoiseState *data_ov023_0208a7c0;                        /* the noise overlay state */
extern u8   data_0204be04;                                          /* the published active screen */

void func_ov023_02089c38(void)
{
    int i;

    if (data_0204be04 == 0 || data_ov023_0208a7c0->aFlag[data_0204be04 == 0] == 0) {
        data_ov023_0208a7c0->nScroll += 0x4000;
        if (data_ov023_0208a7c0->nScroll == 0x10000) {
            data_ov023_0208a7c0->nScroll = 0;
        }
    }
    func_ov023_02089880();
    for (i = 0; i < 12; i++) {
        func_ov023_02089ae0(&data_ov023_0208a7c0->aTile[i]);
    }
}
