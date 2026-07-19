extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);

extern void func_ov023_0208929c(void *entity, int a, int b, int mode, int extra);

/* Script command: five-operand entity call. Mode 1 ignores the last operand. */
int func_ov023_02086dcc(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    int a = func_02021980(ctx, args + 8);
    int b = func_02021980(ctx, args + 0x10);
    int mode = func_02021980(ctx, args + 0x18);
    int extra = func_02021980(ctx, args + 0x20);
    int id = func_02020d10(ctx, entity);
    if (mode == 1) {
        func_ov023_0208929c(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64,
                            a, b, mode, 0);
    } else {
        func_ov023_0208929c(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64,
                            a, b, mode, extra);
    }
    return 1;
}
