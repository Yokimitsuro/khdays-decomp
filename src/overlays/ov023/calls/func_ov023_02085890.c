extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

extern int func_ov023_020858d0(int ctx, int args);

/* Script command: resolves operand 0 twice through the handle table, caches the result in the
 * operand block, and falls back to the default step when the action is not ready. */
int func_ov023_02085890(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int r;
    func_02021980(ctx, (void *)(args + 8));
    *(int *)(args + 4) = func_02020d10(ctx, func_02020d10(ctx, entity));
    r = func_ov023_020858d0(ctx, args);
    if (r == 0) {
        func_020219b4(ctx, args);
    }
    return r;
}
