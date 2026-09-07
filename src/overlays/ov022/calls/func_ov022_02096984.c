/* ov022: track whether the actor is pressing into a wall.
 *
 * Runs from the per-frame tick, only for the local player's actor. It turns the
 * direction being pressed into a unit vector from the sine/cosine table, then
 * checks both wall collision blocks for a surface the actor is pushing into.
 * Holding the SAME surface starts a 64-bit tick stamp; once the dwell time has
 * elapsed the wall is committed as the landing point.
 *
 * If no wall is being held, a second sweep looks for climbable surfaces across
 * the remaining contacts and either starts a climb or forwards the state,
 * depending on which area the actor is in.
 *
 * The collision blocks turn out to be a repeated 0xa8-byte structure rather
 * than loose fields: handle, contact array, and a mode that must read 2.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

struct Surface {
    u8 pad00[0xc];
    u8 nTag;                     /* 0x0c */
    u8 pad0d[3];
    int nLandingId;              /* 0x10 */
};

struct WallHold {
    struct Surface *pSurface;    /* 0x00 */
    unsigned long long nStamp;   /* 0x04 */
};

struct CollBlock {
    int nHandle;                 /* 0x00 */
    u8 *pContacts;               /* 0x04 */
    u8 pad008[0x9c];
    int nContactMode;            /* 0xa4 */
};

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 nOwner;                   /* 0x008 */
    u8 pad009[9];
    u16 nHp;                     /* 0x012 */
    u8 pad014[6];
    u16 nButtons2;               /* 0x01a */
    u8 pad01c[8];
    u32 nInputMask;              /* 0x024 */
    u8 pad028[0x3e];
    short nSlotIndex;            /* 0x066 */
    struct CollBlock collMain;   /* 0x068 */
    u8 pad110[0xa8];
    struct CollBlock collWallA;  /* 0x1b8 */
    struct CollBlock collWallB;  /* 0x260 */
    u8 pad308[0x15c];
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[0xc];
    short nAngleBias;            /* 0x478 */
    u8 pad47a[0x1e7e];
    u8 stateBlk;                 /* 0x22f8 */
    u8 pad22f9[0x36f];
    int nLandingPoint;           /* 0x2668 */
    u8 pad266c[0x450];
    int nAimAngle;               /* 0x2abc */
    u8 pad2ac0[0x104];
    struct WallHold wallHold;       /* 0x2bc4 */
};

extern u16 data_0204c18c;
extern short data_0203d210[];

extern int func_02030788(void);
extern int func_ov022_020a0814(struct Actor *pActor);
extern void func_01ff8d18(const struct Vec3 *pIn, struct Vec3 *pOut);
extern int func_ov002_0206b7a4(void);
extern int func_ov022_02095450(u8 *pBlk);
extern int func_ov022_02095524(u8 *pBlk);
extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb40(int nSlot);
extern struct Surface *func_0202c37c(struct CollBlock *pBlk, u32 nIndex);
extern void func_02028d74(int nHandle, short *pTri, struct Vec3 *pOut);
extern int VEC_DotProduct(const struct Vec3 *pA, const struct Vec3 *pB);
extern unsigned long long func_020031d4(void);
extern int func_ov002_02072754(int nSlot);
extern void func_ov022_020ad2e4(struct Actor *pActor, int nMode);
extern void func_ov013_0207fd2c(struct Actor *pActor, struct Vec3 *pNormal);
extern void func_ov022_02096964(struct Actor *pActor);

