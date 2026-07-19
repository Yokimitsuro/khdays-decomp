extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(int index);

extern void func_ov023_02088f08(void *entity, int a, int b);

/* Script command: two-parameter entity call, operand 1 read through the float accessor. */
int func_ov023_02085edc(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int a = func_02021948(ctx, (void *)(args + 8));
    int b = func_02021980(ctx, (void *)(args + 0x10));
    func_ov023_02088f08(*(char **)(*(char **)(ctx + 0x128) + 0x440)
                        + func_02020d10(ctx, entity) * 0x1a64, a, b);
    return 1;
}
