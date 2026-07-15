/* NONMATCHING: CSE tie - retail recomputes the widget-pool address (heap+0x4bd8)
 * per call instead of holding it (our mwcc is -2 instr). Logic exact. For the port. */
/* func_ov000_02059200 -- allocate the 18 logo menu cursors, ov000. Builds cursor 4 and
 * 5 into heap[2]/heap[3], then cursors 6..21 into heap[4..19] via func_ov000_02055b48
 * over the widget pool @heap+0x4bd8. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *func_ov000_02055b48(void *pool, int id);
void func_ov000_02059200(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    int *base = h + 2;
    base[0] = (int)func_ov000_02055b48((char *)h + 0x4bd8, 4);
    base[1] = (int)func_ov000_02055b48((char *)h + 0x4bd8, 5);
    int i;
    for (i = 0; i < 16; i++) {
        base[i + 2] = (int)func_ov000_02055b48((char *)h + 0x4bd8, i + 6);
    }
}
