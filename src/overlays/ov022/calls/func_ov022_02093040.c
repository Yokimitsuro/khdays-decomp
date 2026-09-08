/* ov022: run the actor's nine-slot dust emitter for a frame.
 *
 * Reactions 0xe and 0xf keep the charge climbing while the actor is no more than
 * 0x400 above the surface it is touching; any other reaction bleeds the cooldown
 * back down and drops the charged bit. Once the emitter is armed, every slot
 * whose animation has run past its first frame is re-seeded: a random offset
 * around the facing vector, a height that fans downward slot by slot, and one
 * random scale shared by the three axes. Each slot's animation is advanced
 * either way.
 *
 * Then, low enough and on reaction 0xf, either of the next two contacts landing
 * on a surface of kind 4 asks for a spawn: if every handle the emitter already
 * holds is far enough along, one free handle is spent on a new one. Handles
 * whose spawn has finished are released at the end of every frame.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long s64;

struct Vec3 {
    int x, y, z;
};

struct Anim {
    u8 pad0000[0xa4];
};

/* One of the emitter's nine slots. */
struct Slot {
    u8 nFlags;                   /* 0x0000 */
    u8 pad0001[3];
    struct Anim anim;            /* 0x0004 */
    struct Vec3 vecPos;          /* 0x00a8 */
    int nScaleX;                 /* 0x00b4 */
    int nScaleY;                 /* 0x00b8 */
    int nScaleZ;                 /* 0x00bc */
    u8 pad00c0[0x48];
};

struct Emitter {
    struct Slot aSlots[9];       /* 0x0000 */
    u8 pad0948[4];
    int nTarget;                 /* 0x094c */
    s8 aHandles[5];              /* 0x0950 */
    u8 pad0955[3];
    int nCooldown;               /* 0x0958 */
    int nCharge;                 /* 0x095c */
    u8 pad0960[0x10];
    int nChargeMax;              /* 0x0970 */
};

struct Coll {
    int pWorld;                  /* 0x0000 */
    u8 *pContacts;               /* 0x0004 */
    u8 pad0008[0x90];
    u8 blkSpawn;                 /* 0x0098 */
    u8 pad0099[3];
    int nContactY;               /* 0x009c */
    u8 pad00a0[4];
    int nContactCount;           /* 0x00a4 */
};

/* Records are 0x14 bytes each and live off the owner's first pointer. */
struct RecordTable {
    u8 pad0000[0xac];
    u8 *pRecords;                /* 0x00ac */
};

/* The usual fixed-point multiply: 12 fractional bits, rounded. */
static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

extern int func_0202aee0(struct Anim *pAnim, int nWhich);
extern void func_0202a818(struct Anim *pAnim, int nDelta);
extern int func_0203084c(void);
extern int func_ov022_02089604(int nTarget, int nHandle);
extern int func_ov022_020893f4(int nTarget, u8 *pBlk, u16 nAngle);
extern int func_ov022_020894f8(int nTarget, int nHandle);

void func_ov022_02093040(struct Emitter *pEm, struct Vec3 *pPos,
                         struct Vec3 *pOrigin, int nDelta, int nReaction,
                         int nAngle, struct Coll *pColl)
{
    struct Vec3 vecOrigin;
    struct Vec3 vecPos;
    int i;
    struct Anim *pAnim;
    struct Slot *pSlot;
    int bWanted;
    int nRand;
    int nScale;
    int nMin;
    int nProgress;
    u8 *pRec;
    struct RecordTable *pTable;
    u8 *pEntry;
    u8 nIndex;
    int k;

    if (nReaction != 0xe && nReaction != 0xf) {
        if (pEm->nCooldown > 0) {
            pEm->nCooldown -= nDelta;
        }
        if (pEm->nCooldown < 0) {
            pEm->nCooldown = 0;
        }
        pEm->aSlots[0].nFlags &= ~8;
    } else {
        if (pColl->nContactCount != 0 && pColl->pContacts != 0
            && pPos->y - pColl->nContactY <= 0x400) {
            pEm->nCharge += nDelta;
            if (pEm->nCharge > pEm->nChargeMax) {
                pEm->aSlots[0].nFlags |= 8;
            }
        } else {
            pEm->nCharge = 0;
            pEm->aSlots[0].nFlags &= ~8;
        }
    }
    if ((pEm->aSlots[0].nFlags & 4) == 0) {
        return;
    }
    vecOrigin = *pOrigin;
    pSlot = pEm->aSlots;
    pAnim = &pEm->aSlots[0].anim;
    for (i = 0; i < 9; i++) {
        if (func_0202aee0(pAnim, 2) < 0x1000) {
            vecPos = vecOrigin;
            nRand = func_0203084c();
            vecPos.x += FxMul(func_0203084c() - 0x800, 0x99a);
            vecPos.y += FxMul(func_0203084c(), 0x800) + (4 - i) * 0x200;
            vecPos.z += FxMul(func_0203084c() - 0x800, 0x99a);
            nScale = FxMul(nRand, 0x800) + 0x800;
            pSlot->vecPos = vecPos;
            pSlot->nScaleZ = nScale;
            pSlot->nScaleY = nScale;
            pSlot->nScaleX = nScale;
        }
        func_0202a818(pAnim, nDelta);
        pAnim = (struct Anim *)((u8 *)pAnim + sizeof(struct Slot));
        pSlot++;
    }
    bWanted = 0;
    if (pColl->nContactCount != 0 && pColl->pContacts != 0
        && pPos->y <= 0x3400) {
        pTable = (struct RecordTable *)pColl->pWorld;
        pEntry = pColl->pContacts + 1;
        for (k = 1; k < 3; k++) {
            nIndex = pEntry[0x80];
            if (nIndex == 0xff) {
                pRec = 0;
            } else {
                pRec = pTable->pRecords + nIndex * 0x14;
            }
            if (pRec != 0 && pRec[0xc] == 4 && nReaction == 0xf) {
                bWanted = 1;
            }
            pEntry++;
        }
    }
    if (bWanted != 0) {
        nMin = 0x7fffffff;
        for (i = 0; i < 5; i++) {
            if (pEm->aHandles[i] != -1) {
                nProgress = func_ov022_02089604(pEm->nTarget, pEm->aHandles[i]);
                if (nMin > nProgress) {
                    nMin = nProgress;
                }
            }
        }
        if (nMin > 0x3000) {
            for (i = 0; i < 5; i++) {
                if (pEm->aHandles[i] == -1) {
                    pEm->aHandles[i] = (s8)func_ov022_020893f4(
                        pEm->nTarget, &pColl->blkSpawn, (u16)nAngle);
                    break;
                }
            }
        }
    }
    if (pEm->nTarget == 0) {
        return;
    }
    for (i = 0; i < 5; i++) {
        if (pEm->aHandles[i] != -1
            && func_ov022_020894f8(pEm->nTarget, pEm->aHandles[i]) != 0) {
            pEm->aHandles[i] = -1;
        }
    }
}
