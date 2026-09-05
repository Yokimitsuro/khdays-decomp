typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef int (*ActorHook)(int actor);
typedef void (*ActorFinishHook)(int actor, int mode);

extern int func_02030788(void);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov022_02095524(void *state);
extern int func_ov022_020a35f4(int actor, int mode);
extern int data_ov038_020b4ca0;

int func_ov038_020b4794(int actor)
{
    Vec3 zero;
    Vec3 delta;

    int scene = data_ov038_020b4ca0 + 0x2c + 0x2c00;
    int result = 0;
    int canFinish = 0;
    int clear;


    if (func_02030788() == 0) {
        *(u64 *)(actor + 0x464) |= 0x10000ULL;
    }
    if (func_02030788() == 0) {
        *(u64 *)(actor + 0x46c) |= 0x10000ULL;
    }

    zero.x = zero.y = zero.z = 0;
    if ((*(u32 *)(actor + 0x24) & 4) == 0) {
        *(u64 *)actor |= 0x400000000000ULL;
        *(int *)(actor + 0x58) = 0;
    }

    delta = zero;
    delta.y = 0;
    VEC_Add((Vec3 *)(actor + 0x498), &delta,
            (Vec3 *)(actor + 0x498));
    (*(ActorHook *)(actor + 0x668))(actor);

    if ((*(u16 *)(actor + 0x1a) & 1) == 0) {
        canFinish = 1;
    }
    if (func_ov022_02095524((void *)(actor + 0x22f8)) == 0 || canFinish) {
        if (*(int *)(scene + 0x228) > 1) {
            result = func_ov022_020a35f4(actor, 0x22);
        } else {
            clear = 0;
            *(int *)(actor + 0x698) = *(int *)(actor + 0x69c) =
                *(int *)(actor + 0x6a0) = *(int *)(actor + 0x498) =
                *(int *)(actor + 0x49c) = *(int *)(actor + 0x4a0) = clear;
            *(u64 *)actor |= 4ULL;
            if ((*(u32 *)(actor + 0x24) & 4) != 0) {
                (*(ActorFinishHook *)(actor + 0x664))(actor, clear);
                result = func_ov022_020a35f4(actor, 0);
            } else {
                result = func_ov022_020a35f4(actor, 2);
            }
        }
    }
    return result;
}