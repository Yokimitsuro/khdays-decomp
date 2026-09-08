/* Ov022_StepShot -- one frame of a shot in flight.
 *
 * The shot's clock takes the frame, its own step gives it a delta, and the delta
 * moves it. The hit pass then runs against where it has just arrived.
 *
 * A shot dies when it has flown further than its kind allows, and, unless its
 * kind holds it, when its clock passes the kind's life; a held kind runs its own
 * marshalling first and only expires once it has been released. Anything but a
 * live shot is finished off here: the state goes to spent, the clock is set to
 * the retire mark, the eight already-struck ids are cleared and the rig slots go
 * back.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ShotDesc */
struct ShotDesc {
    unsigned int nFlags;         /* 0x00 */
    u8 pad04[0x10];
    int nMaxDist;                /* 0x14 */
    int nMaxAge;                 /* 0x18 */
    u8 pad1c[0x20];
    int nField3c;                /* 0x3c */
};

/* Ov022Shot */
struct Shot {
    u8 nFlags;                   /* 0x000 */
    u8 pad001;
    s8 nState;                   /* 0x002 */
    u8 pad003;
    int nAge;                    /* 0x004 */
    u8 pad008[8];
    struct VecFx32 vecStart;     /* 0x010 */
    u8 pad01c[0xc];
    u16 nSlotFlags;              /* 0x028 */
    u8 pad02a[0xa2];
    struct VecFx32 vecPos;       /* 0x0cc */
    u8 pad0d8[0x60];
    struct ShotDesc *pDesc;      /* 0x138 */
    short aHitIds[8];            /* 0x13c */
};

struct ReactionCtx;

extern void func_ov022_0209198c(struct VecFx32 *pOut, struct ReactionCtx *pCtx,
                                struct Shot *pShot, int nDelta);
extern void VEC_Add(struct VecFx32 *pA, struct VecFx32 *pB,
                    struct VecFx32 *pOut);
extern void func_ov022_02091540(u16 *pFlags, int nDelta);
extern void func_ov022_02091b48(struct ReactionCtx *pCtx, struct Shot *pShot,
                                struct VecFx32 *pAt, struct VecFx32 *pDelta);
extern int func_01ff8e94(struct VecFx32 *pA, struct VecFx32 *pB);
extern void func_ov022_02091e08(struct ReactionCtx *pCtx, struct Shot *pShot);
extern void func_ov022_020914a0(struct Shot *pShot, int nRig);

#define SHOT_HELD 0x10
#define SHOT_RELEASED 1
#define SHOT_LIVE 2
#define SHOT_LANDED 3
#define SHOT_SPENT 4
#define RETIRE_MARK 0x3000
#define HIT_SLOTS 8

int func_ov022_020916e8(struct ReactionCtx *pCtx, struct Shot *pShot, int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDelta;
    struct ShotDesc *pDesc;
    int nSlot;

    pDesc = pShot->pDesc;
    pShot->nAge = pShot->nAge + nDelta;
    vecAt = pShot->vecPos;
    func_ov022_0209198c(&vecDelta, pCtx, pShot, nDelta);
    VEC_Add(&vecAt, &vecDelta, &vecAt);
    pShot->vecPos = vecAt;
    func_ov022_02091540(&pShot->nSlotFlags, nDelta);
    func_ov022_02091b48(pCtx, pShot, &vecAt, &vecDelta);
    if (pShot->nState != SHOT_LANDED
        && func_01ff8e94(&pShot->vecStart, &vecAt) > pDesc->nMaxDist) {
        pShot->nState = SHOT_SPENT;
    }
    if ((pDesc->nFlags & SHOT_HELD) != 0) {
        func_ov022_02091e08(pCtx, pShot);
        if ((pShot->nFlags & SHOT_RELEASED) != 0
            && pShot->nAge >= pDesc->nMaxAge) {
            pShot->nState = SHOT_SPENT;
        }
    } else {
        if (pShot->nAge >= pDesc->nMaxAge) {
            pShot->nState = SHOT_SPENT;
        }
    }
    if (pShot->nState != SHOT_LIVE) {
        pShot->nState = SHOT_SPENT;
        pShot->nAge = RETIRE_MARK;
        nSlot = 0;
        do {
            pShot->aHitIds[nSlot] = -1;
            nSlot++;
        } while (nSlot < HIT_SLOTS);
        func_ov022_020914a0(pShot, pDesc->nField3c);
    }
    return 0;
}
