/* If the pending flag at heap+0x8d9e is set, clear it and return the deferred
 * handler func_ov002_02068720; otherwise return 0 (nothing pending). */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02068720(void);

int func_ov002_020686fc(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    if (*(unsigned char *)(heap + 0x8d9e) != 0) {
        *(unsigned char *)(heap + 0x8d9e) = 0;
        return (int)&func_ov002_02068720;
    }
    return 0;
}
