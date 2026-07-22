/* Uploads a texture extended-palette block into the bank recorded at data_0204470c[2]. */
extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];
extern char *data_0204470c[];

void GX_LoadTexPltt(const void *src, unsigned int offset, unsigned int len) {
    char *base = data_0204470c[2];
    if (data_020422b8[0] != -1) {
        MI_DmaCopy32Async(data_020422b8[0], src, base + offset, len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, base + offset, len);
}
