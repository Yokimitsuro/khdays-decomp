/* In its visible states, uploads the effect's bone matrix, scale and matrix to the geometry FIFO
 * and runs its animation channels. */

extern void MI_Copy48B(int dst, int src);
extern void GX_SendFifoWords(int a, void *b, int c);
extern void NNS_G3dGlbFlush(void);
extern void NNS_G3dDraw(int a);

void Ov077_UploadBoneMatrices(int self, int *blk) {
    int tmp[3];
    if (*blk != 2 && *blk != 3) return;
    MI_Copy48B(self + 0x158 + 0x400, (int)blk + 0x84);
    {
        int v = *(int *)(blk[10] + 0x1c);
        tmp[0] = v;
        tmp[1] = v;
        tmp[2] = v;
        GX_SendFifoWords(0x1b, tmp, 3);
    }
    NNS_G3dGlbFlush();
    GX_SendFifoWords(0x17, (void *)((int)blk + 0x84), 0xc);
    NNS_G3dDraw((int)blk + 0x24);
}
