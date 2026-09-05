/* Advances the finish-action motion and records the tick hook result in bit 1
 * of the byte at actor offset 0x694. On completion it wakes the actor node,
 * clears both motion accumulators, and returns the actor to mode 0 or mode 2.
 * The finish hook takes the actor and the zero mode value as two arguments.
 */typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1; unsigned char b1 : 1; } Flags694;
typedef int (*Hook)(int pActor);
typedef void (*FinishHook)(int pActor, int mode);

extern int func_02030788(void);
extern void func_ov022_0209fe20(int pActor, Vec3 *out);
extern int VEC_Add(void *a, void *b, void *d);
extern void func_ov057_020b6ca8(int pActor);
extern void func_0202af1c(int pNode);
extern int func_ov022_020a35f4(int pActor, int mode);

int func_ov057_020b7140(int pActor) {
    Vec3 motionSample;
    Vec3 motionDelta;
    int result = 0;
    int zeroValue;

    if (func_02030788() == 0) {
        *(unsigned long long *)(pActor + 0x464) |= 0x10000LL;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(pActor + 0x46c) |= 0x10000LL;
    }
    func_ov022_0209fe20(pActor, &motionSample);
    if (motionSample.y != 0) {
        *(int *)(pActor + 0x58) = motionSample.y;
    } else if ((*(unsigned int *)(pActor + 0x24) & 4) == 0) {
        *(unsigned long long *)pActor |= 0x400000000000LL;
        *(int *)(pActor + 0x58) = 0;
    }
    motionDelta = motionSample;
    motionDelta.y = 0;
    VEC_Add((Vec3 *)(pActor + 0x498), &motionDelta, (Vec3 *)(pActor + 0x498));
    func_ov057_020b6ca8(pActor);
    ((Flags694 *)(pActor + 0x694))->b1 = (*(Hook *)(pActor + 0x668))(pActor);
    if (((Flags694 *)(pActor + 0x694))->b1) {
        int pNode;
        *(unsigned long long *)pActor |= 0x2000000000000LL;
        pNode = *(int *)(pActor + 0x20);
        if ((*(unsigned int *)pNode & 0x20) == 0) {
            func_0202af1c(pNode + 4);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(pActor + 0x464) |= 2LL;
        }
    }
    if (((Flags694 *)(pActor + 0x694))->b1) {
        zeroValue = 0;
        *(int *)(pActor + 0x698) = *(int *)(pActor + 0x69c) =
            *(int *)(pActor + 0x6a0) = *(int *)(pActor + 0x498) =
            *(int *)(pActor + 0x49c) = *(int *)(pActor + 0x4a0) = zeroValue;
        *(unsigned long long *)pActor |= 4LL;
        if ((*(unsigned int *)(pActor + 0x24) & 4) != 0) {
            (*(FinishHook *)(pActor + 0x664))(pActor, zeroValue);
            result = func_ov022_020a35f4(pActor, 0);
        } else {
            result = func_ov022_020a35f4(pActor, 2);
        }
    }
    return result;
}
