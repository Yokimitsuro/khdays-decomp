extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov063_020b5b14(int *ctx);
extern int func_0201ef9c(void *tbl, int n);
extern void func_0202a3cc(int a, int b, int c, int d);
extern void func_ov063_020b6fd0(int a, int b);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
extern unsigned char data_0204c240;
extern int data_ov063_020b7d14;

void *func_ov063_020b5a34(int *ctx) {
    int base = NNSi_FndGetCurrentRootHeap();
    func_ov063_020b5b14(ctx);
    if ((data_0204c240 & 4) == 0) {
        *(int *)(base + 0x2c50) = func_0201ef9c(&data_ov063_020b7d14, ctx[0] + 7);
        func_0202a3cc(base + 0x2c2c, *(int *)(base + 0x20) + 4,
                      *(int *)(base + 0x2c50), ctx[0] + 7);
        *(int *)(base + 0x6bc) = -1;
        (*(void (**)(int, int))(base + 0x664))(base, 0);
    }
    func_ov063_020b6fd0(base, base + 0x2ca8);
    func_ov022_020a4798(base, 0x50, 0xd1);
    return (void *)&func_ov022_0209fb24;
}
