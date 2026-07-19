extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);

extern void func_ov023_020846bc(int ctx, int args, int id, int *kind, char *name);
extern void func_ov023_020894c0(void *entity, char *name, int kind, int a, int b, int c);

/* Script command: resolves the motion name and kind for the entity, then starts it. */
int func_ov023_020853f8(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int a = func_02021980(ctx, (void *)(args + 8));
    int b = func_02021980(ctx, (void *)(args + 0x20));
    int kind = -1;
    char name[0x40];
    int id = func_02020d10(ctx, entity);
    name[0] = 0;
    func_ov023_020846bc(ctx, args, id, &kind, name);
    func_ov023_020894c0(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64,
                        name, kind, a, b, 0);
    return 1;
}
