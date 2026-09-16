/* func_ov023_02087bc8 -- Ov023_ActorStepEffects: run an actor's effect timing for one frame.
 * Without flag bit 8 (+0x1a28) a plain timer counts (+0x454): every period (+4) frames the
 * effect of index +8 is spawned (Ov023_ActorSpawnEffect 02087a48) and the timer restarts.
 * Otherwise the motion state (+4) is advanced by the entity's speed (0202c6a8 on +0x1a38;
 * Ov023_MotionAdvance 02087b34): a unit speed advances once; any other speed advances once
 * when the new frame (0202aee0 on the entity's animation) lands on a whole frame, else one
 * whole frame at a time until a track fires or the whole frames are used up.  A firing track
 * spawns its effect. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u8   anim[0x20];          /* 0x04 */
} Ov023Entity;

typedef struct Ov023MotionState {  /* at +4 of the actor */
    int  nPeriod;             /* 0x000 (actor +4) */
    int  nEffect;             /* 0x004 (actor +8) */
    u8   pad_008[0x450 - 0x8];
    int  nTimer;              /* 0x450 (actor +0x454) */
} Ov023MotionState;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    Ov023MotionState motion;  /* 0x0004 */
    u8   pad_0458[0x15e0 - 0x458];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a28 - 0x15e4];
    int  nFlags;              /* 0x1a28 */
    u8   pad_1a2c[0x1a38 - 0x1a2c];
    int  nEntity;             /* 0x1a38 */
} Ov023Actor;

/* The remainder is the high half of the helper's long long return; writing `%` emits
 * _s32_div_f, which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern int  func_0202c6a8(u16 nEntity);                             /* Entity_GetSpeed */
extern int  func_ov023_02087b34(Ov023MotionState *pState, int nStep); /* Ov023_MotionAdvance */
extern int  func_0202aee0(void *pAnim, int nArg);                   /* Anim_GetFrame */
extern void func_ov023_02087a48(Ov023Actor *pActor, int nIndex);    /* Ov023_ActorSpawnEffect */

void func_ov023_02087bc8(Ov023Actor *pActor)
{
    int nResult;
    int nSpeed;
    int nFrame;
    int nNext;
    int nSteps;

    nResult = -1;
    if (pActor->nFlags & 0x100) {
        nSpeed = func_0202c6a8((u16)pActor->nEntity);
        if (nSpeed == 0x1000) {
            nResult = func_ov023_02087b34(&pActor->motion, nSpeed);
        } else {
            nFrame = func_0202aee0(pActor->pEntity->anim, 0);
            nNext = nFrame + nSpeed;
            nSteps = nNext / 0x1000 - nFrame / 0x1000;
            if (nNext % 0x1000 == 0) {
                nResult = func_ov023_02087b34(&pActor->motion, nSpeed);
            } else {
                while (nSteps > 0 && nResult == -1) {
                    nResult = func_ov023_02087b34(&pActor->motion, 0x1000);
                    nSteps--;
                }
            }
        }
        if (nResult != -1) {
            func_ov023_02087a48(pActor, nResult);
        }
    } else {
        if ((int)(func_02020400(pActor->motion.nTimer, pActor->motion.nPeriod) >> 32) == 0) {
            func_ov023_02087a48(pActor, pActor->motion.nEffect);
            pActor->motion.nTimer = 0;
        }
        pActor->motion.nTimer++;
    }
}
