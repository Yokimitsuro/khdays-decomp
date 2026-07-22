/* Uploads a sub BG extended-palette block: async DMA when a channel is configured, plain
 * CPU copy otherwise.  The destination is LCDC bank H (0x6898000). */
extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];

void GXS_LoadBGExtPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020422b8[0] != -1) {
        MI_DmaCopy32Async(data_020422b8[0], src, (void *)(offset + 0x98000 + 0x6800000), len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, (void *)(offset + 0x98000 + 0x6800000), len);
}
