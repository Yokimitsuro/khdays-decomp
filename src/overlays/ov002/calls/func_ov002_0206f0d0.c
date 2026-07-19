extern char *NNSi_FndGetCurrentRootHeap(void);
extern void INITi_CpuClear32_0x01ff86fc(int value, void *dst, int size);
extern int func_02030694(void);
extern char *data_ov002_0207fa08;
extern void func_ov002_0206f124(void);
extern void func_ov002_0206f1ec(void);

/* Allocates the state block for sub-scene 9 out of the root heap, seeds it from the
 * caller's config and picks the first tick depending on whether the load started. */
void *func_ov002_0206f0d0(int *cfg) {
    char *st = NNSi_FndGetCurrentRootHeap();
    *(char **)&data_ov002_0207fa08 = st;
    *(int *)st = 9;
    *(int *)(st + 0xc) = *cfg;
    *(int *)(st + 0x10) = 0;
    *(int *)(st + 0x14) = 0;
    INITi_CpuClear32_0x01ff86fc(0, st + 0x18, 8);
    if (func_02030694() != 0) {
        return (void *)&func_ov002_0206f124;
    }
    return (void *)&func_ov002_0206f1ec;
}
