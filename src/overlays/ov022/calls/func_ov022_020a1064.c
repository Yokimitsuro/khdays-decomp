/* ov022: run the frame's other three command handlers, then the fallback.
 *
 * The same shape as the first pipeline: three handlers get the same arguments
 * and any yes is the answer, and only when all three pass does the fallback get
 * a turn. Where this one differs is what it hands the last handler: the command
 * carries two points and the handler wants the vector between them, so it is
 * worked out on the stack first.
 *
 * The hit slot is cleared up front so a handler that does not fill it cannot
 * leave the previous frame's answer behind.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

struct Command {
    struct Vec3 vecFrom;         /* 0x00 */
    struct Vec3 vecTo;           /* 0x0c */
};

struct Actor {
    u8 pad0000[0x26bc];
    int nHit;                    /* 0x26bc */
    int nHitKind;                /* 0x26c0 */
    u8 bHitHeld;                 /* 0x26c4 */
};

extern int func_ov022_0209e398(struct Actor *pActor, struct Command *pCmd,
                               void *pCtx);
extern int func_ov022_0209e830(struct Actor *pActor, struct Command *pCmd,
                               void *pCtx);
extern int func_ov022_0209ecc8(struct Actor *pActor, struct Command *pCmd,
                               void *pCtx);
extern int func_ov022_020a1c80(struct Actor *pActor, struct Command *pCmd,
                               int *pHit);
extern int func_ov022_0209e4a4(struct Actor *pActor, void *pCtx,
                               struct Vec3 *pDelta);
extern void VEC_Subtract(const struct Vec3 *pA, const struct Vec3 *pB,
                         struct Vec3 *pOut);

int func_ov022_020a1064(struct Actor *pActor, struct Command *pCmd, void *pCtx)
{
    struct Vec3 vDelta;
    int bTaken;

    bTaken = 0;
    pActor->nHit = 0;
    pActor->bHitHeld = 0;
    if (func_ov022_0209e398(pActor, pCmd, pCtx) != 0) {
        bTaken = 1;
    }
    if (func_ov022_0209e830(pActor, pCmd, pCtx) != 0) {
        bTaken = 1;
    }
    if (func_ov022_0209ecc8(pActor, pCmd, pCtx) != 0) {
        bTaken = 1;
    }
    if (bTaken == 0) {
        if (func_ov022_020a1c80(pActor, pCmd, &pActor->nHit) != 0) {
            VEC_Subtract(&pCmd->vecTo, &pCmd->vecFrom, &vDelta);
            bTaken = func_ov022_0209e4a4(pActor, pCtx, &vDelta);
        }
    }
    return bTaken;
}
