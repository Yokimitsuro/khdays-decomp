extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);

extern void func_0202bf84(unsigned short id);
extern void func_ov023_020848b8(int ctx, char *args, int id, void *out);
extern void func_ov023_020891e4(void *entity, void *out, int a, int b);
extern int func_ov023_02088ee8(void *entity, int on);

typedef struct { int a, b, c; } Ov023Spawn;

/* Script command: spawns the entity's follower at the resolved transform and enables or disables
 * its automatic update depending on the trailing operand. */
int func_ov023_02084994(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    int a = func_02021980(ctx, args + 0x38);
    int b = func_02021994(ctx, args + 0x28);
    int id;
    Ov023Spawn out;
    func_02021994(ctx, args + 0x30);
    id = func_02020d10(ctx, entity);
    func_0202bf84((unsigned short)id);
    func_ov023_020848b8(ctx, args, id, &out);
    func_ov023_020891e4(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, &out, b, a);
    if (*(short *)(args + 0x40) != 0) {
        return func_ov023_02088ee8(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, 0);
    }
    return func_ov023_02088ee8(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, 1);
}
