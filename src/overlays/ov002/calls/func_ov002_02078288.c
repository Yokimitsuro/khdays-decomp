typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed long long s64;
typedef struct Ov002Vec3 { int x, y, z; } Ov002Vec3;
typedef struct VecFx16 { s16 x, y, z; } VecFx16;
typedef struct Ov002PieceClass { char pad000[0x4c]; u16 wClassFlags; } Ov002PieceClass;
typedef struct Ov002PieceElement { char pad000[8]; Ov002PieceClass *pOwner; } Ov002PieceElement;
typedef struct Ov002SpotActionOwner {
    char pad000[0x70];
    int nAttractHeight;
    char pad074[0x11c];
    Ov002Vec3 vAttractPosition;
} Ov002SpotActionOwner;
typedef struct Ov002Spawned {
    struct Ov002Spawned *pNext;
    char pad004[8];
    Ov002Vec3 vHome;
    char pad018[0x10];
    Ov002SpotActionOwner *pActionOwner;
    char pad02c[4];
    u8 bResting : 1;
    u8 bActivationPending : 1;
    u8 bPlaced : 1;
    u8 bAtSpot : 1;
    u8 bOther : 4;
    s8 nSpinDirection;
    char pad032[2];
    s16 nSpin, nHealth, nPower;
    char pad03a[2];
    int nSpeed;
    Ov002Vec3 vPos, vVel;
    Ov002PieceElement *pGroundElement;
} Ov002Spawned;
typedef struct Ov002SpawnCtx {
    char pad000[0xc];
    Ov002Spawned *pHead;
    char pad010[0x174];
} Ov002SpawnCtx;
typedef struct Ov002SpotStage {
    char pad000[0x58];
    int nUpdateHold;
    char pad05c[0x5c];
    Ov002SpawnCtx aCtx[24];
    char pad2518[0xc];
    int bCheckMovingPlatforms;
} Ov002SpotStage;
typedef struct Ov002SpotHolder { char pad000[4]; Ov002SpotStage *pStage; } Ov002SpotHolder;
typedef struct HitInfo {
    char pad000[0x14];
    s16 nX, nY, nZ;
    char pad01a[2];
    int nPlaneDistance;
} HitInfo;
typedef struct HitPassOwner { char pad000[0x158]; Ov002PieceElement *pElement; } HitPassOwner;
typedef struct HitState { char pad000[0x28]; HitPassOwner *pPassOwner; } HitState;
typedef struct Hit { void *pModel; HitInfo *pInfo; HitState *pState; int nNearestHit; } Hit;
typedef struct CollCastParams {
    Ov002Vec3 *pOrigin, *pDir;
    int nRadius;
    u16 wDirIsUnit, wFlagE;
    void *pExtra;
} CollCastParams;
typedef struct SinCos { s16 nSin, nCos; } SinCos;
extern Ov002SpotHolder data_ov002_0207fa28;
extern SinCos data_0203d210[];
extern int func_ov002_0207687c(void);
extern int func_ov002_0207285c(int);
extern int func_01ff8d18(const Ov002Vec3 *, Ov002Vec3 *);
extern void VEC_Subtract(const Ov002Vec3 *, const Ov002Vec3 *, Ov002Vec3 *);
extern void VEC_Add(const Ov002Vec3 *, const Ov002Vec3 *, Ov002Vec3 *);
extern void VEC_MultAdd(int, const Ov002Vec3 *, const Ov002Vec3 *, Ov002Vec3 *);
extern int VEC_DotProductFx16(const Ov002Vec3 *, const VecFx16 *);
extern void func_01ffd0e8(int, const Ov002Vec3 *, const Ov002Vec3 *, Ov002Vec3 *);
extern void func_ov002_02077df0(Ov002Spawned *);
extern void func_ov002_02078120(Ov002Spawned *);
extern Ov002Vec3 *func_ov002_02076d04(Ov002PieceElement *);
extern Hit *func_0202c208(u16, CollCastParams *);
extern Hit *func_0202c248(u16, CollCastParams *);
static inline int MulRound(int a, int b) { return (int)(((s64)a * b + 0x800) >> 12); }
static inline int Abs(int a) { return a < 0 ? -a : a; }

/* Update all spawned spots: attraction, resting contacts, collision response,
 * moving-platform bounce and out-of-world release.
 *
 * MWCC: preserve the declaration order and the separate resting/ground element
 * bindings with lifetime optimization disabled. Together they retain the ROM's
 * callee-saved register allocation. The qualified gravity expression and const
 * stage binding also preserve the scalar stack-slot order. */
