extern void MIi_CpuCopy32(void *src, void *dst, int size);
extern char *data_ov002_0207fa14;
/* Copy the request's id (+0x10) and its 0x28-byte payload (+0x14) into the context, and stash the
 * low byte of its type (+2). */
void func_ov002_02074084(int req) {
    int ctx = (int)data_ov002_0207fa14;
    *(int *)(ctx + 0x98) = *(int *)(req + 0x10);
    MIi_CpuCopy32((void *)(req + 0x14), (void *)(ctx + 0x9c), 0x28);
    *(char *)(ctx + 0x11) = *(short *)(req + 2);
}
