/* Ov022_FindClimbTarget -- look for a climbable ledge in front of the actor
 * and, when one is found, store its top as the ground target and the
 * facing to take; returns 1 on success.
 *
 * The climb meter must have reached 15.0 (else it grows by the area frame)
 * and the actor needs a slot; a floor closer than 0.875 below the actor
 * refuses. A sphere of 0.125 is cast along the facing from 1.5 above the
 * actor: the wall hit must belong to an owner with a live 0x158 word, not
 * be the excluded one, and face the actor (dot below -0.2). From the actor
 * pushed 2.0 out of the wall a second sphere of 0.3 is cast 3.0 back into
 * it with the same checks (dot below -0.8); the wall polygon's near-level
 * edges (|normal.y| <= 0.7) must all have the actor on their inside. The
 * hit record is kept in the ground block, the wall normal flattened and
 * reversed into the climb direction, the hit point moved 0.5 along it and
 * the ground 1.45 above it is searched: none, or a tag-3 surface among its
 * slots 1..2, refuses; three 0.28 spheres 0.48 above the ground point,
 * turned +90, -90 and 0 degrees from the climb direction (the last also
 * stepping back), must all be clear; the ground must sit between the actor
 * and 2.25 above it (a tolerance of 0.19 past that); a 10.0 ray down from
 * the wall point at the actor's centre height must not find a floor within
 * 2.75. Then the climb angle is the wall normal's heading, the actor's
 * 0x26b0 reach turned to it and added to the wall point gives the target.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    short x;
    short y;
    short z;
} VecS16;

typedef struct {
    int aM[9];
} MtxFx33;

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
};

/* HitPassOwner */
struct HitPassOwner {
    u8 pad000[0x158];
    void *pElement;              /* 0x158 */
};

/* HitState */
struct HitState {
    u8 pad00[0x28];
    struct HitPassOwner *pPassOwner;   /* 0x28 */
};

/* HitEdge: one polygon edge of a HitInfo */
struct HitEdge {
    VecS16 vecNormal;            /* 0x00 */
    u8 pad06[6];
};

/* HitInfo: the collision polygon a hit points at */
struct HitInfo {
    u8 pad00[0x12];
    u16 nEdgeCount;              /* 0x12 */
    short nX;                    /* 0x14: the packed normal */
    short nY;                    /* 0x16 */
    short nZ;                    /* 0x18 */
    u8 pad1a[6];
    struct HitEdge aEdges[4];    /* 0x20 */
    VecFx32 aPoints[4];          /* 0x50 */
    u8 aSurfaceSlots[4];         /* 0x80 */
};

/* Hit: the collision record a cast returns (0x98 bytes; the ground block keeps a copy) */
struct Hit {
    void *pModel;                /* 0x00 */
    struct HitInfo *pInfo;       /* 0x04 */
    struct HitState *pState;     /* 0x08 */
    int nNearestHit;             /* 0x0c */
    u8 pad10[0x88];
};

/* CollSurfaceAttr */
struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                 /* 0x0c */
    u8 pad10[4];
};

/* CollCastParams */
struct CollCastParams {
    VecFx32 *pOrigin;            /* 0x00 */
    VecFx32 *pDir;               /* 0x04 */
    int nRadius;                 /* 0x08 */
    u16 wDirIsUnit;              /* 0x0c */
    u16 wFlagE;                  /* 0x0e */
    void *pExtra;                /* 0x10 */
};

/* Ov022GroundBlock */
struct GroundBlock {
    VecFx32 vec;                 /* 0x00 */
    struct Hit hit;              /* 0x0c */
    int nStepScratch;            /* 0xa4 */
    u16 nFacingAngle;            /* 0xa8 */
    u8 padaa[2];
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x42];
    short nSlotIndex;            /* 0x0066 */
    u8 pad0068[0x9c];
    int nFloorY;                 /* 0x0104 */
    u8 pad0108[4];
    int nHasFloor;               /* 0x010c */
    u8 pad0110[0x37c];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x120];
    struct GroundBlock ground;   /* 0x05b8 */
    u8 pad0664[0x2048];
    int nCenterY;                /* 0x26ac */
    int nClimbReach;             /* 0x26b0 */
    u8 pad26b4[0x406];
    short nAreaFrame;            /* 0x2aba */
};

