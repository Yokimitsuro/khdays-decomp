/* Uploads a sub OBJ palette block: DMA when one is configured and the block is big enough, plain CPU
 * copy otherwise. */
extern void MI_DmaCopy16(int ch, const void *src, void *dst, unsigned int len);
extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];

void GXS_LoadOBJPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020422b8[0] != -1 && len > 0x1c) {
        MI_DmaCopy16(data_020422b8[0], src, (void *)(offset + 0x600 + 0x5000000), len);
        return;
    }
    MIi_CpuCopy16(src, (void *)(offset + 0x600 + 0x5000000), len);
}
