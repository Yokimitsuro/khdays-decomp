/* Clone the blit descriptor's header and give the copy its own zeroed parameter
 * block, sized from the tile count at 32 bytes per tile.
 *
 * The size is worked out BEFORE the header copy, and the freshly stored block
 * pointer is read back out of the destination for the clear rather than reused
 * from the allocation -- both are what the ROM does. */
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int size, int align);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int value, void *dest,
                                        unsigned int size);

typedef struct {
    void *pSrc;                 /* +0 */
    unsigned short wStride;     /* +4 */
    unsigned char bWidth;       /* +6 */
    unsigned char bHeight;      /* +7 */
    void *pParams;              /* +8 */
} Ov002BlitDesc;

void func_ov002_0206675c(Ov002BlitDesc *dest, const Ov002BlitDesc *src) {
    int size = (src->bWidth * src->bHeight) << 5;

    dest->pSrc = src->pSrc;
    dest->wStride = src->wStride;
    dest->bWidth = src->bWidth;
    dest->bHeight = src->bHeight;

    dest->pParams = NNS_FndAllocFromDefaultExpHeapEx(size, 4);
    INITi_CpuClear32_0x01ff86fc(0, dest->pParams, size);
}
