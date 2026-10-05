/* Chase tick. Steers toward the target every frame: it turns the horizontal
   distance into a Q12 approach factor, spreads the aim angle by a random amount
   that widens as the factor approaches zero, sets the turn rate from the frame
   delta, drives the movement vector from the current facing's sine and cosine,
   and retires the state with request 2 once the chase duration runs out.

   `+ (nFactor - nFactor)` on the RNG result is NOT a typo: RandNextScaled
   returns long long and that unfoldable zero is what emits the ROM's
   `add r0, r0, #0`. FX_Inv is the reloc's own name for 01ff8a04 even though it
   takes two arguments and divides. */

#include "nitro/types.h"
#include "game/ai_task.h"

typedef struct {
    int nX;
    int nY;
    int nZ;
} Vec3;

struct State {
    char *pActor;
    int nAngle04;
    int nAngleTarget08;
    char pad0c[4];
    Vec3 *pPos10;
    int nAngleStep14;
    char pad18[4];
    Vec3 vMove1c;
    char pad28[0];
    int nElapsed28;
    int nDuration2c;
};

struct Node {
    AI_TASK_FIELDS(struct State)
};

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int VEC_Normalize(const Vec3 *v, Vec3 *unit);
extern int FX_Div(int num, int den);
extern int RandNextScaled();
extern short FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const Vec3 *src, Vec3 *dst);
extern void SetIndexedSlot(struct Node *node, int slot, void *next);

extern const short data_0203d210[];

void Ov285_Chase_Tick(struct Node *node)
{
    struct State *st;
    Vec3 vToTarget;
    Vec3 vFacing;
    int nFactor;
    int nHalf;
    int nSpread;

    st = node->pState;
    VEC_Subtract((const Vec3 *)(st->pActor + 0x190), st->pPos10, &vToTarget);
    vToTarget.nY = 0;
    nFactor = VEC_Normalize(&vToTarget, &vToTarget);
    nFactor = FX_Div(nFactor, 0x14000);
    nFactor = nFactor * 2 - 0x1000;
    if (nFactor < -0x1000) {
        nFactor = -0x1000;
    }
    if (nFactor > 0x1000) {
        nFactor = 0x1000;
    }

    nHalf = 0x1000 - (nFactor < 0 ? -nFactor : nFactor);
    nSpread = nHalf * 2;
    if (nSpread < 0) {
        nSpread = -nSpread;
    }
    nSpread = (int)(((long long)(RandNextScaled(nSpread + 1) +
                                 (nFactor - nFactor) - nHalf) * 0x3244 +
                     0x800) >> 12);

    if (nFactor > 0) {
        st->nAngleTarget08 =
            (FX_Atan2(-vToTarget.nX, -vToTarget.nZ) + 0x3244) - nSpread;
    } else {
        st->nAngleTarget08 =
            nSpread + (FX_Atan2(vToTarget.nX, vToTarget.nZ) + 0x3244);
    }

    st->nAngleStep14 = (*(int *)((char *)node->pList + 0x2c) * 0x1e) / 10;

    {
        int nIdx = (u16)(int)(((long long)st->nAngle04 * 0x28be60db9391LL +
                              0x80000000000LL) >> 44) >> 4;

        vFacing.nX = data_0203d210[nIdx * 2];
        vFacing.nY = 0;
        vFacing.nZ = data_0203d210[nIdx * 2 + 1];
        ScaleVec3Fx12(0x400, &vFacing, &st->vMove1c);

        st->nElapsed28 += *(int *)((char *)node->pList + 0x2c);
        if (st->nElapsed28 <= st->nDuration2c) {
            return;
        }
        *(u8 *)(st->pActor + 0x1c7) = 2;
        SetIndexedSlot(node, node->slot, 0);
    }
}
