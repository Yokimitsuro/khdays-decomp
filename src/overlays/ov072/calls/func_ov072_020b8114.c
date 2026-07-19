typedef void (*Ov072Handler)(void);

extern unsigned char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov072_020b81b8(void *arg);
extern int func_0202a388(void *slot, int arg1, int seq_id, int arg3);
extern void func_ov022_020a4798(void *ctx, int a, int b);
extern void func_ov072_020b9874(void *ctx);
extern void func_ov022_0209fb24(void);

extern char data_ov072_020ba6e8[];

Ov072Handler func_ov072_020b8114(int *arg) {
    unsigned char *ctx;

    ctx = NNSi_FndGetCurrentRootHeap();
    ctx[0x2c30] &= ~1;
    ctx[0x2c30] &= ~4;
    func_ov072_020b81b8(arg);
    func_0202a388(ctx + 0x2e44, *(int *)(ctx + 0x20) + 4,
                  (int)data_ov072_020ba6e8, *arg + 7);
    func_ov022_020a4798(ctx, 0x43, 0xc5);
    func_ov072_020b9874(ctx);
    return func_ov022_0209fb24;
}