#define CLIMB_READY 0xf000
#define FLOOR_NEAR 0xe00
#define CAST_RAISE 0x1800
#define WALL_RADIUS 0x200
#define WALL_FACING -0x333
#define WALL_PUSH 0x2000
#define BACK_REACH 0x3000
#define BACK_RADIUS 0x4cd
#define BACK_FACING -0xccd
#define EDGE_TILT -0xb33
#define STEP_IN 0x800
#define GROUND_RAISE 0x1733
#define TAG_NO_CLIMB 3
#define PROBE_RAISE 0x7b3
#define PROBE_RADIUS 0x480
#define TOP_MAX 0x2400
#define TOP_TOLERANCE 0x300
#define WALL_BACK -0x1c0
#define RAY_DROP 0xa000
#define FLOOR_MIN 0x2c00

extern const short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */
extern const short data_0203e110[];               /* kFxSinCosTable entry 960 (+0xfc: entry 1023, ~90 degrees) */
extern const short data_02040210[];               /* kFxSinCosTable entry 3072 (270 degrees) */

extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ffa724(int nScale, VecFx32 *pIn, VecFx32 *pOut);             /* ScaleVec3Fx12 */
extern struct Hit *func_0202c2ac(u16 nSlot, VecFx32 *pFrom, VecFx32 *pDir, int nRadius, struct ActorNode *pNode);   /* sphere cast */
extern int func_020293a8(struct HitState *pState);                              /* IsField1cEqualData42910 */
extern void func_02028d74(void *pModel, VecS16 *pPacked, VecFx32 *pOut);        /* VecFx32FromVecS16 */
extern int VEC_DotProduct(VecFx32 *pA, VecFx32 *pB);
extern void func_01ffd0e8(int nT, VecFx32 *pDir, VecFx32 *pFrom, VecFx32 *pOut); /* Vec3ScaleAddQ27 */
extern void VEC_MultAdd(int nScale, VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_01ff8d18(VecFx32 *pIn, VecFx32 *pOut);                         /* VEC_Normalize */
extern struct Hit *func_ov022_02098040(int nSlot, VecFx32 *pPos, VecFx32 *pOut, struct Hit **ppHit);   /* Ov022_FindGroundUnder */
extern struct CollSurfaceAttr *func_0202c37c(struct Hit *pHit, int nTag);
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(VecFx32 *pVec, MtxFx33 *pMtx, VecFx32 *pOut);
extern struct Hit *func_0202c248(u16 nSlot, struct CollCastParams *pParams);    /* CollCast (sphere) */
extern struct Hit *func_0202c208(u16 nSlot, struct CollCastParams *pParams);    /* CollCast (ray) */
extern short FX_Atan2(int y, int x);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

/* Keep the signed 16-bit return and explicit inline: changing the return to
 * int changes MWCC 3.0/139's register allocation/spill scheduling. The lookups
 * below are written at their case sites; the const declarations allow MWCC
 * to hoist these invariant table reads before the loop. */
static inline short Ov022_ClimbReadTrig16(const short *table, int index)
{
    return table[index];
}
int func_ov022_02095e48(struct Actor *pActor)
{
    VecFx32 vecPos;
    VecFx32 vecHit;
    VecFx32 vecDir;
    VecFx32 vecClimb;
    VecFx32 vecFrom;
    VecFx32 vecNormal;
    VecFx32 vecTo;
    VecFx32 vecOff;
    struct CollCastParams params;
    MtxFx33 mtx;
    VecFx32 vecDelta;
    VecFx32 vecEdge;
    VecFx32 vecProbe;
    VecFx32 vecRot;
    VecFx32 vecDown;
    struct Hit *apHit[2];
    struct Hit *pHit;
    struct HitState *pState;
    struct CollSurfaceAttr *pAttr;
    int nTrig;
    int i;
    int nDiff;
    int nTop;
    int nLimit;
    short nSinA;
    short nCosA;
    short nSinB;
    short nCosB;
    short nSinC;
    short nCosC;

    if (pActor->ground.nStepScratch < CLIMB_READY) {
        pActor->ground.nStepScratch += pActor->nAreaFrame;
        return 0;
    }
    if (pActor->nSlotIndex < 0) {
        return 0;
    }
    vecPos = pActor->vecAim;
    if (pActor->nHasFloor != 0 && pActor->vecAim.y - pActor->nFloorY < FLOOR_NEAR) {
        return 0;
    }
    vecFrom = vecPos;
    vecFrom.y += CAST_RAISE;
    nTrig = ((u16)(pActor->pNode->nAngle - 0x8000) >> 4) * 2;
    vecDir.x = -data_0203d210[nTrig];
    vecDir.y = 0;
    vecDir.z = -data_0203d210[nTrig + 1];
    func_01ffa724(VEC_Mag(&vecDir), &vecDir, &vecDir);
    pHit = func_0202c2ac(pActor->nSlotIndex, &vecFrom, &vecDir, WALL_RADIUS, 0);
    if (pHit == 0) {
        return 0;
    }
    pState = pHit->pState;
    if (pState != 0) {
        if (pState->pPassOwner->pElement == 0) {
            return 0;
        }
        if (func_020293a8(pState)) {
            return 0;
        }
    }
    func_02028d74(pHit->pModel, (VecS16 *)&pHit->pInfo->nX, &vecNormal);
    if (VEC_DotProduct(&vecNormal, &vecDir) > WALL_FACING) {
        return 0;
    }
    func_01ffd0e8(pHit->nNearestHit, &vecDir, &vecFrom, &vecHit);
    vecTo = vecHit;
    vecTo = vecFrom;
    VEC_MultAdd(WALL_PUSH, &vecNormal, &vecTo, &vecTo);
    vecDir.x = -vecNormal.x;
    vecDir.y = 0;
    vecDir.z = -vecNormal.z;
    func_01ffa724(BACK_REACH, &vecDir, &vecDir);
    pHit = func_0202c2ac(pActor->nSlotIndex, &vecTo, &vecDir, BACK_RADIUS, pActor->pNode);
    if (pHit == 0) {
        return 0;
    }
    pState = pHit->pState;
    if (pState != 0) {
        if (pState->pPassOwner->pElement == 0) {
            return 0;
        }
        if (func_020293a8(pState)) {
            return 0;
        }
    }
    func_02028d74(pHit->pModel, (VecS16 *)&pHit->pInfo->nX, &vecNormal);
    if (VEC_DotProduct(&vecNormal, &vecDir) > BACK_FACING) {
        return 0;
    }
    if (pHit->pInfo != 0) {
        for (i = 0; i < pHit->pInfo->nEdgeCount; i++) {
            func_02028d74(pHit->pModel, &pHit->pInfo->aEdges[i].vecNormal, &vecEdge);
            if (vecEdge.y <= -EDGE_TILT && vecEdge.y >= EDGE_TILT) {
                VEC_Subtract(&vecFrom, &pHit->pInfo->aPoints[i], &vecDelta);
                if (VEC_DotProduct(&vecEdge, &vecDelta) <= 0) {
                    return 0;
                }
            }
        }
    }
    func_01ffd0e8(pHit->nNearestHit, &vecDir, &vecTo, &vecHit);
    vecTo = vecHit;
    pActor->ground.hit = *pHit;
    vecNormal.y = 0;
    func_01ff8d18(&vecNormal, &vecNormal);
    vecClimb.x = -vecNormal.x;
    vecClimb.y = 0;
    vecClimb.z = -vecNormal.z;
    VEC_MultAdd(STEP_IN, &vecClimb, &vecHit, &vecHit);
    vecFrom = vecHit;
    vecHit.y += GROUND_RAISE;
    apHit[0] = func_ov022_02098040(pActor->nSlotIndex, &vecHit, &vecHit, &apHit[1]);
    if (apHit[0] != 0 && apHit[1] != 0) {
        for (i = 1; i < 3; i++) {
            pAttr = func_0202c37c(apHit[1], apHit[1]->pInfo->aSurfaceSlots[i]);
            if (pAttr != 0 && pAttr->aTags[0] == TAG_NO_CLIMB) {
                apHit[0] = 0;
                break;
            }
        }
    }
    if (apHit[0] != 0) {
        vecProbe = vecHit;
        vecProbe.y += PROBE_RAISE;
        params.nRadius = PROBE_RADIUS;
        params.pOrigin = &vecProbe;
        params.pDir = &vecRot;
        params.wDirIsUnit = 1;
        params.wFlagE = 0;
        params.pExtra = 0;
        for (i = 0; i < 3; i++) {
            switch (i) {
            case 0:
                nCosA = Ov022_ClimbReadTrig16(data_0203e110, 0x7f);
                nSinA = Ov022_ClimbReadTrig16(data_0203e110, 0x7e);
                MTX_RotY33_(&mtx, nSinA, nCosA);
                break;
            case 1:
                nCosB = Ov022_ClimbReadTrig16(data_02040210, 1);
                nSinB = Ov022_ClimbReadTrig16(data_02040210, 0);
                MTX_RotY33_(&mtx, nSinB, nCosB);
                break;
            case 2:
                nCosC = Ov022_ClimbReadTrig16(data_0203d210, 1);
                nSinC = Ov022_ClimbReadTrig16(data_0203d210, 0);
                MTX_RotY33_(&mtx, nSinC, nCosC);
                MTX_MultVec33(&vecClimb, &mtx, &vecRot);
                func_01ffa724(PROBE_RADIUS, &vecRot, &vecRot);
                vecProbe.x -= vecRot.x;
                vecProbe.z -= vecRot.z;
                break;
            }
            MTX_MultVec33(&vecClimb, &mtx, &vecRot);
            func_01ffa724(PROBE_RADIUS, &vecRot, &vecRot);
            if (func_0202c248(pActor->nSlotIndex, &params) != 0) {
                apHit[0] = 0;
                break;
            }
        }
    }
    if (apHit[0] != 0) {
        nLimit = vecPos.y + TOP_MAX;
        if (nLimit < vecHit.y) {
            nDiff = vecHit.y - nLimit;
            if (nDiff < 0) {
                nDiff = -nDiff;
            }
            if (nDiff > TOP_TOLERANCE) {
                apHit[0] = 0;
            }
        } else if (vecPos.y > vecHit.y) {
            apHit[0] = 0;
        }
    }
    if (apHit[0] != 0) {
        vecTo.y = vecHit.y - pActor->nCenterY;
        VEC_MultAdd(WALL_BACK, &vecClimb, &vecTo, &vecTo);
        vecDown.x = 0;
        vecDown.y = -RAY_DROP;
        vecDown.z = 0;
        params.pOrigin = &vecTo;
        params.pDir = &vecDown;
        params.wFlagE = 0;
        params.pExtra = 0;
        params.wDirIsUnit = 1;
        pHit = func_0202c208(pActor->nSlotIndex, &params);
        if (pHit != 0) {
            nTop = vecTo.y + pActor->nCenterY;
            func_01ffd0e8(pHit->nNearestHit, &vecDown, &vecTo, &vecHit);
            nDiff = nTop - vecHit.y;
            if (nDiff < 0) {
                nDiff = -nDiff;
            }
            if (nDiff < FLOOR_MIN) {
                apHit[0] = 0;
            }
        }
        if (apHit[0] != 0) {
            pActor->ground.nFacingAngle = FX_Atan2(vecNormal.x, vecNormal.z);
            nTrig = (pActor->ground.nFacingAngle >> 4) * 2;
            MTX_RotY33_(&mtx, data_0203d210[nTrig], data_0203d210[nTrig + 1]);
            vecOff.x = pActor->nClimbReach;
            vecOff.y = 0;
            vecOff.z = 0;
            MTX_MultVec33(&vecOff, &mtx, &vecOff);
            VEC_Add(&vecTo, &vecOff, &pActor->ground.vec);
            return 1;
        }
    }
    return 0;
}
