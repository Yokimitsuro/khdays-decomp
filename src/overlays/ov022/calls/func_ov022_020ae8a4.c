/* Ov022_SteerPartnerToPoint -- drive a partner's buttons towards a point
 * and tell whether it has been stuck there long enough.
 *
 * The flat direction to the point becomes the angle bias and button-2 bit 6
 * goes up. While the partner holds (flag-2 or flag-3 bit 7) it climbs or
 * drops by the height difference against its slot's inner reach -- 0xc00
 * when the leader stands still, 0x40 when the leader is not holding -- or,
 * without flag bit 36, jumps after a holding leader unless flag bit 14.
 * Otherwise a holding leader (and no knockdown kind 1) makes it jump when
 * aiming mode 2 allows, else walk; a free partner with flag bit 14 stops
 * and jumps, one without bit 26 walks or descends by the height check, the
 * climb flag and aim mode. Inside the range (0x2000, or 0x4000 once
 * steering) the jump button drops unless stopped or flagged, and a small
 * height difference stops the tracking; model 2 with a blocked run also
 * stops it and walks. A tracked partner that is far above or below, or
 * close to its slot's last position, ticks the slot's stall count by the
 * mode rate and reports 1 when it passes the slot's limit; otherwise the
 * slot's position takes the partner's and the count resets.
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

/* PlayerSlotDesc */
struct SlotDesc {
    u8 pad00[0x1c];
    int nReachInner;             /* 0x1c */
    u8 pad20[4];
    int nStallLimit;             /* 0x24 */
};

/* PlayerSlot */
struct PlayerSlot {
    int nState;                  /* 0x00 */
    u32 nFlags;                  /* 0x04 */
    int nStall;                  /* 0x08 */
    u8 pad0c[0x14];
    VecFx32 vecPos;              /* 0x20 */
    u8 pad2c[0x18];
    struct SlotDesc *pDesc;      /* 0x44 */
};

/* Ov022Charge */
struct Charge {
    signed char nKnockdownKind;  /* 0x00 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008;
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nModelId;                /* 0x000c */
    u8 pad0010[8];
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[0x448];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[4];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x12];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x1e60];
    u32 run[0xdc];               /* 0x22f8 Ov022ActionOwner */
    u8 pad2668[0x108];
    struct Charge charge;        /* 0x2770 */
    u8 pad2771[0x441];
    signed char nAimMode;        /* 0x2bb2 */
};

#define FLAG_BIT14 (1ULL << 14)
#define FLAG_BIT26 (1ULL << 26)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT61 (1ULL << 61)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG3_BIT7 (1ULL << 7)
#define BUTTON_JUMP 0x800
#define BUTTON_WALK 0x2
#define BUTTON2_BIT6 0x40
#define RANGE_NEAR 0x2000
#define RANGE_STEER 0x4000
#define REACH_DEFAULT 0x1000
#define REACH_STILL 0xc00
#define REACH_FREE 0x40
#define STILL_DIST 0x100
#define HEIGHT_FAR 0xa000
#define SLOT_NEAR 0x1000
#define STALL_FAST 0xcd
#define STALL_SLOW 0x89
#define KNOCKDOWN_1 1
#define AIM_MODE_1 1
#define AIM_MODE_2 2
#define MODEL_2 2

extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern int FX_Inv(int nNumerator, int nDenominator);
extern int FX_Atan2(int y, int x);
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);                             /* VEC_Distance */
extern int func_ov022_020afd0c(struct Actor *pActor, int nY);                   /* IsDeltaOver1000 */
extern int func_ov022_02095524(u32 *pRun);                                      /* ov022_IsState9Or6WithFlag200 */
extern int func_02023c40(void);                                                 /* LoadGlobalU8_0204c058 */

static inline void VEC_Set(VecFx32 *pVec, int x, int y, int z)
{
    pVec->x = x;
    pVec->y = y;
    pVec->z = z;
}

