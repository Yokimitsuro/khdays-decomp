/* Ov022_SweepCapsuleOverGroup -- test a capsule against every member of a group.
 *
 * Nothing is tested while the actor carries the no-contact flag. Otherwise the
 * capsule's own direction is taken once, the group named by the capsule is
 * looked up, and every member that is present and open to contact is tested
 * against the capsule with its own radius.
 *
 * Any hit answers yes. Only the local player reports one: the contact is turned
 * into a hit record and handed on, and the actor keeps the contact point.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Capsule {
    VecFx32 vecA;                /* 0x00 */
    VecFx32 vecB;                /* 0x0c */
    int nGroup;                  /* 0x18 */
    int nRadius;                 /* 0x1c */
};

struct GroupMember {
    u8 pad0000[4];
    struct GroupMember *pNext;   /* 0x04 */
    u8 pad0008[0xa];
    u16 nFlags;                  /* 0x12 */
};

struct ContactPoint {
    VecFx32 vecPos;              /* 0x00 */
    int nRadius;                 /* 0x0c */
};

struct HitRecord {
    VecFx32 vecPos;              /* 0x00 */
};

struct Actor {
    unsigned int nFlags;         /* 0x0000 */
    u8 pad0004[0x26c4];
    VecFx32 vecImpact;           /* 0x26c8 */
};

extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov002_02072754(int nGroup);
extern struct GroupMember *func_ov002_02076688(u16 nId);
extern struct ContactPoint *func_ov002_02076d24(struct GroupMember *pMember);
extern int func_ov022_0209e0d8(const VecFx32 *pPoint, int nRadius,
                               VecFx32 *pOut, struct Capsule *pCapsule);
extern int func_02030788(void);
extern void func_ov022_020a1118(struct HitRecord *pHit, void *pCtx,
                                VecFx32 *pContact, struct ContactPoint *pPoint,
                                VecFx32 *pDir);
extern void func_ov022_020a1258(struct Actor *pActor, void *pCtx,
                                struct GroupMember *pMember,
                                struct HitRecord *pHit, int nArg);

#define ACTOR_NO_CONTACT 0x10000
#define MEMBER_OPEN 0x40

int func_ov022_0209e398(struct Actor *pActor, struct Capsule *pCap, void *pCtx)
{
    struct HitRecord hit;
    VecFx32 vecDir;
    VecFx32 vecContact;
    struct GroupMember *pMember;
    struct ContactPoint *pPoint;
    int bHit;

    bHit = 0;
    if ((pActor->nFlags & ACTOR_NO_CONTACT) != 0) {
        return 0;
    }
    VEC_Subtract(&pCap->vecB, &pCap->vecA, &vecDir);
    pMember = func_ov002_02076688((u16)func_ov002_02072754(pCap->nGroup));
    if (pMember != 0) {
        do {
            pPoint = func_ov002_02076d24(pMember);
            if (pPoint != 0 && (pMember->nFlags & MEMBER_OPEN) != 0
                && func_ov022_0209e0d8(&pPoint->vecPos, pPoint->nRadius,
                                       &vecContact, pCap) != 0) {
                bHit = 1;
                if (func_02030788() == 0 && pCtx != 0) {
                    func_ov022_020a1118(&hit, pCtx, &vecContact, pPoint,
                                        &vecDir);
                    func_ov022_020a1258(pActor, pCtx, pMember, &hit, 0);
                    pActor->vecImpact = vecContact;
                }
            }
            pMember = pMember->pNext;
        } while (pMember != 0);
    }
    return bHit;
}
