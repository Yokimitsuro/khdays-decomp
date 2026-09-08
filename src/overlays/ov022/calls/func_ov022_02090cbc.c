/* Ov022_SpawnShot -- take a free shot out of the pool and start it.
 *
 * The request names a kind, and the kind says how many shots of it may be in the
 * air; the first idle slot within that count is the one taken. If they are all
 * busy the request is refused.
 *
 * The shot then takes the request's point twice over -- once as where it is and
 * once as where it started -- its rig slots are returned, and the rest of the
 * request is copied across: the owner, the three ids, the fuse, and the
 * direction as three whole numbers. A shot whose kind is not marked keeps its
 * speed scaled by the kind's own figure, half again as much on the wider
 * setting. What is left is the eight already-struck ids cleared and the two
 * trailing counters zeroed.
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
    unsigned int nFlags;             /* 0x00 */
    u8 pad04[0xc];
    int nSpeed;                      /* 0x10 */
    u8 pad14[8];
    int nField1c;                    /* 0x1c */
    u8 pad20[0x2c];
    s8 nMax;                         /* 0x4c */
    u8 pad4d[3];
};

/* Ov022Shot */
struct Shot {
    u8 nFlags;                       /* 0x000 */
    u8 pad001;
    s8 nState;                       /* 0x002 */
    u8 pad003;
    int nAge;                        /* 0x004 */
    u8 nOwner;                       /* 0x008 */
    s8 nField09;                     /* 0x009 */
    u8 nField0a;                     /* 0x00a */
    u8 nField0b;                     /* 0x00b */
    int nField0c;                    /* 0x00c */
    struct VecFx32 vecStart;         /* 0x010 */
    struct VecFx32 vecDir;           /* 0x01c */
    u8 pad028[0xa4];
    struct VecFx32 vecPos;           /* 0x0cc */
    u8 pad0d8[0x5c];
    u8 nField134;                    /* 0x134 */
    u8 pad135[3];
    struct ShotDesc *pDesc;          /* 0x138 */
    short aHitIds[8];                /* 0x13c */
    u8 pad14c[0x78];
    u16 nField1c4;                   /* 0x1c4 */
    u8 nField1c6;                    /* 0x1c6 */
    u8 pad1c7;
};

struct ShotPool {
    u8 pad00[0xc];
    struct Shot *pShots;             /* 0x0c */
    struct ShotDesc *pDescs;         /* 0x10 */
};

struct SpawnReq {
    struct VecFx32 vecPos;           /* 0x00 */
    short nDirX;                     /* 0x0c */
    short nDirY;                     /* 0x0e */
    short nDirZ;                     /* 0x10 */
    short nFuse;                     /* 0x12 */
    u8 pad14[4];
    int nId0;                        /* 0x18 */
    int nId1;                        /* 0x1c */
    int nId2;                        /* 0x20 */
    int nRig;                        /* 0x24 */
    int nDesc;                       /* 0x28 */
};

extern void func_ov022_020914a0(struct Shot *pShot, int nRig);
extern int func_02023c40(void);
extern void func_01ffa724(int nScale, struct VecFx32 *pIn, struct VecFx32 *pOut);

#define SHOT_IDLE 0
#define SHOT_LIVE 1
#define SHOT_LANDED 2
#define DESC_UNSCALED 0x20
#define WIDE_SETTING 1
#define ID_NONE 7
#define HIT_SLOTS 8

int func_ov022_02090cbc(struct ShotPool *pPool, struct SpawnReq *pReq,
                        int nOwner)
{
    struct ShotDesc *pDesc;
    struct Shot *pShot;
    int nIndex;
    struct Shot *pWalk;
    struct Shot *pShots;
    int nCount;
    int nScale;
    short nDirY;
    short nDirZ;

    pDesc = &pPool->pDescs[pReq->nDesc];
    nCount = pDesc->nMax;
    pShot = 0;
    nIndex = 0;
    if (nCount > 0) {
        pShots = pPool->pShots;
        pWalk = pShots;
        do {
            if (pWalk->nState == SHOT_IDLE) {
                pShot = &pShots[nIndex];
                break;
            }
            nIndex++;
            pWalk++;
        } while (nIndex < nCount);
    }
    if (pShot == 0) {
        return 0;
    }
    pShot->vecPos = pReq->vecPos;
    func_ov022_020914a0(pShot, pReq->nRig);
    pShot->pDesc = pDesc;
    pShot->nOwner = (u8)nOwner;
    pShot->vecStart = pReq->vecPos;
    pShot->nFlags = 0;
    pShot->nState = pDesc->nField1c > 0 ? SHOT_LIVE : SHOT_LANDED;
    pShot->nAge = 0;
    pShot->nField0c = pReq->nFuse;
    pShot->nField134 = 0;
    pShot->nField09 = (u8)pReq->nId0;
    if (pReq->nId0 >= ID_NONE) {
        pShot->nField09 = -1;
    }
    pShot->nField0a = (u8)pReq->nId1;
    pShot->nField0b = (u8)pReq->nId2;
    nDirZ = pReq->nDirZ;
    nDirY = pReq->nDirY;
    pShot->vecDir.x = pReq->nDirX;
    pShot->vecDir.y = nDirY;
    pShot->vecDir.z = nDirZ;
    if ((pDesc->nFlags & DESC_UNSCALED) == 0) {
        if (func_02023c40() == WIDE_SETTING) {
            nScale = pDesc->nSpeed * 3 / 2;
        } else {
            nScale = pDesc->nSpeed;
        }
        func_01ffa724(nScale, &pShot->vecDir, &pShot->vecDir);
    }
    nIndex = 0;
    do {
        pShot->aHitIds[nIndex] = -1;
        nIndex++;
    } while (nIndex < HIT_SLOTS);
    pShot->nField1c4 = 0;
    pShot->nField1c6 = 0;
    return 1;
}
