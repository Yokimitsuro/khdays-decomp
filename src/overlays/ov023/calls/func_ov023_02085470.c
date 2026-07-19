extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);

extern void func_ov023_020895dc(void *entity, int a, int b);

/* Script command: three-operand entity call -- operands 2 and 1 in that read order. */
int func_ov023_02085470(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int b = func_02021980(ctx, (void *)(args + 0x10));
    int a = func_02021994(ctx, (void *)(args + 8));
    func_ov023_020895dc(*(char **)(*(char **)(ctx + 0x128) + 0x440)
                        + func_02020d10(ctx, entity) * 0x1a64, a, b);
    return 1;
}
