/* func_ov015_02080424 -- Ov015_TriggerHitTest: the trigger's hit handler.  While its
 * GameState field (+0x14 / +0x16) is clear the trigger is disabled (0).  A kind-1 query
 * on a box trigger (shape +0x3c == 1) with a zero message type tests the message's point
 * (+0x4) and radius (+0x10) against the box (centre +0x30, extent +0x40, ov002 0207c824)
 * and answers 1 / 0; any other kind answers -1. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int func_020235d0(u16 nField, u8 nBit);                    /* GameState_GetField */
extern int func_ov002_0207c824(VecFx32 *pCentre, VecFx32 *pExtent, VecFx32 *pPoint, int nRadius); /* point within the box */

typedef struct Ov015Trigger {
    u8   pad_00[0x14];
    u16  nStateField;         /* 0x14 */
    u8   nStateBit;           /* 0x16 */
    u8   pad_17[0x30 - 0x17];
    VecFx32 centre;           /* 0x30 */
    s8   nShape;              /* 0x3c */
    u8   pad_3d[3];
    VecFx32 extent;           /* 0x40 */
} Ov015Trigger;

typedef struct Ov015HitQuery {
    s8   nType;               /* 0x00 */
    u8   pad_01[3];
    VecFx32 point;            /* 0x04 */
    int  nRadius;             /* 0x10 */
} Ov015HitQuery;

int func_ov015_02080424(Ov015Trigger *pTrigger, int nKind, Ov015HitQuery *pQuery)
{
    int bEnabled;
    int bInside;

    if ((func_020235d0(pTrigger->nStateField, pTrigger->nStateBit) & 1) != 0) {
        bEnabled = 1;
    } else {
        bEnabled = 0;
    }
    if (bEnabled == 0) {
        return 0;
    }
    if (nKind == 1) {
        bInside = 0;
        if (pTrigger->nShape == 1 && pQuery->nType == 0) {
            bInside = func_ov002_0207c824(&pTrigger->centre, &pTrigger->extent, &pQuery->point, pQuery->nRadius);
        }
        return bInside != 0;
    }
    return -1;
}
