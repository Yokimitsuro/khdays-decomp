extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern char *func_020218a4(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern void func_0202c3e4(unsigned short id, int a, void *out);
extern int FX_Atan2(int y, int x);
extern int func_ov023_02084a44(int ctx, int id, int angle);

typedef struct { int x, y, z; } Ov023Vec3;

/* Script command: turns the entity to face the point named by operand 1 -- either another
 * entity's position or a resolved world point. */
int func_ov023_02084ae8(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    char *op = func_020218a4(ctx, args + 8);
    int id = func_02020d10(ctx, entity);
    Ov023Vec3 here;
    Ov023Vec3 target;
    unsigned short angle;
    if (*(short *)op == 1) {
        target = *(Ov023Vec3 *)(func_0202bfcc((unsigned short)func_02020d10(ctx,
                     func_02021980(ctx, op))) + 0xa8);
    } else if (*(short *)op == 2) {
        func_0202c3e4((unsigned short)id, func_02021948(ctx, op), &target);
    } else {
        return 1;
    }
    here = *(Ov023Vec3 *)(func_0202bfcc((unsigned short)id) + 0xa8);
    here.x = target.x - here.x;
    here.z = target.z - here.z;
    angle = (unsigned short)(0x13fff - FX_Atan2(here.z, here.x));
    return func_ov023_02084a44(ctx, id, angle);
}