#pragma push
#pragma opt_lifetimes off
void func_ov002_02078288(void)
{
    int nCtx;
    int nScale;
    Ov002PieceElement *pOldGround;
    CollCastParams params;
    Ov002Vec3 vBlend, vDirection, vAttract;
    Ov002Vec3 vOrigin, vDown, vBounceNormal;
    Ov002Vec3 vGroundNormal, vGround, vNegative, vReflected;
    Ov002Spawned *pRow;
    int nGravity;
    Ov002Spawned *pNext;
    Ov002PieceElement *pElement;
    int nSlot;
    Hit *pHit;
    HitState *pGroundState;
    HitInfo *pGroundInfo;
    HitInfo *pWallInfo;
    Ov002Vec3 *pGroundVelocity;
    int nDistance;
    int nGroundFraction;
    int nWallFraction;
    int nDot;
    Ov002SpotStage *pCtxWalk;

    Ov002PieceElement *pElementResting;
    Ov002PieceElement *pElementGround;
    nScale = func_ov002_0207687c();
    nGravity = (int)(const int)MulRound(nScale, 0x45);
    Ov002SpotStage *const pStage = data_ov002_0207fa28.pStage;
    nCtx = 0;
    if (pStage->nUpdateHold != 0) return;
    params.wFlagE = 0xf;
    params.wDirIsUnit = 0;
    params.pExtra = 0;
    pCtxWalk = pStage;
    for (; nCtx < 24; nCtx++, pCtxWalk = (Ov002SpotStage *)((char *)pCtxWalk + 0x184)) {
        nSlot = func_ov002_0207285c(nCtx);
        if (nSlot < 0) continue;
        pRow = pCtxWalk->aCtx[0].pHead;
        while (pRow != 0) {
            pNext = pRow->pNext;
            if (pRow->pActionOwner != 0) {
                vAttract = pRow->pActionOwner->vAttractPosition;
                vAttract.y += pRow->pActionOwner->nAttractHeight;
                VEC_Subtract(&vAttract, &pRow->vPos, &vDirection);
                nDistance = func_01ff8d18(&vDirection, &vDirection);
                pRow->nSpin += nScale >> 4;
                if (pRow->nSpin > 0x1000) pRow->nSpin = 0x1000;
                if (pRow->nSpin >= 0x1000 && nDistance < 0x800) {
                    func_ov002_02077df0(pRow);
                    pRow = pNext;
                    continue;
                }
                vBlend.x = MulRound(-vDirection.z, (0x1000 - pRow->nSpin) * pRow->nSpinDirection);
                vBlend.z = MulRound(vDirection.x, (0x1000 - pRow->nSpin) * pRow->nSpinDirection);
                vBlend.y = 0;
                VEC_MultAdd(pRow->nSpin, &vDirection, &vBlend, &vBlend);
                nDistance *= 2;
                if (nDistance > 0x800) nDistance = 0x800;
                pRow->vVel.x = MulRound(vBlend.x, nDistance);
                pRow->vVel.y = MulRound(vBlend.y, nDistance);
                pRow->vVel.z = MulRound(vBlend.z, nDistance);
                VEC_MultAdd(nScale, &pRow->vVel, &pRow->vPos, &pRow->vPos);
                goto copy_position;
            }
            if (pRow->nPower > 0) pRow->nPower--;
            if (pRow->bAtSpot) {
                pRow->nSpin += nScale >> 2;
                pRow->vPos.y = pRow->vVel.y + (data_0203d210[(u16)pRow->nSpin >> 4].nSin >> 4);
                goto copy_position;
            }
            if (pRow->bResting) {
                if (pRow->nHealth > 0 && --pRow->nHealth == 0) {
                    func_ov002_02077df0(pRow);
                    pRow = pNext;
                    continue;
                }
                if (pRow->pGroundElement != 0) {
                    vOrigin = pRow->vPos;
                    vOrigin.y += 0x2000;
                    vDown.z = 0;
                    vDown.x = 0;
                    vDown.y = -0x4000;
                    params.pDir = &vDown;
                    params.pOrigin = &vOrigin;
                    pHit = func_0202c208((u16)nSlot, &params);
                    pRow->pGroundElement = 0;
                    if (pHit != 0) {
                        if (pHit->pState != 0 && (pElementResting = pHit->pState->pPassOwner->pElement) != 0) {
                            pGroundVelocity = func_ov002_02076d04(pElementResting);
                            if (pGroundVelocity != 0) VEC_Add(&pRow->vPos, pGroundVelocity, &pRow->vPos);
                            pRow->pGroundElement = pElementResting;
                        }
                    } else {
                        pRow->vVel.z = 0;
                        pRow->vVel.y = 0;
                        pRow->vVel.x = 0;
                        pRow->bResting = 0;
                    }
                }
                goto copy_position;
            }
            vOrigin = pRow->vPos;
            vOrigin.y -= pRow->nSpeed;
            params.pDir = &pRow->vVel;
            params.pOrigin = &vOrigin;
            params.nRadius = pRow->nSpeed + 0x100;
            pHit = func_0202c208((u16)nSlot, &params);
            if (pHit != 0) {
                pGroundState = pHit->pState;
                pGroundInfo = pHit->pInfo;
                nGroundFraction = pHit->nNearestHit;
            } else nGroundFraction = -1;
            pHit = func_0202c248((u16)nSlot, &params);
            if (pHit != 0) {
                pWallInfo = pHit->pInfo;
                nWallFraction = pHit->nNearestHit;
            } else nWallFraction = -1;
            if (nGroundFraction < 0 && nWallFraction < 0) {
                if (pStage->bCheckMovingPlatforms != 0) {
                    pOldGround = pRow->pGroundElement;
                    pRow->pGroundElement = 0;
                    vOrigin = pRow->vPos;
                    vOrigin.y += 0x2000;
                    vDown.z = 0;
                    vDown.x = 0;
                    vDown.y = -0x4000;
                    params.pDir = &vDown;
                    params.pOrigin = &vOrigin;
                    pHit = func_0202c208((u16)nSlot, &params);
                    if (pHit != 0 && pHit->pState != 0 &&
                        (pElement = pHit->pState->pPassOwner->pElement) != 0 &&
                        pElement->pOwner->wClassFlags == 0x13) {
                        pRow->pGroundElement = pElement;
                        if (pElement == pOldGround) {
                            func_01ffd0e8(pHit->nNearestHit, &vDown, &vOrigin, &vOrigin);
                            if (vOrigin.y >= pRow->vPos.y) {
                                pGroundVelocity = func_ov002_02076d04(pElement);
                                pRow->vPos.y = vOrigin.y;
                                nDot = VEC_DotProductFx16(&pRow->vVel, (const VecFx16 *)&pHit->pInfo->nX);
                                vBounceNormal.x = pHit->pInfo->nX;
                                vBounceNormal.y = pHit->pInfo->nY;
                                vBounceNormal.z = pHit->pInfo->nZ;
                                VEC_MultAdd(-2 * nDot, &vBounceNormal, &pRow->vVel, &pRow->vVel);
                                if (pRow->vVel.y < 0) pRow->vVel.y = -pRow->vVel.y;
                                if (pGroundVelocity != 0 && pGroundVelocity->y > 0)
                                    pRow->vVel.y += pGroundVelocity->y * 2;
                                goto apply_velocity;
                            }
                        }
                    }
                }
                VEC_Add(&pRow->vPos, &pRow->vVel, &pRow->vPos);
                pRow->vVel.y -= nGravity;
            } else if (nGroundFraction >= 0 && (nWallFraction < 0 || nGroundFraction <= nWallFraction)) {
                vGround = pRow->vPos;
                pRow->pGroundElement = 0;
                if (pGroundState != 0 && (pElementGround = pGroundState->pPassOwner->pElement) != 0) {
                    pGroundVelocity = func_ov002_02076d04(pElementGround);
                    if (pGroundVelocity != 0 && pGroundVelocity->y > 0) vGround.y += pGroundVelocity->y;
                    pRow->pGroundElement = pElementGround;
                }
                nDot = VEC_DotProductFx16(&vGround, (const VecFx16 *)&pGroundInfo->nX) - pGroundInfo->nPlaneDistance;
                if (nDot >= 0) {
                    vGroundNormal.x = 0;
                    vGroundNormal.y = pRow->nSpeed - Abs(nDot);
                    vGroundNormal.z = 0;
                } else {
                    vGroundNormal.x = 0;
                    vGroundNormal.y = -Abs(nDot);
                    vGroundNormal.z = 0;
                }
                VEC_Add(&vGroundNormal, &vGround, &vGround);
                nDot = VEC_DotProductFx16(&pRow->vVel, (const VecFx16 *)&pGroundInfo->nX);
                vGroundNormal.x = pGroundInfo->nX;
                vGroundNormal.y = pGroundInfo->nY;
                vGroundNormal.z = pGroundInfo->nZ;
                VEC_MultAdd(-2 * nDot, &vGroundNormal, &pRow->vVel, &pRow->vVel);
                pRow->vVel.x /= 2;
                pRow->vVel.y /= 2;
                pRow->vVel.z /= 2;
                if (Abs(pRow->vVel.y) < 0x100) pRow->bResting = 1;
                pRow->vPos = vGround;
            } else if (nWallFraction >= 0) {
                vNegative.x = -pRow->vVel.x;
                vNegative.y = -pRow->vVel.y;
                vNegative.z = -pRow->vVel.z;
                nDot = 2 * VEC_DotProductFx16(&vNegative, (const VecFx16 *)&pWallInfo->nX);
                vReflected.x = (int)((((s64)nDot * pWallInfo->nX) >> 12) - vNegative.x);
                vReflected.y = (int)((((s64)nDot * pWallInfo->nY) >> 12) - vNegative.y);
                vReflected.z = (int)((((s64)nDot * pWallInfo->nZ) >> 12) - vNegative.z);
                pRow->vVel = vReflected;
            } else {
apply_velocity:
                VEC_Add(&pRow->vPos, &pRow->vVel, &pRow->vPos);
                pRow->vVel.y -= nGravity;
            }
            if (pRow->vPos.y < -0x64000) {
                if (pRow->bPlaced) func_ov002_02078120(pRow);
                else func_ov002_02077df0(pRow);
            }
copy_position:
            pRow->vHome = pRow->vPos;
            pRow = pNext;
        }
    }
}

#pragma pop
