/* Idle tick: sets the +0x48 rate to 30/10 of the frame step and re-acquires the lock-on target
 * into +0x24 (none: pose request 2, dispatch null). The +0x38 aim pose faces the target
 * (flattened, data_02042258 when degenerate). The +0x4c bob phase advances by 30 x frame step,
 * wrapping at 60.0; its sine (FX_Mul by 0x6488, /60, RadToIdx into data_0203d210) halved plus the
 * actor radius (+0x80) and 0.25 above the target's +0x78 height is the hover target, eased into
 * +0x10 by a tenth while the +0x13c height is valid. The surface gap decides the next pose:
 * with the +0x6c wait spent, 6 beyond 3.5 else 7; otherwise 6 beyond 8.0 or 7 within 1.0. */

#include "game/engine.h"

struct v3 { int x, y, z; };

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_Normalize(void *v, void *out);
extern fx16  FX_Atan2(int x, int z);
extern struct v3 data_02042258;
extern int  data_02042264;
extern const short data_0203d210[];

void Ov273_IdleTick(int *self) {
    int actor;
    int target;
    int owner;
    int *state = (int *)self[1];
    struct v3 dir;
    struct v3 unit;
    int d;
    int zero = 0;

    owner = *state;
    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 10;
    target = state[9] = Ov107_FindNearestObject(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    actor = *state;
    VEC_Subtract((void *)(target + 0x74), (void *)(actor + 0x74), &dir);
    dir.y = 0;
    if (VEC_Normalize(&dir, &unit) == 0) {
        unit = data_02042258;
    }
    QuatFromAxisAngle((void *)(state + 0xe), &data_02042264, FX_Atan2(unit.x, unit.z));
    state[0x13] += *(int *)(self[0] + 0x2c) * 30;
    if (state[0x13] >= 0x3c000) state[0x13] = 0;
    {
        unsigned short idx = FX_RadToIdx(FX_Mul(state[0x13], 0x6488) / 60);
        int h = *(int *)(target + 0x78) + (*(int *)(actor + 0x80) + data_0203d210[(idx >> 4) << 1] / 2) + 0x400;
        if (*(int *)(owner + 0x13c) != zero - 0x80000001) { /* 0x7fffffff built from a zero local: ROM `sub r0, r3, #0x80000001` */
            state[4] += (h - *(int *)(owner + 0x13c)) / 10;
        }
    }
    d = VEC_Normalize(&dir, &dir) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    if (d < 0) d = 0;
    if (state[0x1b] <= 0) {
        if (d > 0x3800) {
            *(unsigned char *)(*state + 0x1c7) = 6;
            SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 7;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    if (d > 0x8000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    if (d < 0x1000) {
        *(unsigned char *)(*state + 0x1c7) = 7;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
