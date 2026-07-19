extern int func_02021980(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

/* The script VM entity table: ctx->world->entities + id * sizeof(Entity). */

extern void func_ov023_020894c0(void *entity, int a, int b, int c, int d, int e);

/* Script command: starts the default motion on the entity from operand 0 with operand 1 as its
 * parameter. */
int func_ov023_02086a00(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int param = func_02021980(ctx, (void *)(args + 8));
    func_ov023_020894c0(*(char **)(*(char **)(ctx + 0x128) + 0x440)
                        + func_02020d10(ctx, entity) * 0x1a64, 0, -2, param, 0, 0);
    return 1;
}
