extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(int index);

extern void func_02016d10(int anim, int a);
extern void func_02016cd0(int anim, int a);

typedef struct { int x, y, z; } Ov023Vec3;

/* Script command: zeroes the Y component of the entity node's offset vector and restarts its
 * animation. */
int func_ov023_020860b4(int ctx, int args) {
    char *node = func_0202bfcc((unsigned short)func_02020d10(ctx, func_02021980(ctx, (void *)args)));
    Ov023Vec3 v;
    v.x = *(int *)(node + 0xb4);
    v.y = 0;
    v.z = *(int *)(node + 0xbc);
    *(Ov023Vec3 *)(node + 0xb4) = v;
    func_02016d10(*(int *)(node + 0x7c), 8);
    func_02016cd0(*(int *)(node + 0x7c), 0x3f);
    return 1;
}