int func_ov022_020ae8a4(struct Actor *pSelf, struct Actor *pLeader, VecFx32 *pPoint, int bNoClimb)
{
    VecFx32 vecDir;
    struct PlayerSlot *pSlot;
    int nRet;
    int bStop;
    int nRange;
    int bTrack;
    int nDist;
    int nDy;
    int nReach;
    int nStep;
    u16 nAngle;

    pSlot = func_020358a4((u8)(pSelf->nId - 1));
    nRet = 0;
    bStop = 0;
    nRange = RANGE_NEAR;
    bTrack = 1;
    VEC_Subtract(pPoint, &pSelf->vecAim, &vecDir);
    nDy = vecDir.y;
    vecDir.y = 0;
    nDist = VEC_Mag(&vecDir);
    if (nDist != 0) {
        VEC_Set(&vecDir, FX_Inv(vecDir.x, nDist), FX_Inv(vecDir.y, nDist), FX_Inv(vecDir.z, nDist));
    } else {
        return 0;
    }
    nAngle = FX_Atan2(-vecDir.x, -vecDir.z);
    pSelf->nAngleBias = nAngle;
    pSelf->nButtons2 |= BUTTON2_BIT6;
    if ((pSelf->nFlags2 & FLAG2_BIT7) != 0 || (pSelf->nFlags3 & FLAG3_BIT7) != 0) {
        if ((pSelf->nFlags & FLAG_BIT36) != 0) {
            nReach = REACH_DEFAULT;
            if (pSlot->pDesc != 0) {
                nReach = pSlot->pDesc->nReachInner;
            }
            if (func_01ff8e94(&pLeader->vecAim, &pLeader->vecAim) < STILL_DIST) {
                nReach = REACH_STILL;
            }
            if ((pLeader->nFlags2 & FLAG2_BIT7) == 0) {
                nReach = REACH_FREE;
            }
            pSelf->nButtons2 &= ~(BUTTON_JUMP | BUTTON_WALK);
            if (nReach < nDy) {
                pSelf->nButtons2 |= BUTTON_JUMP;
            } else if (~nReach > nDy) {
                pSelf->nButtons2 |= BUTTON_WALK;
            }
        } else {
            if ((pLeader->nFlags2 & FLAG2_BIT7) != 0 && (pSelf->nFlags & FLAG_BIT14) == 0) {
                pSelf->nButtons |= BUTTON_JUMP;
                pSelf->nButtons2 |= BUTTON_JUMP;
            } else {
                pSelf->nButtons2 &= ~BUTTON_JUMP;
            }
            pSelf->nButtons2 &= ~BUTTON_WALK;
        }
        nRange = RANGE_STEER;
    } else {
        if ((pLeader->nFlags2 & FLAG2_BIT7) != 0 && pSelf->charge.nKnockdownKind != KNOCKDOWN_1) {
            if (pSelf->nAimMode == AIM_MODE_2 && (pSelf->nFlags & FLAG_BIT14) == 0) {
                pSelf->nButtons |= BUTTON_JUMP;
                pSelf->nButtons2 |= BUTTON_JUMP;
            } else {
                if (pSelf->nAimMode != AIM_MODE_1) {
                    pSelf->nButtons |= BUTTON_WALK;
                }
                pSelf->nButtons2 |= BUTTON_WALK;
            }
            nRange = RANGE_STEER;
        } else {
            if ((pSelf->nFlags & FLAG_BIT14) != 0) {
                bStop = 1;
                pSelf->nButtons |= BUTTON_JUMP;
            } else if ((pSelf->nFlags & FLAG_BIT26) == 0) {
                pSelf->nButtons2 &= ~BUTTON_JUMP;
                if (func_ov022_020afd0c(pSelf, pPoint->y) != 0 && pSelf->charge.nKnockdownKind != KNOCKDOWN_1) {
                    if (bNoClimb != 0 || nDist < nDy) {
                        if (pSelf->nAimMode != AIM_MODE_1) {
                            pSelf->nButtons |= BUTTON_WALK;
                        }
                        pSelf->nButtons2 |= BUTTON_WALK;
                    } else if (pSelf->nAimMode == AIM_MODE_2) {
                        pSelf->nButtons2 |= BUTTON_WALK;
                    } else {
                        pSelf->nButtons2 &= ~BUTTON_WALK;
                    }
                } else {
                    pSelf->nButtons2 &= ~BUTTON_WALK;
                }
            }
        }
    }
    if (nRange > nDist) {
        if ((pSelf->nFlags & (FLAG_BIT26 | FLAG_BIT61)) == 0 && bStop == 0) {
            pSelf->nButtons2 &= ~BUTTON2_BIT6;
        }
        if ((nDy < 0 ? -nDy : nDy) < HEIGHT_FAR) {
            bTrack = 0;
        }
    }
    if (pSelf->nModelId == MODEL_2 && func_ov022_02095524(pSelf->run) != 0) {
        bTrack = 0;
        pSelf->nButtons |= BUTTON_WALK;
    }
    if (bTrack) {
        if (nDy < 0) {
            nDy = -nDy;
        }
        if (nDy > HEIGHT_FAR || func_01ff8e94(&pSelf->vecAim, &pSlot->vecPos) < SLOT_NEAR) {
            nStep = func_02023c40() == 1 ? STALL_FAST : STALL_SLOW;
            pSlot->nStall += nStep;
            if (pSlot->pDesc->nStallLimit < pSlot->nStall) {
                pSlot->nStall = 0;
                nRet = 1;
            }
            goto done;
        }
    }
    pSlot->vecPos = pSelf->vecAim;
    pSlot->nStall = 0;
done:
    return nRet;
}
