extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern int func_02020af0(void *world, int name);
extern int func_0201f468(int a, void *b, int c);
extern void func_0202b984(unsigned short id, int a, int b, int c);
extern void func_020219b4(int ctx, int arg);

/* Script command: same as func_02022670 but always yields afterwards, passing the negated entity
 * id (or the "no entity" sentinel) as the resume key. */
int func_02022578(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    int name = func_02021948(ctx, args + 8);
    int id = func_02020d10(ctx, entity);
    char *world = *(char **)(ctx + 0x128);
    if (func_0201f468(func_02020af0(world, name), world + 0x28, 0) != 0) {
        func_0202b984((unsigned short)id, *(int *)(*(char **)(ctx + 0x128) + 0x28), 0, 0);
        if (id == 0) {
            func_020219b4(ctx, ~0x62);
        } else {
            func_020219b4(ctx, -id);
        }
    } else {
        func_020219b4(ctx, id);
    }
    return 0;
}
