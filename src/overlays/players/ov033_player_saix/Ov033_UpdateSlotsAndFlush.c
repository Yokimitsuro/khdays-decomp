/* Draws the character's effect block while the owner is shown: the six secondary slots, then the
 * main effect when it is active. */

extern void Ov033_DispatchWhenStateActive(int a);
extern void NNS_G3dGlbFlush(void);
extern void GX_SendFifoWords(int a, int b, int c);
extern void NNS_G3dDraw(int a);

typedef struct { unsigned char b0 : 1; } Flags;

void Ov033_UpdateSlotsAndFlush(int self, int blk) {
    int i;
    char *p;
    if (!((Flags *)(self + 0x694))->b0) return;
    p = (char *)(blk + 0x118);
    for (i = 0; i < 6; i++, p += 0x110) {
        Ov033_DispatchWhenStateActive((int)p);
    }
    if (*(int *)blk != 1) return;
    NNS_G3dGlbFlush();
    GX_SendFifoWords(0x17, blk + 0x8c, 0xc);
    NNS_G3dDraw(blk + 0x2c);
}
