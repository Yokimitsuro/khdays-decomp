/* Uploads a sub OBJ extended-palette block: async DMA when a channel is configured, plain
 * CPU copy otherwise. */
extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];

void GXS_LoadOBJExtPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020422b8[0] != -1) {
        MI_DmaCopy32Async(data_020422b8[0], src, (void *)(offset + 0x8a0000 + 0x6000000), len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, (void *)(offset + 0x8a0000 + 0x6000000), len);
}