void func_ov022_02096984(struct Actor *pActor)
{
    struct WallHold *pHold;
    int bSkip;
    int nAngle;
    struct CollBlock *apBlocks[2];
    struct Vec3 vecNormal;
    struct Vec3 vecDir;
    int i;
    struct CollBlock *pBlk;
    struct Surface *pSurf;
    int bClimb;
    int nDot;
    int nIdx;
    int j;
    u16 nSaved;
    int nInner;
    struct CollBlock *pSweep;
    int nOuter;

    pHold = &pActor->wallHold;
    bSkip = 0;
    if (pActor->nOwner != func_02030788()) {
        return;
    }
    apBlocks[0] = &pActor->collWallA;
    apBlocks[1] = &pActor->collWallB;
    if (func_02030788() == 0 || (pActor->nFlags & (1ULL << 16)) != 0) {
        nAngle = pActor->nAimAngle;
    } else {
        nSaved = pActor->nButtons2;
        pActor->nButtons2 = data_0204c18c;
        nAngle = func_ov022_020a0814(pActor);
        pActor->nButtons2 = nSaved;
    }
    if (nAngle == -1) {
        bSkip = 1;
    } else {
        nAngle = (u16)(nAngle + pActor->nAngleBias);
        nIdx = (nAngle >> 4) * 2;
        vecDir.x = -data_0203d210[nIdx];
        vecDir.z = -data_0203d210[nIdx + 1];
        vecDir.y = 0;
        func_01ff8d18(&vecDir, &vecDir);
    }
    if ((pActor->nInputMask & 2) == 0
        || func_ov002_0206b7a4() != 0
        || pActor->nSlotIndex < 0) {
        bSkip = 1;
    }
    if ((pActor->nFlags2 & (1ULL << 28)) != 0
        || (pActor->nFlags2 & (1ULL << 27)) != 0) {
        bSkip = 1;
    }
    if (pActor->nHp == 0 || (pActor->nFlags2 & (1ULL << 8)) != 0) {
        bSkip = 1;
    }
    if (func_ov022_02095450(&pActor->stateBlk) != 0
        && func_ov022_02095524(&pActor->stateBlk) == 0) {
        bSkip = 1;
    }
    if (func_02030788() == 0) {
        if ((pActor->nFlags & (1ULL << 33)) != 0
            || (pActor->nFlags & (1ULL << 28)) != 0) {
            bSkip = 1;
        }
        if ((pActor->nFlags2 & (1ULL << 13)) != 0
            || (pActor->nFlags2 & (1ULL << 12)) != 0) {
            bSkip = 1;
        }
    } else {
        if ((pActor->nFlags2 & (1ULL << 13)) != 0
            || (pActor->nFlags2 & (1ULL << 12)) != 0
            || (pActor->nFlags2 & (1ULL << 24)) != 0) {
            bSkip = 1;
        }
        if (func_ov002_0204cb40(func_ov022_02083f0c()) != 0) {
            bSkip = 1;
        }
    }

    if (bSkip == 0) {
        bSkip = 1;
        for (i = 0; i < 2; i++) {
            pBlk = apBlocks[i];
            if (pBlk->pContacts != 0 && pBlk->nContactMode == 2) {
                pSurf = func_0202c37c(pBlk, pBlk->pContacts[0x80]);
                if (pSurf != 0) {
                    func_02028d74(pBlk->nHandle,
                                  (short *)(pBlk->pContacts + 0x14),
                                  &vecNormal);
                    vecNormal.y = 0;
                    func_01ff8d18(&vecNormal, &vecNormal);
                    nDot = VEC_DotProduct(&vecNormal, &vecDir);
                    if (nDot <= 0 && pSurf->nTag == 1 && nDot <= 0) {
                        bSkip = 0;
                        if (pHold->pSurface == 0) {
                            pHold->pSurface = pSurf;
                            pHold->nStamp = func_020031d4();
                            break;
                        }
                        if (pHold->pSurface != pSurf) {
                            bSkip = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (bSkip != 0) {
        bClimb = 0;
        if ((pActor->nInputMask & 2) != 0 && nAngle != -1) {
            nOuter = 0;
            while (nOuter < 2 && bClimb == 0) {
                pSweep = apBlocks[nOuter];
                if (pSweep->pContacts != 0 && pSweep->nContactMode == 2) {
                    nInner = 1;
                    do {
                        pSurf = func_0202c37c(pSweep, pSweep->pContacts[nInner + 0x80]);
                        if (pSurf != 0 && pSurf->nTag == 8) {
                            func_02028d74(pSweep->nHandle,
                                          (short *)(pSweep->pContacts + 0x14),
                                          &vecNormal);
                            vecNormal.y = 0;
                            func_01ff8d18(&vecNormal, &vecNormal);
                            if (VEC_DotProduct(&vecNormal, &vecDir) <= 0) {
                                bClimb = 1;
                                break;
                            }
                        }
                        nInner++;
                    } while (nInner < 4);
                }
                nOuter++;
            }
        }
        if (bClimb != 0) {
            if (func_ov002_02072754(pActor->nSlotIndex) != 0xf) {
                func_ov022_020ad2e4(pActor, 3);
            } else {
                func_ov013_0207fd2c(pActor, &vecNormal);
            }
        }
        func_ov022_02096964(pActor);
        return;
    }

    if (pHold->nStamp + 0xcc8d > func_020031d4()) {
        return;
    }
    pActor->nLandingPoint = pHold->pSurface->nLandingId;
    func_ov022_02096964(pActor);
}
