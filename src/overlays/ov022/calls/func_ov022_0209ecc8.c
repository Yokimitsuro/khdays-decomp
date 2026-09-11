/* Ov022_SweepCapsuleOverEntries -- test a capsule against every active entry.
 *
 * Outside a live session the hit context must be open; inside one it must be
 * open or the actor must carry flag bit 12. The capsule's direction is taken
 * once, then every entry is tried except the actor's own (unless the capsule
 * says self-hits count): the entry is looked up against the capsule's group
 * and hit-id list, its point is fetched and tested against the capsule with
 * its own reach.
 *
 * Any hit answers yes. The local player with a context turns it into a hit
 * record and applies it, and a hit entry's id (shifted into the high bits) is
 * written into the first free slot of the capsule's hit-id list.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022Capsule (with the list this variant carries) */
struct Capsule {
    struct VecFx32 vecA;             /* 0x00 */
    struct VecFx32 vecB;             /* 0x0c */
    int nGroup;                      /* 0x18 */
    u8 pad1c[4];
    short *pHitIds;                  /* 0x20 */
    u32 nFlags;                      /* 0x24 */
};

/* Ov022SweepHit */
struct SweepHit {
    u8 pad00[8];
    int nOwnerFlags;                 /* 0x08 bit 6: open to contact */
};

struct HitRecord {
    struct VecFx32 vecPos;           /* 0x00 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                      /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                          /* 0x0009 */
    u8 pad000a[0x4ba];
    int nReach;                      /* 0x04c4 */
};

#define HIT_OPEN 0x40
#define FLAG_BIT12 (1ULL << 12)
#define CAPSULE_SELF 0x1
#define HIT_ID_FREE (-1)
#define HIT_ID_SLOTS 8
#define HIT_ID_SHIFT 11
#define FLAG_SET(nFlags, nBit) (((nFlags) & (nBit)) > 0)

extern int func_02030670(void);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB, struct VecFx32 *pOut);
extern int func_ov022_020882f8(void);
extern struct Actor *func_ov022_0209ee54(struct Actor *pActor, int nEntry, int nGroup,
                                         short *pHitIds);
extern void func_ov022_020ad44c(struct VecFx32 *pOut, struct Actor *pEntry);
extern int func_ov022_0209e0d8(struct VecFx32 *pPoint, int nRadius, struct VecFx32 *pOut,
                               struct Capsule *pCapsule);
extern int func_02030788(void);
extern void func_ov022_020a1118(struct HitRecord *pHit, struct SweepHit *pCtx,
                                struct VecFx32 *pContact, struct VecFx32 *pPoint,
                                struct VecFx32 *pDir);
extern void func_ov022_020a1870(struct Actor *pActor, struct SweepHit *pCtx,
                                struct Actor *pEntry, struct HitRecord *pHit);

int func_ov022_0209ecc8(struct Actor *pActor, struct Capsule *pCap, struct SweepHit *pCtx)
{
    struct HitRecord hit;
    struct VecFx32 vecDir;
    struct VecFx32 vecContact;
    struct VecFx32 vecPoint;
    int bHit;
    struct Actor *pEntry;
    int nEntry;
    int nSlot;
    short *pIds;

    bHit = 0;
    if (func_02030670() == 0) {
        if (!FLAG_SET(pCtx->nOwnerFlags, HIT_OPEN)) {
            return 0;
        }
    } else if ((pCtx->nOwnerFlags & HIT_OPEN) == 0 && (pActor->nFlags & FLAG_BIT12) == 0) {
        return 0;
    }
    VEC_Subtract(&pCap->vecB, &pCap->vecA, &vecDir);
    nEntry = 0;
    if (func_ov022_020882f8() > 0) {
        do {
            if (nEntry != pActor->nId || (pCap->nFlags & CAPSULE_SELF) != 0) {
                pEntry = func_ov022_0209ee54(pActor, nEntry, pCap->nGroup, pCap->pHitIds);
                if (pEntry != 0) {
                    func_ov022_020ad44c(&vecPoint, pEntry);
                    if (func_ov022_0209e0d8(&vecPoint, pEntry->nReach, &vecContact, pCap) != 0) {
                        bHit = 1;
                        if (func_02030788() == 0 && pCtx != 0) {
                            func_ov022_020a1118(&hit, pCtx, &vecContact, &vecPoint, &vecDir);
                            func_ov022_020a1870(pActor, pCtx, pEntry, &hit);
                        }
                        pIds = pCap->pHitIds;
                        if (pIds != 0) {
                            for (nSlot = 0; nSlot < HIT_ID_SLOTS; nSlot++) {
                                if (pIds[nSlot] == HIT_ID_FREE) {
                                    pIds[nSlot] = pEntry->nId << HIT_ID_SHIFT;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            nEntry++;
        } while (nEntry < func_ov022_020882f8());
    }
    return bHit;
}
