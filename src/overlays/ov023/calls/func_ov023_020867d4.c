extern int func_02021980(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

/* The script VM entity table: ctx->world->entities + id * sizeof(Entity). */

extern void func_ov023_02089370(void *entity, int on);

/* Script command: turns a flag on the entity from operand 0 on or off from operand 1. */
int func_ov023_020867d4(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int on;
    if (func_02021980(ctx, (void *)(args + 8)) != 0) {
        on = 1;
    } else {
        on = 0;
    }
    func_ov023_02089370(*(char **)(*(char **)(ctx + 0x128) + 0x440)
                        + func_02020d10(ctx, entity) * 0x1a64, on);
    return 1;
}
