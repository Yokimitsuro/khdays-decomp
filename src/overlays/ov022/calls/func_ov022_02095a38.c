/* ov022: decide whether the actor may act on the hit it is holding.
 *
 * Nothing happens at all while the combo record is busy, and two of the models
 * have to clear an extra record check of their own first.
 *
 * After that the hit's own stage decides. Two of the five stages only ask
 * whether a bit of the hit word is set. The last one is the wall case: the
 * actor has to be asking for it, and then either the hit kind is the simple one
 * and two bits will do, or it is the wall kind and the two wall blocks have to
 * be looked at.
 *
 * A wall block counts only while it is in contact, has a contact array, and
 * none of its three tags is the blocking kind. The face's normal is then turned
 * into an angle and compared against the actor's facing: the wall counts when
 * the two are within about forty-seven degrees of each other, measured either
 * way round the circle.
 *
 * Once one block has blocked, the flag stays set for the other, which is what
 * the ROM does and not an accident of where it is declared.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

#define ANGLE_BIAS 0x8000
#define IN_CONTACT 2
#define TAG_BLOCKING 2
#define AIM_BIT 2
#define HIT_BIT_A 1
#define HIT_BIT_B 4
#define FACING_NEAR 0x2100
#define FACING_FAR 0xdf00

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022CollBlock */
struct CollBlock {
    int nHandle;                 /* 0x00 */
    u8 *pContacts;               /* 0x04 */
    void *pRide;                 /* 0x08 */
    u8 pad00c[0x90];
    int nContactY;               /* 0x9c */
    u8 pada0[4];
    int nContactMode;            /* 0xa4 */
};

/* CollSurfaceAttr */
struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                 /* 0x0c */
    u8 pad10[4];
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
    u16 nAngleReplay;            /* 0x82 */
};

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[2];
    u8 nBusy;                    /* 0x02 */
    u8 pad03;
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord; /* 0x14 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0xc];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x10];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x190];
    struct CollBlock collWallA;  /* 0x01b8 */
    struct CollBlock collWallB;  /* 0x0260 */
    u8 pad0308[0x608];
    u32 nStateFlags;             /* 0x0910 */
    u8 pad0914[0x46c];
    struct ComboLock *pComboLock;/* 0x0d80 */
    u8 pad0d84[0x1938];
    int nHit;                    /* 0x26bc */
    int nHitKind;                /* 0x26c0 */
    u8 nHitStage;                /* 0x26c4 */
};

extern int func_ov022_0209fc48(struct Actor *pActor, int nIndex);
extern int func_ov022_020b0e50(u32 *pFlags);
extern struct CollSurfaceAttr *func_0202c37c(struct CollBlock *pBlock, int nTag);
extern void func_02028d74(int nHandle, u8 *pFace, struct VecFx32 *pOut);
extern int FX_Atan2(int x, int y);

int func_ov022_02095a38(struct Actor *pActor)
{
    struct CollBlock *aBlocks[2];
    struct VecFx32 vecNormal;
    struct CollSurfaceAttr *pAttr;
    int bResult;
    int bBlocked;
    u16 nFacing;
    int nDelta;
    int j;
    int bBlocking;
    int i;

    bResult = 0;
    if (pActor->pComboLock->pRecord->nBusy != 0) {
        return bResult;
    }
    bBlocked = 0;
    if (pActor->nModelId == 0 || pActor->nModelId == 5) {
        if (func_ov022_0209fc48(pActor, 1) == 0) {
            bBlocked = 1;
        }
    }
    if (bBlocked != 0) {
        return 0;
    }
    if (func_ov022_020b0e50(&pActor->nStateFlags) == 0) {
        if (pActor->nHitStage != 1 && pActor->nHitStage != 3) {
            return 0;
        }
    }
    switch (pActor->nHitStage) {
    case 1:
    case 2:
        if ((pActor->nHit & HIT_BIT_A) != 0) {
            bResult = 1;
        }
        break;
    case 3:
        if ((pActor->nHit & HIT_BIT_B) != 0) {
            bResult = 1;
        }
        break;
    case 4:
        if ((pActor->nInputMask & AIM_BIT) == 0) {
            break;
        }
        switch (pActor->nHitKind) {
        case 4:
            if ((pActor->nHit & HIT_BIT_A) != 0
                || (pActor->nHit & HIT_BIT_B) != 0) {
                bResult = 1;
            }
            break;
        case 1:
            aBlocks[0] = &pActor->collWallA;
            aBlocks[1] = &pActor->collWallB;
            bBlocking = 0;
            for (i = 0; i < 2; i++) {
                nFacing = (u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS;
                if (aBlocks[i]->nContactMode != IN_CONTACT) {
                    continue;
                }
                if (aBlocks[i]->pContacts == 0) {
                    continue;
                }
                for (j = 1; j < 4; j++) {
                    pAttr = func_0202c37c(aBlocks[i],
                                          aBlocks[i]->pContacts[j + 0x80]);
                    if (pAttr != 0 && pAttr->aTags[0] == TAG_BLOCKING) {
                        bBlocking = 1;
                        break;
                    }
                }
                if (bBlocking != 0) {
                    continue;
                }
                func_02028d74(aBlocks[i]->nHandle, aBlocks[i]->pContacts + 0x14,
                              &vecNormal);
                nDelta = (u16)(nFacing - (u16)FX_Atan2(-vecNormal.x,
                                                       -vecNormal.z));
                if (nDelta <= FACING_NEAR || nDelta >= FACING_FAR) {
                    bResult = 1;
                    break;
                }
            }
            break;
        }
        break;
    }
    return bResult;
}
