extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int level);
extern int func_ov007_0204d31c(void);

/* Per-frame brightness ramp-DOWN (level = -frame/2) over 0x20 frames; once it
 * bottoms out, hold at -0x10 and return the next handler. */
int func_ov007_0204d2d0(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int ret = 0;
    int frame = *(int *)(root + 0x20) + 1;

    *(int *)(root + 0x20) = frame;
    if (frame >= 0x20) {
        func_0201e374(-0x10);
        ret = (int)func_ov007_0204d31c;
    } else {
        func_0201e374(-frame / 2);
    }
    return ret;
}
