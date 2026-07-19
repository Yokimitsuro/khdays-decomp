extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

extern char *func_0202bfcc(int index);
extern void func_01fff774(void *p, int slot, int value);

/* Script command: writes operand 2 into slot (operand 1) of the entity from operand 0. */
int func_ov023_020862e8(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int slot = func_02021980(ctx, (void *)(args + 8));
    int value = func_02021994(ctx, (void *)(args + 0x10));
    func_01fff774(func_0202bfcc((unsigned short)func_02020d10(ctx, entity)) + 4,
                  (unsigned short)slot, value);
    return 1;
}
