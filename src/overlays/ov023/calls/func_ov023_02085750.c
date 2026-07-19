extern int func_02021980(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

/* The script VM entity table: ctx->world->entities + id * sizeof(Entity). */

extern char *func_0202bfcc(int index);
extern void func_0202accc(void *dst, int kind, void *src, short value);

/* Script command: pushes operand 1 as a type-3 tween onto the entity from operand 0, unless the
 * entity resolves to the "none" handle. */
int func_ov023_02085750(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int value = func_02021980(ctx, (void *)(args + 8));
    int id = func_02020d10(ctx, entity);
    if (id != 0x40) {
        char *p = func_0202bfcc((unsigned short)id);
        func_0202accc(p + 4, 3, p + 0xe4, (short)value);
    }
    func_020219b4(ctx, args);
    return 0;
}
