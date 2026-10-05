/* NNS_G3dGlbFlush (NitroSystem G3D): send the global state block NNS_G3dGlb -- its first word
 * is the packed command word, the next 0x34 words the projection, the camera, the material
 * colours, the polygon attributes, the viewport, the base transform and the texture parameter
 * -- then clear the block's two dirty bits in flag (+0xd4). */

extern void GX_SendFifoWords(unsigned int cmd, const void *src, unsigned int words);

struct G3dGlbBlock {
    unsigned int cmd;       /* +0x00: the packed command word */
    char _4[0xd0];
    unsigned int flag;      /* +0xd4 */
};

extern struct G3dGlbBlock NNS_G3dGlb;

void NNS_G3dGlbFlush(void)
{
    unsigned int *p = (unsigned int *)&NNS_G3dGlb;
    GX_SendFifoWords(*p, p + 1, 0x34);
    NNS_G3dGlb.flag &= ~1u;
    NNS_G3dGlb.flag &= ~2u;
}
