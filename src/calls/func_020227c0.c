extern void func_02020888(int engine, int a, int b);
extern void func_02030d10(int id);
extern int func_02020a9c(void);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern char **data_0204be08;

/* Shuts the 3D subsystem down: blanks the three engines, stops the two effects (the second only
 * when it is not already gated) and frees the four buffers. */
void func_020227c0(void) {
    char *ctx = (char *)((void **)&data_0204be08)[1];
    func_02020888(0, 0, 0);
    func_02020888(1, 0, 0);
    func_02020888(2, 0, 0);
    func_02030d10(0x11);
    if ((func_02020a9c() & 2) == 0) {
        func_02030d10(0x12);
    }
    NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 0x9c));
    NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 0x10));
    NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 0x14));
    NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 0xc));
}
