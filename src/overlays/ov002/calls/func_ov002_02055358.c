extern void GX_LoadBGPltt(void *src, unsigned int offset, unsigned int size);
extern void GX_LoadBG3Char(void *src, unsigned int offset, unsigned int size);
extern int NNSi_FndFreeFromDefaultHeap(int block);
/* Upload the resource's palette (res+8) and BG3 character data (res+4) to VRAM, then release the
 * staging block if one was passed. */
void func_ov002_02055358(int block, int res) {
    GX_LoadBGPltt(*(void **)(*(int *)(res + 8) + 0xc), 0, *(unsigned int *)(*(int *)(res + 8) + 8));
    GX_LoadBG3Char(*(void **)(*(int *)(res + 4) + 0x14), 0, *(unsigned int *)(*(int *)(res + 4) + 0x10));
    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
}
