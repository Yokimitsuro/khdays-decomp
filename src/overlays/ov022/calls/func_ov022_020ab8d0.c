/* Ov022_StepChargeState -- run one frame of the charge state: turn the charge
 * with the aim while the input flag is up, then decide whether the state is
 * over.
 *
 * With input bit 2 held: any of the buttons 0xc03 or a new aim angle (other
 * than -1) counts as a change and is remembered as the last aim; a change
 * bumps the turn count and, with no turn pending, takes the aim angle (or a
 * random one when the aim is -1) as the new heading. Without it the recoil
 * sentinel 0x80000000 is cleared and flag bit 46 raised under flag bit 36 with
 * flag-2 bit 7. Charge kind 3 keeps the state: with input bit 2 a changed
 * heading is stored (biased by 0x8000) as a pending turn and used now, or a
 * pending turn is consumed; a live heading adds a 0x133 step along it to
 * vecStep. The state's own post-draw step then answers whether it is over.
 * Any other kind ends into state 5 (flag bit 36 with flag-2 bit 7) or 4.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Actor;

typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Charge */
/* Ov022Charge: the charge kinds overload +0x08..+0x18 (Ghidra names them from the
 * deal-count view: nCount, nAccum, nEntry, nHeld); this state uses them as turn state. */
struct Charge {
    signed char nKnockdownKind;  /* 0x00 */
    u8 pad01[3];
    int nMeter;                  /* 0x04 */
    int nTurnCount;              /* 0x08 */
    u8 pad0c[4];
    int nTurnAngle;              /* 0x10 */
    int nLastAim;                /* 0x14 */
    int bTurnPending;            /* 0x18 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[0x10];
    u16 nButtons;                /* 0x0018 */
    u8 pad001a[0xa];
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x2c];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x1c4];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[0x20db];
    struct Charge charge;        /* 0x2770 */
    u8 pad278c[0x330];
    int nAimAngle;               /* 0x2abc */
};

#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG2_BIT7 (1ULL << 7)
#define INPUT_BIT2 0x4
#define TURN_BUTTONS 0xc03
#define AIM_NONE (-1)
#define RECOIL_SENTINEL 0x80000000
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define TURN_SPEED 0x133
#define CHARGE_KIND_TURN 3
#define STATE_END 4
#define STATE_END_ALT 5

extern short data_0203d210[];               /* sin, cos pairs by angle >> 4 */

extern int func_020307f4(int nRange);                                          /* Session_RandNextScaled */
extern int func_ov022_0209bd04(struct Actor *pActor);                          /* Ov022_GetChargeKind */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

/* Byte-exact only with copy propagation off for this function (as Ov022_ShapeMotionDelta): with
 * it on, build 139 forwards the two negated trig values into their fixed-point multiplies, where
 * the ROM keeps them as separate temporaries (-cos in ip). Restored after the function. */
#pragma push
#pragma opt_propagation off
int func_ov022_020ab8d0(struct Actor *pActor)
{
    VecFx32 vecDir;
    VecFx32 vecFlat;
    int nRet;
    struct Charge *pCharge;
    int bChanged;
    int nNewAngle;
    int nAim;
    int nAngle;
    int nTrig;
    int nSinNeg;
    int nCosNeg;

    nRet = 0;
    pCharge = &pActor->charge;
    bChanged = 0;
    nNewAngle = AIM_NONE;
    if ((pActor->nInputMask & INPUT_BIT2) != 0) {
        if ((pActor->nButtons & TURN_BUTTONS) != 0) {
            bChanged = 1;
        }
        nAim = pActor->nAimAngle;
        if (nAim != AIM_NONE && pCharge->nLastAim != nAim) {
            bChanged = 1;
        }
        pCharge->nLastAim = nAim;
        if (bChanged) {
            pCharge->nTurnCount++;
            if (pCharge->bTurnPending == 0) {
                nNewAngle = pActor->nAimAngle;
                if (nNewAngle == AIM_NONE) {
                    nNewAngle = func_020307f4(0xffff);
                }
            }
        }
    } else {
        if (pActor->nRecoil == RECOIL_SENTINEL) {
            pActor->nRecoil = 0;
        }
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            pActor->nFlags |= FLAG_BIT46;
        }
    }
    if (func_ov022_0209bd04(pActor) != CHARGE_KIND_TURN) {
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            nRet = func_ov022_020a35f4(pActor, STATE_END_ALT);
        } else {
            nRet = func_ov022_020a35f4(pActor, STATE_END);
        }
    } else {
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            nAngle = AIM_NONE;
            if (bChanged && nNewAngle != AIM_NONE) {
                pCharge->nTurnAngle = (u16)(nNewAngle + ANGLE_BIAS);
                pCharge->bTurnPending = 1;
                nAngle = nNewAngle;
            } else if (pCharge->bTurnPending != 0) {
                nAngle = pCharge->nTurnAngle;
                pCharge->bTurnPending = 0;
            }
            if (nAngle >= 0) {
                nTrig = (nAngle >> ANGLE_STEP) * 2;
                nSinNeg = -data_0203d210[nTrig];
                nCosNeg = -data_0203d210[nTrig + 1];
                vecDir.x = (int)(((long long)nSinNeg * TURN_SPEED + 0x800) >> 12);
                vecDir.y = 0;
                vecDir.z = (int)(((long long)nCosNeg * TURN_SPEED + 0x800) >> 12);
                vecFlat = vecDir;
                vecFlat.y = 0;
                VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
            }
        }
        pActor->bStateOver = pActor->pfnPostDraw(pActor);
    }
    return nRet;
}
#pragma pop
