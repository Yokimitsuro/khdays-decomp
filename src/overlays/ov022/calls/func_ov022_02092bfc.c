/* Ov022_StepSpinEffect -- one frame of the effect that spins down and rests.
 *
 * Nothing runs unless the effect is on. While it is either resting or spinning
 * its hold counter runs down and stops at zero.
 *
 * Resting only spends the rest counter and reports nothing to draw. Both start
 * states arm the spin, one of them setting the spin's full angle first. Spinning
 * takes a fixed share of the frame off the angle; once the angle is spent the
 * effect drops back to resting with a fresh rest counter.
 *
 * Anything still running is placed: turned to face backwards along the caller's
 * angle when asked, moved to the caller's point, and handed to the model with
 * whatever angle is left as a whole number.
 */

typedef unsigned char u8;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct MtxFx33 {
    int m[9];
};

struct Effect {
    u8 nFlags;                       /* 0x000 */
    u8 pad001[0x7b];
    int nModel;                      /* 0x07c */
    u8 pad080[0x28];
    struct VecFx32 vecAt;            /* 0x0a8 */
    u8 pad0b4[0x81];
    u8 nState;                       /* 0x135 */
    u8 pad136[0xe];
    struct MtxFx33 mtx;              /* 0x144 */
    int nSpin;                       /* 0x168 */
    u8 pad16c[4];
    int nHold;                       /* 0x170 */
    int nRest;                       /* 0x174 */
};

/* Two signed halfwords per angle step: the sine first, then the cosine. */
extern short data_0203d210[];

extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void func_02016d10(int nModel, int nAngle);

#define EFFECT_ON 1
#define STATE_RESTING 0
#define STATE_ARM_FULL 1
#define STATE_ARM 2
#define STATE_SPINNING 3
#define SPIN_FULL 0x16000
#define SPIN_RATE 0x1800
#define REST_TIME 0x3000

void func_ov022_02092bfc(struct Effect *pEffect, struct VecFx32 *pAt, int nAngle,
                         int bTurn, int nDelta)
{
    int bAlive;
    int nStep;
    int nIndex;

    bAlive = 1;
    if ((pEffect->nFlags & EFFECT_ON) == 0) {
        return;
    }
    if (pEffect->nState == STATE_SPINNING || pEffect->nState == STATE_RESTING) {
        if (pEffect->nHold > 0) {
            pEffect->nHold = pEffect->nHold - nDelta;
        }
        if (pEffect->nHold < 0) {
            pEffect->nHold = 0;
        }
    }
    switch (pEffect->nState) {
    case STATE_RESTING:
        if (pEffect->nRest > 0) {
            pEffect->nRest = pEffect->nRest - nDelta;
        }
        if (pEffect->nRest < 0) {
            pEffect->nRest = 0;
        }
        bAlive = 0;
        break;
    case STATE_ARM_FULL:
        pEffect->nSpin = SPIN_FULL;
        pEffect->nState = STATE_SPINNING;
        break;
    case STATE_ARM:
        pEffect->nState = STATE_SPINNING;
        break;
    case STATE_SPINNING:
        nStep = (int)(((long long)nDelta * SPIN_RATE + 0x800) >> 12);
        if (pEffect->nSpin > nStep) {
            pEffect->nSpin = pEffect->nSpin - nStep;
        } else {
            pEffect->nState = STATE_RESTING;
            pEffect->nSpin = 0;
            pEffect->nRest = REST_TIME;
        }
        break;
    }
    if (bAlive == 0) {
        return;
    }
    if (bTurn != 0) {
        nIndex = nAngle >> 4;
        MTX_RotY33_(&pEffect->mtx, -data_0203d210[nIndex * 2],
                    -data_0203d210[nIndex * 2 + 1]);
    }
    pEffect->vecAt = *pAt;
    func_02016d10(pEffect->nModel, pEffect->nSpin >> 12);
}
