extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(int index);

extern void func_02033d0c(int a, int b, void *vec, int d);

typedef struct { int x, y, z; } Ov023Vec3;

/* Script command: runs the world action from operands 0/1 at the position of the entity named by
 * operand 2. */
int func_ov023_02086f18(int ctx, int args) {
    int a = func_02021980(ctx, (void *)args);
    int b = func_02021980(ctx, (void *)(args + 8));
    char *node = func_0202bfcc((unsigned short)func_02020d10(ctx,
                     func_02021980(ctx, (void *)(args + 0x10))));
    Ov023Vec3 pos = *(Ov023Vec3 *)(node + 0xa8);
    func_02033d0c(a, b, &pos, 0);
    return 1;
}
