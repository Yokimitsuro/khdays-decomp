extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);

extern void func_0202beb8(int id, int on);
extern void func_ov023_02089274(void *entity, int on);

/* Script command: toggles the entity's visibility both on its graphics node and, when it is
 * actually spawned, on the entity itself. */
int func_ov023_0208449c(int ctx, int args) {
    int id = func_02020d10(ctx, func_02021980(ctx, (void *)args));
    char *tbl;
    func_0202beb8((unsigned short)id, 1);
    tbl = *(char **)(*(char **)(ctx + 0x128) + 0x440);
    if (tbl != 0) {
        char *entity = tbl + id * 0x1a64;
        if (*(int *)(entity + 0x15e0) != 0) {
            func_ov023_02089274(entity, 1);
        }
    }
    return 1;
}
