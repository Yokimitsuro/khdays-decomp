/* Uploads a sub OAM block: DMA when one is configured and the block is big enough, plain CPU
 * copy otherwise. */
extern void MI_DmaCopy32(int ch, const void *src, void *dst, unsigned int len);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];

void GXS_LoadOAM(const void *src, unsigned int offset, unsigned int len) {
    if (data_020422b8[0] != -1 && len > 0x30) {
        MI_DmaCopy32(data_020422b8[0], src, (void *)(offset + 0x400 + 0x7000000), len);
        return;
    }
    MIi_CpuCopy32(src, (void *)(offset + 0x400 + 0x7000000), len);
}
