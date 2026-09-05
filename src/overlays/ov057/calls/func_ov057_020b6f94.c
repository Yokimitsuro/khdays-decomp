typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef int (*ActorHook)(int pActor);
typedef void (*ActorFinishHook)(int pActor, int mode);

extern int func_02030788(void);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov022_02095524(void *state);
extern int func_ov022_020a35f4(int pActor, int mode);
extern int data_ov057_020b74a0;

/* Ticks the charge phase, then either advances to mode 0x22 or clears both
 * motion vectors and finishes the actor once its charge sequence ends. */
int func_ov057_020b6f94(int pActor)
{
    Vec3 zero;
    Vec3 delta;

    int pSceneBlock = data_ov057_020b74a0 + 0x2c + 0x2c00;
    int result = 0;
    int actionEnded = 0;
    int zeroValue;


    if (func_02030788() == 0) {
        *(u64 *)(pActor + 0x464) |= 0x10000ULL;
    }
    if (func_02030788() == 0) {
        *(u64 *)(pActor + 0x46c) |= 0x10000ULL;
    }

    zero.x = zero.y = zero.z = 0;
    if ((*(u32 *)(pActor + 0x24) & 4) == 0) {
        *(u64 *)pActor |= 0x400000000000ULL;
        *(int *)(pActor + 0x58) = 0;
    }

    delta = zero;
    delta.y = 0;
    VEC_Add((Vec3 *)(pActor + 0x498), &delta,
            (Vec3 *)(pActor + 0x498));
    (*(ActorHook *)(pActor + 0x668))(pActor);

    if ((*(u16 *)(pActor + 0x1a) & 1) == 0) {
        actionEnded = 1;
    }
    if (func_ov022_02095524((void *)(pActor + 0x22f8)) == 0 || actionEnded) {
        if (*(int *)(pSceneBlock + 0x228) > 1) {
            result = func_ov022_020a35f4(pActor, 0x22);
        } else {
            zeroValue = 0;
            *(int *)(pActor + 0x698) = *(int *)(pActor + 0x69c) =
                *(int *)(pActor + 0x6a0) = *(int *)(pActor + 0x498) =
                *(int *)(pActor + 0x49c) = *(int *)(pActor + 0x4a0) = zeroValue;
            *(u64 *)pActor |= 4ULL;
            if ((*(u32 *)(pActor + 0x24) & 4) != 0) {
                (*(ActorFinishHook *)(pActor + 0x664))(pActor, zeroValue);
                result = func_ov022_020a35f4(pActor, 0);
            } else {
                result = func_ov022_020a35f4(pActor, 2);
            }
        }
    }
    return result;
}