extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

extern void func_ov023_02089174(void *entity);

/* Script command: looks the entity up from operand 0 and runs the action on it. */
int func_ov023_02086508(int ctx, int args) {
    int id = func_02020d10(ctx, func_02021980(ctx, (void *)args));
    func_ov023_02089174(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64);
    return 1;
}
