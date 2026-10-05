/* Tear the node's sub-objects down when its bit 0 is set and the byte at +0x135 is non-zero:
 * release the block at +0xb4, overwrite the 36-byte template at +0x144, clear bits 0xa4 in the
 * global state word, release the block at +0xa8, and run the two follow-ups.
 *
 * Parked over which register holds the pooled base of that read-modify-write. It was the
 * spelling of the global: `*(unsigned int *)((char *)&data + 0xd4)` puts the base and the value
 * in mwcc's preferred order, `data[0x35]` puts them in the original's. */
extern void NNS_G3dGlbSetBaseScale(unsigned int *p);
extern void MI_Copy36B(void *dst, void *src);
extern void NNS_G3dGlbSetBaseTrans(unsigned int *p);
extern void Gfx_ApplyBaseTransform(void);
extern void NNS_G3dDraw(unsigned int *p);
extern int data_02047428;
extern unsigned int NNS_G3dGlb[];

void Ov022_TearDownNode(unsigned char *node) {
    if ((*node & 1) != 0 && node[0x135] != 0) {
        NNS_G3dGlbSetBaseScale((unsigned int *)(node + 0xb4));
        MI_Copy36B((void *)(node + 0x144), &data_02047428);
        NNS_G3dGlb[0x35] &= ~0xa4;
        NNS_G3dGlbSetBaseTrans((unsigned int *)(node + 0xa8));
        Gfx_ApplyBaseTransform();
        NNS_G3dDraw((unsigned int *)(node + 0x24));
    }
}
