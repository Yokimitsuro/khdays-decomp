/* Advances the finish-action motion and records the tick hook result in bit 1
 * of the byte at actor offset 0x694. On completion it wakes the actor node,
 * clears both motion accumulators, and returns the actor to mode 0 or mode 2.
 * The finish hook takes the actor and the zero mode value as two arguments.
 */typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1; unsigned char b1 : 1; } Flags694;
typedef int (*Hook)(int obj);
typedef void (*FinishHook)(int obj, int mode);

extern int func_02030788(void);
extern void func_ov022_0209fe20(int obj, Vec3 *out);
extern int VEC_Add(void *a, void *b, void *d);
extern void func_ov038_020b44a8(int obj);
extern void func_0202af1c(int p);
extern int func_ov022_020a35f4(int obj, int mode);

int func_ov038_020b4940(int obj) {
    Vec3 q;
    Vec3 v;
    int r = 0;
    int clear;

    if (func_02030788() == 0) {
        *(unsigned long long *)(obj + 0x464) |= 0x10000LL;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(obj + 0x46c) |= 0x10000LL;
    }
    func_ov022_0209fe20(obj, &q);
    if (q.y != 0) {
        *(int *)(obj + 0x58) = q.y;
    } else if ((*(unsigned int *)(obj + 0x24) & 4) == 0) {
        *(unsigned long long *)obj |= 0x400000000000LL;
        *(int *)(obj + 0x58) = 0;
    }
    v = q;
    v.y = 0;
    VEC_Add((Vec3 *)(obj + 0x498), &v, (Vec3 *)(obj + 0x498));
    func_ov038_020b44a8(obj);
    ((Flags694 *)(obj + 0x694))->b1 = (*(Hook *)(obj + 0x668))(obj);
    if (((Flags694 *)(obj + 0x694))->b1) {
        int p;
        *(unsigned long long *)obj |= 0x2000000000000LL;
        p = *(int *)(obj + 0x20);
        if ((*(unsigned int *)p & 0x20) == 0) {
            func_0202af1c(p + 4);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(obj + 0x464) |= 2LL;
        }
    }
    if (((Flags694 *)(obj + 0x694))->b1) {
        clear = 0;
        *(int *)(obj + 0x698) = *(int *)(obj + 0x69c) =
            *(int *)(obj + 0x6a0) = *(int *)(obj + 0x498) =
            *(int *)(obj + 0x49c) = *(int *)(obj + 0x4a0) = clear;
        *(unsigned long long *)obj |= 4LL;
        if ((*(unsigned int *)(obj + 0x24) & 4) != 0) {
            (*(FinishHook *)(obj + 0x664))(obj, clear);
            r = func_ov022_020a35f4(obj, 0);
        } else {
            r = func_ov022_020a35f4(obj, 2);
        }
    }
    return r;
}
