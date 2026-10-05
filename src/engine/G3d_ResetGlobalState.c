/* Resets the global scale, rotation and translation, flushes the cached commands and sends the
 * default color. */

typedef struct { int m[3][3]; } MtxFx33;

extern void MTX_Identity33_(MtxFx33 *mtx);
extern void GXi_FlushCommandList(void);
extern void GX_SendFifoWords(unsigned int cmd, const void *src, unsigned int words);
extern void NNS_G3dGlbFlush(void);

typedef struct {
    char pad_00[0xb8];
    int trans_x;   /* 0xb8 */
    int trans_y;   /* 0xbc */
    int trans_z;   /* 0xc0 */
    int scale_x;   /* 0xc4 */
    int scale_y;   /* 0xc8 */
    int scale_z;   /* 0xcc */
    char pad_d0[0x4];
    unsigned int flags; /* 0xd4 */
} GfxState;

extern GfxState NNS_G3dGlb;
extern MtxFx33  data_02047428;

void G3d_ResetGlobalState(void) {
    MtxFx33 m;
    int cmd_word;

    NNS_G3dGlb.scale_z = 0x1000;
    NNS_G3dGlb.scale_y = 0x1000;
    NNS_G3dGlb.scale_x = 0x1000;
    MTX_Identity33_(&m);
    MTX_Identity33_(&data_02047428);
    NNS_G3dGlb.trans_z = 0;
    NNS_G3dGlb.trans_y = 0;
    NNS_G3dGlb.trans_x = 0;
    NNS_G3dGlb.flags &= ~0xa4u;
    NNS_G3dGlbFlush();
    cmd_word = 0x7fff;
    GX_SendFifoWords(0x20, &cmd_word, 1);
    GXi_FlushCommandList();
}
