/* Queue the descriptor's blit: the source at +0, its parameter block at +8, and
 * two byte counts -- the row stride at +4 and the tile count (+6 times +7) --
 * both scaled by 32 bytes per tile. */
extern void GFXi_EnqueueCommand(void *src, int strideBytes, void *params,
                                int sizeBytes);

typedef struct {
    void *pSrc;                 /* +0 */
    unsigned short wStride;     /* +4 */
    unsigned char bWidth;       /* +6 */
    unsigned char bHeight;      /* +7 */
    void *pParams;              /* +8 */
} Ov002BlitDesc;

void func_ov002_02066820(Ov002BlitDesc *self) {
    GFXi_EnqueueCommand(self->pSrc, self->wStride << 5, self->pParams,
                        (self->bWidth * self->bHeight) << 5);
}
