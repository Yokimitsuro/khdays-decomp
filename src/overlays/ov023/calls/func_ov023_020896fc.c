/* func_ov023_020896fc -- Ov023_InitNoiseOverlay: set up the event's noise overlay.  Its texture
 * "ev/tex_noise.nsbtx" is loaded (Ov023_LoadNoiseTexture 02089760 into the state block
 * data_ov023_0208a7c0 points at) and the 4 x 3 tile positions at the head of the block are
 * laid out on a 64-unit grid starting at 32 (as fx32). */
typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct Ov023NoiseState {
    Fx32Pair aTile[12];       /* 0x00: [row * 3 + column] */
} Ov023NoiseState;

extern void func_ov023_02089760(const char *pszTexture);           /* Ov023_LoadNoiseTexture */
extern char data_ov023_0208a75c[];                                  /* "ev/tex_noise.nsbtx" */
extern Ov023NoiseState *data_ov023_0208a7c0;                        /* the noise overlay state */

void func_ov023_020896fc(void)
{
    int i;
    int j;

    func_ov023_02089760(data_ov023_0208a75c);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            data_ov023_0208a7c0->aTile[i * 3 + j].x = (0x20 + i * 0x40) << 12;
            data_ov023_0208a7c0->aTile[i * 3 + j].y = (0x20 + j * 0x40) << 12;
        }
    }
}
