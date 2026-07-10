extern int func_ov022_020882f8(void);
extern int data_ov022_020b2e78;

unsigned int func_ov022_0208848c(void) {
    unsigned int acc = 0;
    int base = *(int *)((char *)&data_ov022_020b2e78 + 4);
    int n;
    int i;
    int w;
    if (base == 0) return 0;
    n = func_ov022_020882f8();
    i = 0;
    if (0 < n) {
        do {
            int e = *(int *)(base + 4);
            i = i + 1;
            base = base + 0xc;
            w = *(short *)(*(int *)(e + 0x20) + 0x66);
            if (w >= 0) {
                acc = acc | 1 << w;
            }
        } while (i < n);
    }
    return acc;
}
