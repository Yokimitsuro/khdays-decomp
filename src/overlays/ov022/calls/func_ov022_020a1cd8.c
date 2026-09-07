/* ov022: find what the actor's reach touches, trying three sweeps in turn.
 *
 * The straight sweep goes first. If it finds something the caller cannot use,
 * or finds nothing, the same sweep is retried from a point one radius lower and
 * then from one radius higher, each with its own kind so the caller knows which
 * one answered. The lowered sweep only counts if the surface it hit is steep
 * enough, and both offset sweeps are thrown away if the contact point ends up on
 * the wrong side of the reach limit.
 *
 * A hit that carries an owner answers with the owner's handle instead of the
 * contact itself, and only if that handle exists.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define STEEP_LIMIT 0x100
#define PARTS_PER_HIT 4
#define KIND_OWNED 4

struct Vec3 {
    int x, y, z;
};

struct Part {
    u8 pad00[0x14];
    u8 verts[0x6c];              /* 0x14 */
    u8 aId[4];                   /* 0x80 */
};

struct Owner {
    u8 pad00[0x28];
    int *pSlot;                  /* 0x28 */
};

struct Hit {
    int nFace;                   /* 0x00 */
    struct Part *pPart;          /* 0x04 */
    struct Owner *pOwner;        /* 0x08 */
    void *pShape;                /* 0x0c */
    u8 pad10[0x88];
};

struct Thing {
    u8 pad00[0xc];
    u8 nRole;                    /* 0x0c */
};

struct Ray {
    u8 pad00[4];
    int nLimit;                  /* 0x04 */
    u8 pad08[4];
    struct Vec3 vec;             /* 0x0c */
    int nRadius;                 /* 0x18 */
    int nMask;                   /* 0x1c */
};

struct Contact {
    u8 pad00[4];
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    struct Vec3 vec;             /* 0x0c */
    int nHandle;                 /* 0x18 */
    struct Hit hit;              /* 0x1c */
};

struct Scene {
    u8 pad00[0x20];
    void *pWorld;                /* 0x20 */
};

extern struct Hit *func_0202c2ac(u16 nMask, struct Ray *pRay,
                                 struct Vec3 *pFrom, int nRadius,
                                 void *pWorld);
extern struct Hit *func_0202c268(u16 nMask, struct Ray *pRay,
                                 struct Vec3 *pFrom, void *pWorld);
extern struct Hit *func_0202c2f8(u16 nMask, struct Ray *pRay,
                                 struct Vec3 *pFrom, void *pWorld);
extern struct Thing *func_0202c37c(struct Hit *pHit, int nId);
extern void func_01ffd0e8(void *pShape, struct Vec3 *pFrom, struct Ray *pRay,
                          struct Vec3 *pOut);
extern void func_02028d74(int nFace, u8 *pVerts, struct Vec3 *pOut);
extern void func_01ff8d18(struct Vec3 *pOut, struct Vec3 *pIn);

int func_ov022_020a1cd8(struct Scene *pScene, struct Ray *pRay,
                        struct Contact *pOut)
{
    struct Vec3 vFrom;
    struct Vec3 vPoint;
    struct Vec3 vNormal;
    int bTaken;
    struct Hit *pHit;
    int nKind;
    int nOffset;
    int i;

    bTaken = 0;
    nKind = 0;
    if (pOut != 0) {
        pOut->nKind = 0;
        pOut->nState = 0;
    }
    pHit = func_0202c2ac(pRay->nMask, pRay, &pRay->vec, pRay->nRadius,
                         pScene->pWorld);
    if (pHit != 0) {
        if (pHit->pOwner == 0) {
            for (i = 0; i < PARTS_PER_HIT; i++) {
                struct Thing *pThing = func_0202c37c(pHit,
                                                     pHit->pPart->aId[i]);

                if (pThing != 0 && pThing->nRole == 2) {
                    pHit = 0;
                    break;
                }
            }
        }
        if (pHit != 0) {
            func_01ffd0e8(pHit->pShape, &pRay->vec, pRay, &vPoint);
            nKind = 1;
        }
    }
    if (pHit == 0) {
        nOffset = -pRay->nRadius;
        vFrom.x = 0;
        vFrom.z = 0;
        vFrom.y = nOffset;
        vFrom = pRay->vec;
        vFrom.y = vFrom.y - pRay->nRadius;
        pHit = func_0202c268(pRay->nMask, pRay, &vFrom, pScene->pWorld);
        if (pHit != 0) {
            func_02028d74(pHit->nFace, pHit->pPart->verts, &vNormal);
            func_01ff8d18(&vNormal, &vNormal);
            if (vNormal.y >= STEEP_LIMIT || vNormal.y <= -STEEP_LIMIT) {
                nKind = 2;
                func_01ffd0e8(pHit->pShape, &vFrom, pRay, &vPoint);
                if (vPoint.y > pRay->nLimit) {
                    nKind = 0;
                    pHit = 0;
                }
            } else {
                pHit = 0;
            }
        }
    }
    if (pHit == 0) {
        nOffset = pRay->nRadius;
        vFrom.x = 0;
        vFrom.z = 0;
        vFrom.y = nOffset;
        vFrom = pRay->vec;
        vFrom.y = vFrom.y + pRay->nRadius;
        pHit = func_0202c2f8(pRay->nMask, pRay, &vFrom, pScene->pWorld);
        if (pHit != 0) {
            nKind = 3;
            func_01ffd0e8(pHit->pShape, &vFrom, pRay, &vPoint);
            if (vPoint.y < pRay->nLimit) {
                nKind = 0;
                pHit = 0;
            }
        }
    }
    if (pHit != 0) {
        bTaken = 1;
        if (pHit->pOwner != 0) {
            nKind = KIND_OWNED;
            if (pHit->pOwner->pSlot[0x158 / 4] == 0) {
                bTaken = 0;
            }
        }
        if (pOut != 0 && bTaken != 0) {
            pOut->nKind = nKind;
            pOut->nState = 4;
            if (nKind != KIND_OWNED) {
                pOut->hit = *pHit;
            } else {
                pOut->nHandle = pHit->pOwner->pSlot[0x158 / 4];
            }
            pOut->vec = vPoint;
        }
    }
    return bTaken;
}
