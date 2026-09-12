/* Ov022_FindApproachDir -- find a direction from which the actor can reach
 * its partner, or a group member that faces the actor.
 *
 * The flat direction from the partner to the actor is taken first. It is
 * tried straight away when the partner carries flag-2 bit 19 and is within
 * 0x1e units; otherwise it needs the partner's flag-2 bit 6, the partner
 * within that reach and above the actor by no more than the node's headroom.
 * The direction is accepted when it agrees with the partner's facing.
 *
 * Failing that, every member of the actor's slot group whose owner is of
 * kind 2 and whose point lies within its radius plus 0x15 units is tried:
 * when its flat facing agrees with the flat direction from its point to the
 * actor, the sum of the two, normalised, is the answer.
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

/* Ov022ActorNode */
struct ActorNode {
    u8 pad000[0x80];
    u16 nAngle;                  /* 0x080 */
    u8 pad082[0xca];
    int nHeadroom;               /* 0x14c */
};

struct MemberOwner {
    u8 pad00[0x4c];
    u16 nKind;                   /* 0x4c */
};

struct MemberNode {
    u8 pad000[0xa8];
    VecFx32 vecPos;              /* 0x0a8 */
};

/* Ov002Element (the part this function reads) */
struct GroupMember {
    u8 pad000[4];
    struct GroupMember *pNext;   /* 0x004 */
    struct MemberOwner *pOwner;  /* 0x008 */
    u8 pad00c[0x18];
    struct MemberNode *pNode;    /* 0x024 */
    u8 pad028[0x440];
    VecFx32 vecFacing;           /* 0x468 */
    u8 pad474[0x20];
    int nRadius;                 /* 0x494 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x42];
    short nSlotIndex;            /* 0x0066 */
    u8 pad0068[0x3fc];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
};

#define FLAG2_BIT6 (1ULL << 6)
#define FLAG2_BIT19 (1ULL << 19)
#define REACH_NEAR 0x1e00
#define REACH_MARGIN 0x1500
#define DOT_AGREE 0x800
#define OWNER_KIND_2 2
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);         /* VEC_Distance */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);    /* VEC_Normalize, answers the length */
extern int VEC_DotProduct(VecFx32 *pA, VecFx32 *pB);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov002_02072754(int nGroup);
extern struct GroupMember *func_ov002_02076688(u16 nId);

int func_ov022_020aef50(struct Actor *pActor, struct Actor *pPartner, VecFx32 *pOut)
{
    VecFx32 vecDir;
    VecFx32 vecFacing;
    VecFx32 vecTo;
    VecFx32 vecMemberDir;
    VecFx32 *pAim;
    int nDy;
    int nLen;
    u16 nAngle;
    int nTrig;
    int nSinNeg;
    int nCosNeg;
    struct MemberNode *pNode;
    struct GroupMember *pMember;
    int nDist;

    pAim = &pPartner->vecAim;
    func_01ff8e94(pAim, &pActor->vecAim);
    VEC_Subtract(&pActor->vecAim, pAim, &vecDir);
    nDy = vecDir.y;
    vecDir.y = 0;
    nLen = func_01ff8d18(&vecDir, &vecDir);
    if ((pPartner->nFlags2 & FLAG2_BIT19) == 0 || nLen >= REACH_NEAR) {
        if ((pPartner->nFlags2 & FLAG2_BIT6) == 0) {
            goto search;
        }
        if (nLen >= REACH_NEAR || nDy >= 0) {
            goto search;
        }
        if (pActor->pNode->nHeadroom < -nDy) {
            goto search;
        }
    }
    nAngle = pPartner->pNode->nAngle - ANGLE_BIAS;
    nTrig = (nAngle >> ANGLE_STEP) * 2;
    nCosNeg = -data_0203d210[nTrig + 1];
    nSinNeg = -data_0203d210[nTrig];
    vecFacing.x = nSinNeg;
    /* Intentionally redundant: mwcc removes this store, but its presence
     * selects the register allocation for the fill that follows (Codex 12/09). */
    vecFacing.z = 0;
    vecFacing.z = nCosNeg;
    vecFacing.y = 0;
    func_01ff8d18(&vecFacing, &vecFacing);
    if (VEC_DotProduct(&vecFacing, &vecDir) > DOT_AGREE) {
        *pOut = vecDir;
        return 1;
    }
search:
    pMember = func_ov002_02076688((u16)func_ov002_02072754(pActor->nSlotIndex));
    if (pMember != 0) {
        do {
            if (pMember->pOwner != 0 && pMember->pOwner->nKind == OWNER_KIND_2) {
                pNode = pMember->pNode;
                nDist = func_01ff8e94(&pNode->vecPos, &pActor->vecAim);
                if (pMember->nRadius + REACH_MARGIN > nDist) {
                    vecMemberDir = pMember->vecFacing;
                    vecMemberDir.y = 0;
                    func_01ff8d18(&vecMemberDir, &vecMemberDir);
                    VEC_Subtract(&pActor->vecAim, &pNode->vecPos, &vecTo);
                    vecTo.y = 0;
                    func_01ff8d18(&vecTo, &vecTo);
                    if (VEC_DotProduct(&vecMemberDir, &vecTo) > DOT_AGREE) {
                        VEC_Add(&vecTo, &vecMemberDir, pOut);
                        func_01ff8d18(pOut, pOut);
                        return 1;
                    }
                }
            }
            pMember = pMember->pNext;
        } while (pMember != 0);
    }
    return 0;
}
