extern int func_02021980(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern void func_0202accc(void *dst, int kind, void *src, short value);

extern void func_ov023_020846bc(int ctx, char *args, int id, int *kind, char *name);
extern void func_ov023_02089390(void *entity, char *name, int kind, int a, int b);
extern void func_0202ad74(void *dst, unsigned short a, void *src, short value, int b);

/* Script command: plays the named motion on a spawned entity, or falls back to driving the
 * graphics node directly when the entity is not spawned. */
int func_ov023_02084780(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    int a = func_02021980(ctx, args + 8);
    int b = func_02021980(ctx, args + 0x20);
    int kind = -1;
    char name[0x40];
    int id = func_02020d10(ctx, entity);
    char *tbl = *(char **)(*(char **)(ctx + 0x128) + 0x440);
    if (tbl != 0 && *(int *)(tbl + id * 0x1a64 + 0x15e0) != 0) {
        name[0] = 0;
        func_ov023_020846bc(ctx, args, id, &kind, name);
        func_ov023_02089390(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64,
                            name, kind, a, b);
    } else {
        char *node = func_0202bfcc((unsigned short)id);
        kind = func_02021980(ctx, args + 0x18);
        func_0202ad74(node + 4, (unsigned short)a, node + 0xe4, (short)kind, b);
    }
    return 1;
}
