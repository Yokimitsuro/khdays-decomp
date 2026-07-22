/* Uploads a main BG extended-palette block into the bank recorded at data_020446f0[4],
 * clipping the length against the slot's end recorded at data_020446f0[3]. */
extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];
extern char *data_020446f0[];

void GX_LoadBGExtPltt(const void *src, unsigned int offset, unsigned int len) {
    char *dst = data_020446f0[4] + offset;
    unsigned int n = (unsigned int)(dst - data_020446f0[3]);
    if (data_020422b8[0] != -1) {
        MI_DmaCopy32Async(data_020422b8[0], src, (void *)n, len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, (void *)n, len);
}
