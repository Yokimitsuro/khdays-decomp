extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern void func_020219b4(int ctx, int args);

extern void func_0202b850(unsigned short id, int a, int b, void *param, int e);

typedef struct { int mode; int arg1; int arg0; int pad1; int pad2; } Ov023MotionParam;

/* Script command: starts the entity's motion. Operands 1 and 2 select the variant; with both zero
 * the motion runs with no parameter block at all. */
int func_ov023_02084108(int ctx, int args) {
    int id = func_02020d10(ctx, func_02021980(ctx, (void *)args));
    int arg0 = func_02021994(ctx, (void *)(args + 8));
    int arg1 = func_02021994(ctx, (void *)(args + 0x10));
    Ov023MotionParam p;
    Ov023MotionParam *pp = &p;
    if (arg1 == 0) {
        if (arg0 == 0) {
            pp = 0;
        } else {
            p.mode = 2;
            p.arg0 = arg0;
        }
    } else {
        p.mode = 0;
        p.arg0 = arg0;
        p.arg1 = arg1;
    }
    func_0202b850((unsigned short)id, 0, 0, pp, 0);
    return 1;
}
