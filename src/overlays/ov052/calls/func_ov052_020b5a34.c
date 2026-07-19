typedef void (*Ov052Handler)(void);

extern unsigned char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov052_020b5ad8(void *arg);
extern int func_0202a388(void *slot, int arg1, int seq_id, int arg3);
extern void func_ov022_020a4798(void *ctx, int a, int b);
extern void func_ov052_020b7194(void *ctx);
extern void func_ov022_0209fb24(void);

extern char data_ov052_020b8008[];

Ov052Handler func_ov052_020b5a34(int *arg) {
    unsigned char *ctx;

    ctx = NNSi_FndGetCurrentRootHeap();
    ctx[0x2c30] &= ~1;
    ctx[0x2c30] &= ~4;
    func_ov052_020b5ad8(arg);
    func_0202a388(ctx + 0x2e44, *(int *)(ctx + 0x20) + 4,
                  (int)data_ov052_020b8008, *arg + 7);
    func_ov022_020a4798(ctx, 0x43, 0xc5);
    func_ov052_020b7194(ctx);
    return func_ov022_0209fb24;
}
