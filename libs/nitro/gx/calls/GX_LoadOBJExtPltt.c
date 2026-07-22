/* Uploads a main OBJ extended-palette block into the bank recorded at data_020446f0[1]. */
extern void MI_DmaCopy32Async(int ch, const void *src, void *dst, unsigned int len, void *cb, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int len);
extern int data_020422b8[];
extern char *data_020446f0[];

void GX_LoadOBJExtPltt(const void *src, unsigned int offset, unsigned int len) {
    char *base = data_020446f0[1];
    if (data_020422b8[0] != -1) {
        MI_DmaCopy32Async(data_020422b8[0], src, base + offset, len, 0, 0);
        return;
    }
    MIi_CpuCopy32(src, base + offset, len);
}
