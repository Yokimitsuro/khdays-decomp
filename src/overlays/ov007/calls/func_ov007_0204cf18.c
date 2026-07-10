extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int level);
extern void func_ov007_0204ce94(void *root);
extern int func_ov007_0204cf7c(void);

/* Ramp the screen brightness up over 0x20 frames (level = frame/2 - 0x10); once
 * it saturates, snap to full, reset the counter and the pending-input word, drain
 * the input line, and return the next handler. */
int func_ov007_0204cf18(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int ret = 0;
    int frame = *(int *)(root + 0x20) + 1;

    *(int *)(root + 0x20) = frame;
    if (frame >= 0x20) {
        func_0201e374(0);
        *(int *)(root + 0x20) = 0;
        *(int *)(root + 0x70) = 0;
        func_ov007_0204ce94((void *)root);
        ret = (int)func_ov007_0204cf7c;
    } else {
        func_0201e374(frame / 2 - 0x10);
    }
    return ret;
}
