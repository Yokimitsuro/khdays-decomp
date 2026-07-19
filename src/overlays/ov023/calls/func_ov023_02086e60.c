extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_0202c68c(int index, int value);

/* Script command: resolves the entity from operand 0 and stores operand 1 into its slot. */
int func_ov023_02086e60(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int value = func_02021994(ctx, (void *)(args + 8));
    func_0202c68c((unsigned short)func_02020d10(ctx, entity), value);
    return 1;
}
