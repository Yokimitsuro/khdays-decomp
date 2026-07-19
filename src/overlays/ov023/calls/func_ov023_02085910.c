extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);

typedef struct { int x, y, z; } Ov023Vec3;

/* Script command: sets the entity node's scale. A scalar operand scales all three axes; a vector
 * operand (tag non-zero) takes one component per axis. */
int func_ov023_02085910(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    int value = func_02021994(ctx, args + 8);
    char *node = func_0202bfcc((unsigned short)func_02020d10(ctx, entity));
    if (*(short *)(args + 0x10) == 0) {
        *(int *)(node + 0xbc) = value;
        *(int *)(node + 0xb8) = *(int *)(node + 0xbc);
        *(int *)(node + 0xb4) = *(int *)(node + 0xb8);
    } else {
        Ov023Vec3 v;
        v.x = value;
        v.y = func_02021994(ctx, args + 0x10);
        v.z = func_02021994(ctx, args + 0x18);
        *(Ov023Vec3 *)(node + 0xb4) = v;
    }
    return 1;
}
