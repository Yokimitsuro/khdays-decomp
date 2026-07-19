extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);

extern void func_ov023_02089108(void *entity, int value);
extern void func_ov023_02089000(void *entity, int value);
extern void func_ov023_02089154(void *entity, int value);

/* Script command: marks the entity's transform dirty, then applies whichever variant the operand
 * tag selects. */
int func_ov023_02086bf8(int ctx, char *args) {
    char *entity = *(char **)(*(char **)(ctx + 0x128) + 0x440)
                   + func_02020d10(ctx, func_02021980(ctx, args)) * 0x1a64;
    *(int *)(entity + 0x1a28) |= 0x80;
    switch (*(short *)(args + 8)) {
    case 1:
        func_ov023_02089108(entity, func_02021980(ctx, args + 8));
        break;
    case 2: {
        int a = func_02021948(ctx, args + 8);
        int b = func_02021980(ctx, args + 0x10);
        if ((*(int *)(entity + 0x1a28) & 0x100) == 0) {
            func_ov023_02089000(entity, a);
        }
        func_ov023_02089154(entity, b);
        break;
    }
    }
    return 1;
}
