/* func_ov023_020890ac -- Ov023_ActorStartEffectTimer: start the timed effect of an actor.  The
 * state's word at +0x454 (actor +0x458) is cleared; the period (+4) becomes half the entity
 * animation's length in frames (0202aef8 on +0x15e0, divided by the entity speed 0202c6a8 on
 * +0x1a38), the effect index (+8) the mapped kind (Ov023_MapEffectIndex 02089080), the timer
 * (+0x454) -1, and the first frame is run at once (Ov023_ActorStepEffects 02087bc8). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u8   anim[0x20];          /* 0x04 */
} Ov023Entity;

typedef struct Ov023MotionState {  /* at +4 of the actor */
    int  nPeriod;             /* 0x000 */
    int  nEffect;             /* 0x004 */
    u8   pad_008[0x450 - 0x8];
    int  nTimer;              /* 0x450 */
    int  nAlternate;          /* 0x454 */
} Ov023MotionState;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    Ov023MotionState motion;  /* 0x0004 */
    u8   pad_045c[0x15e0 - 0x45c];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a38 - 0x15e4];
    int  nEntity;             /* 0x1a38 */
} Ov023Actor;

extern int  func_0202aef8(void *pAnim, int nTrack);                 /* Anim_GetLengthQ12 */
extern int  func_0202c6a8(u16 nEntity);                             /* Entity_GetSpeed */
extern int  func_02020400(int nNumerator, int nDenominator);        /* the 64-bit divide, low word */
extern int  func_ov023_02089080(int nKind);                         /* Ov023_MapEffectIndex */
extern void func_ov023_02087bc8(Ov023Actor *pActor);                /* Ov023_ActorStepEffects */

void func_ov023_020890ac(Ov023Actor *pActor, int nKind)
{
    Ov023MotionState *pState;

    pState = &pActor->motion;
    pState->nAlternate = 0;
    pActor->motion.nPeriod = func_02020400(func_0202aef8(pActor->pEntity->anim, 0), func_0202c6a8((u16)pActor->nEntity)) / 2;
    pState->nEffect = func_ov023_02089080(nKind);
    pState->nTimer = -1;
    func_ov023_02087bc8(pActor);
}
