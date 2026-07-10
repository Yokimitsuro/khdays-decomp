/* NONMATCHING: register-coloring tie. The 5 loop index/pointer locals of the
 * nested 4x3 loop rotate through r4-r8 differently than the original. Structure
 * identical (76B). Calls func_ov022_020b10c8 over heap+0x10, 4 rows x 3 (0xa8/0x38). */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020b10c8(unsigned char *arg0);
int func_ov022_020b102c(void) {
    unsigned char *outer = (unsigned char *)(NNSi_FndGetCurrentRootHeap() + 0x10);
    int a = 0;
    do {
        unsigned char *inner = outer;
        int b = 0;
        do { func_ov022_020b10c8(inner); b++; inner += 0x38; } while (b < 3);
        a++; outer += 0xa8;
    } while (a < 4);
    return 0;
}
