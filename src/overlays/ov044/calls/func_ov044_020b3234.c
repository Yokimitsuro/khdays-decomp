extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov044_020b3314(int *ctx);
extern int func_0201ef9c(void *tbl, int n);
extern void func_0202a3cc(int a, int b, int c, int d);
extern void func_ov044_020b47d0(int a, int b);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
extern unsigned char data_0204c240;
extern int data_ov044_020b5514;

void *func_ov044_020b3234(int *ctx) {
    int base = NNSi_FndGetCurrentRootHeap();
    func_ov044_020b3314(ctx);
    if ((data_0204c240 & 4) == 0) {
        *(int *)(base + 0x2c50) = func_0201ef9c(&data_ov044_020b5514, ctx[0] + 7);
        func_0202a3cc(base + 0x2c2c, *(int *)(base + 0x20) + 4,
                      *(int *)(base + 0x2c50), ctx[0] + 7);
        *(int *)(base + 0x6bc) = -1;
        (*(void (**)(int, int))(base + 0x664))(base, 0);
    }
    func_ov044_020b47d0(base, base + 0x2ca8);
    func_ov022_020a4798(base, 0x50, 0xd1);
    return (void *)&func_ov022_0209fb24;
}
