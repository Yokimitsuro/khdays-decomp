/* ov022: turn the actor's drift into this frame's step, and decay it.
 *
 * Drift below a floor is not worth carrying, so it is dropped outright and the
 * step comes back as nothing.
 *
 * Otherwise the step is the drift with its vertical set aside: only the
 * horizontal part is capped, at a speed the actor cannot exceed however hard it
 * was pushed. One input bit halves both the step and the drift again, and the
 * vertical is put back untouched either way -- falling is never capped and
 * never slowed.
 *
 * The drift itself is decayed at the end, whatever happened to the step.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define DRIFT_FLOOR 0x200
#define STEP_CAP 0x900
#define SLOW_SCALE 0x333
#define DRIFT_DECAY 0xc80
#define SLOW_BIT 2

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x24];
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x454];
    struct VecFx32 vecDrift;     /* 0x047c */
};

extern int VEC_Mag(const struct VecFx32 *pA);
/* VEC_Normalize */
extern int func_01ff8d18(const struct VecFx32 *pSrc, struct VecFx32 *pDst);
/* scale a vector */
extern void func_01ffa724(int nScale, const struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);

void func_ov022_02097e14(struct Actor *pActor, struct VecFx32 *pOut)
{
    struct VecFx32 vecStep;
    int nFall;

    if (VEC_Mag(&pActor->vecDrift) <= DRIFT_FLOOR) {
        pActor->vecDrift.z = 0;
        pActor->vecDrift.y = 0;
        pActor->vecDrift.x = 0;
        pOut->z = 0;
        pOut->y = 0;
        pOut->x = 0;
        return;
    }
    vecStep = pActor->vecDrift;
    nFall = vecStep.y;
    vecStep.y = 0;
    if (VEC_Mag(&vecStep) > STEP_CAP) {
        func_01ff8d18(&vecStep, &vecStep);
        func_01ffa724(STEP_CAP, &vecStep, &vecStep);
    }
    if ((pActor->nInputMask & SLOW_BIT) != 0) {
        func_01ffa724(SLOW_SCALE, &vecStep, &vecStep);
        func_01ffa724(SLOW_SCALE, &pActor->vecDrift, &pActor->vecDrift);
    }
    vecStep.y = nFall;
    *pOut = vecStep;
    func_01ffa724(DRIFT_DECAY, &pActor->vecDrift, &pActor->vecDrift);
}
