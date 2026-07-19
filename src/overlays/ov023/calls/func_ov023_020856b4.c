extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);

extern void func_ov023_02089304(void *entity, int a, int *vec, int b, int c);

/* Script command: seven operands -- three of them are angles scaled by 0xb6 (degrees to the
 * engine's 1/65536-turn units) and passed as a vector. */
int func_ov023_020856b4(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    int x = func_02021980(ctx, args + 0x10);
    int y = func_02021980(ctx, args + 0x18);
    int z = func_02021980(ctx, args + 0x20);
    int a = func_02021980(ctx, args + 0x28);
    int b = func_02021980(ctx, args + 0x30);
    int c = func_02021948(ctx, args + 8);
    int id = func_02020d10(ctx, entity);
    int angles[3];
    angles[0] = x * 0xb6;
    angles[1] = y * 0xb6;
    angles[2] = z * 0xb6;
    func_ov023_02089304(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64,
                        c, angles, a, b);
    return 1;
}
