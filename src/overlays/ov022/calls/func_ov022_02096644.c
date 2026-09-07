/* ov022: react to what the actor is standing on.
 *
 * Walks the four collision contacts, looks up each surface's attribute block
 * and reacts to its tag: recording a landing point, forcing the airborne flags,
 * or pushing the actor away from a slope. The slope case flattens the surface
 * normal, renormalises it and scales it by how steep the slope was, with a
 * floor of half strength.
 *
 * Afterwards, if the actor is riding something that reports a drift, that
 * drift is added to the step vector.
 *
 * The object turns out to carry a THIRD 64-bit flag word at 0x46c, alongside
 * the ones at 0x00 and 0x464; all three use the same both-halves mask idiom.
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

struct RideOwner {
    u8 pad000[0x158];
    int nDrifts;                 /* 0x158 */
};

struct Ride {
    u8 pad00[0x28];
    struct RideOwner *pOwner;    /* 0x28 */
};

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 nOwner;                   /* 0x008 */
    u8 pad009[0x1b];
    u32 nInputMask;              /* 0x024 */
    u8 pad028[0x30];
    int nRecoil;                 /* 0x058 */
    u8 pad05c[0xc];
    int nCollHandle;             /* 0x068 */
    u8 *pContacts;               /* 0x06c */
    struct Ride *pRide;          /* 0x070 */
    u8 pad074[0x98];
    int nContactMode;            /* 0x10c */
    u8 pad110[0x354];
    unsigned long long nFlags2;  /* 0x464 */
    unsigned long long nFlags3;  /* 0x46c */
    u8 pad474[0x24];
    struct Vec3 vecStep;         /* 0x498 */
    struct Vec3 vecPush;         /* 0x4a4 */
    u8 pad4b0[0x208];
    int nRecoilDecay;            /* 0x6b8 */
    u8 pad6bc[0x1fac];
    int nLandingPoint;           /* 0x2668 */
};

extern struct Surface *func_0202c37c(int *pHandle, u32 nIndex);
extern int func_ov002_0206b7a4(void);
extern int func_02030788(void);
extern void func_02028d74(int nHandle, short *pTri, struct Vec3 *pOut);
extern void func_01ff8d18(const struct Vec3 *pIn, struct Vec3 *pOut);
extern void func_01ffa724(int nScale, const struct Vec3 *pIn, struct Vec3 *pOut);
extern struct Vec3 *func_ov002_02076d04(void);
extern void VEC_Add(const struct Vec3 *pA, const struct Vec3 *pB,
                    struct Vec3 *pOut);

void func_ov022_02096644(struct Actor *pActor)
{
    struct Surface *pSurf;
    int i;
    int nDrop;
    int nScale;
    struct Vec3 vecNormal;
    struct Vec3 vecTmp;
    struct Vec3 *pDrift;

    pActor->nFlags &= ~(1ULL << 43);
    if (pActor->pContacts == 0) {
        return;
    }
    i = 0;
    do {
        if (pActor->nContactMode != 2 || pActor->pRide != 0) {
            break;
        }
        pSurf = func_0202c37c(&pActor->nCollHandle, pActor->pContacts[i + 0x80]);
        if (pSurf != 0) {
            switch (pSurf->nTag) {
            case 0:
                break;
            case 1:
                if (i == 0
                    && (pActor->nInputMask & 4) != 0
                    && func_ov002_0206b7a4() == 0
                    && pActor->nOwner == func_02030788() && i == 0) {
                    pActor->nLandingPoint = pSurf->nLandingId;
                }
                break;
            case 2:
            case 3:
                break;
            case 4:
            case 7:
                if (func_02030788() == 0 && i != 0 && i != 3
                    && (pActor->nFlags & (1ULL << 36)) != 0) {
                    if ((pActor->nFlags2 & (1ULL << 7)) == 0) {
                        pActor->nRecoil = 0;
                        pActor->nRecoilDecay = 0;
                    }
                    if (func_02030788() == 0) {
                        pActor->nFlags2 |= (1ULL << 7);
                    }
                    if (func_02030788() == 0) {
                        pActor->nFlags3 |= (1ULL << 7);
                    }
                }
                break;
            case 5:
                break;
            case 6:
                if (func_02030788() == 0 && i != 0 && i != 3
                    && ((pActor->nFlags & (1ULL << 36)) == 0
                        || (pActor->nFlags2 & (1ULL << 7)) == 0)
                    && (pActor->nInputMask & 4) != 0) {
                    func_02028d74(pActor->nCollHandle,
                                  (short *)(pActor->pContacts + 0x14),
                                  &vecNormal);
                    nDrop = vecNormal.y;
                    vecNormal.y = 0;
                    func_01ff8d18(&vecNormal, &vecNormal);
                    nScale = 0x1000 - nDrop;
                    if (nScale < 0x800) {
                        nScale = 0x800;
                    }
                    func_01ffa724(nScale, &vecNormal, &vecNormal);
                    pActor->vecPush = vecNormal;
                }
                break;
            default:
                break;
            }
        }
        i++;
    } while (i < 4);

    if (func_02030788() != 0) {
        return;
    }
    if ((pActor->nInputMask & 4) == 0
        || pActor->pRide == 0
        || pActor->pRide->pOwner->nDrifts == 0) {
        return;
    }
    pDrift = func_ov002_02076d04();
    if (pDrift == 0) {
        return;
    }
    vecTmp = *pDrift;
    vecTmp.y = 0;
    VEC_Add(&pActor->vecStep, &vecTmp, &pActor->vecStep);
    pActor->vecStep.y += pDrift->y;
}
