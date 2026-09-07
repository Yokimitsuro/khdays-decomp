/* ov022: the actor's per-frame tick.
 *
 * Snapshots the previous position, refreshes the facing angle from the node,
 * then takes either the local player's path -- input, state machine, recoil,
 * ground clamp, position write-back -- or the remote replay path, steps the
 * cue queue, drives the sub-object and finally re-enables rendering.
 *
 * The object carries TWO 64-bit flag words, at 0x00 and 0x464, and every test
 * and clear touches both halves; the low mask of a clear is derived from the
 * high one with a single add.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

/* The game copies vectors through a pointer round-trip rather than by plain
 * struct assignment. Where the two objects are distinct this compiles to the
 * same ldm/stm pair a plain assignment would, but it also survives the two
 * cases the compiler would otherwise fold away: copying the position onto
 * itself, and staging a value through a local before storing it.
 */
#define VEC_COPY(pDst, pSrc) (*(pDst) = *(struct Vec3 *)(void *)(pSrc))

struct NodeAnim {
    u32 nOpaque;
};

struct Node {
    u32 nFlags;                  /* 0x000 */
    struct NodeAnim anim;        /* 0x004 */
    u8 pad008[0x1c];
    u32 nRenderFlags;            /* 0x024 */
    u8 pad028[0x58];
    u16 nAngle;                  /* 0x080 */
    u8 pad082[0x26];
    struct Vec3 vecPos;          /* 0x0a8 */
    u8 pad0b4[0x94];
    u32 nField148;               /* 0x148 */
};

struct Sub {
    u8 pad000[0x60];
    u16 nAim : 8;                /* 0x060, extracted with a shift pair */
    u16 nRest60 : 8;
    u8 pad062[0x12e];
    struct Vec3 vecTarget;       /* 0x190 */
};

struct Actor;
typedef void *(*PfnState)(struct Actor *pActor);

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 nOwner;                   /* 0x008 */
    u8 nId;                      /* 0x009 */
    u8 pad00a[8];
    u16 nHp;                     /* 0x012 */
    u8 pad014[0xc];
    struct Node *pNode;          /* 0x020 */
    u8 pad024[4];
    struct Vec3 vecVel;          /* 0x028 */
    u8 pad034[0x24];
    int nRecoil;                 /* 0x058 */
    u8 pad05c[0xa];
    short nSlotIndex;            /* 0x066 */
    u8 pad068[0x9c];
    int nFloorY;                 /* 0x104 */
    u8 pad108[4];
    int nHasFloor;               /* 0x10c */
    u8 pad110[0x350];
    PfnState pfnState;           /* 0x460 */
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[0xe];
    char nField47a;              /* 0x47a */
    char nField47b;              /* 0x47b */
    u8 pad47c[0xc];
    u32 nFacingAngle;            /* 0x488 */
    struct Vec3 vecPos;          /* 0x48c */
    struct Vec3 vecStep;         /* 0x498 */
    u8 pad4a4[0x28];
    int nStateTimer;             /* 0x4cc */
    u8 pad4d0[0x1c];
    struct Sub *pSub;            /* 0x4ec */
    u8 pad4f0[0x1a4];
    u8 bSuppressDraw : 1;        /* 0x694 */
    u8 nRest694 : 7;
    u8 pad695[0x11b];
    int nAnimHandle;             /* 0x7b0 */
    u8 pad7b4[0x144];
    struct Vec3 vecFacing;       /* 0x8f8 */
    struct Vec3 vecPrevPos;      /* 0x904 */
    u8 pad910[0x480];
    u8 subA[0x10];               /* 0xd90 */
    u8 subB[0x1558];             /* 0xda0 */
    u8 subC[0x370];              /* 0x22f8 */
    int nField2668;              /* 0x2668 */
};

extern u8 data_0204be04;

extern void func_ov022_020ad44c(struct Vec3 *pOut, struct Actor *pActor);
extern void func_ov022_0209ca88(struct Actor *pActor);
extern int func_02030788(void);
extern int func_ov022_0208868c(void);
extern void func_ov022_020a2978(struct Actor *pActor);
extern int func_0202aee0(struct NodeAnim *pAnim, int nFlags);
extern void *func_ov022_0209a6f4(struct Actor *pActor);
extern void func_ov022_020a31b4(struct Actor *pActor);
extern void func_ov022_02096644(struct Actor *pActor);
extern void func_ov022_02096984(struct Actor *pActor);
extern int func_ov022_02083f90(void);
extern void *func_ov022_0209ab1c(struct Actor *pActor);
extern void func_ov022_02097f08(struct Actor *pActor);
extern void func_ov022_0209a1ac(struct Actor *pActor);
extern void func_ov022_0209a264(struct Actor *pActor);
extern int func_ov002_02072754(int nSlot);
extern int func_ov002_02072978(int nArea);
extern int VEC_Mag(const struct Vec3 *pVec);
extern void func_0202de3c(struct Node **ppNode, int nOn);
extern void func_0202b450(struct Node *pNode, const struct Vec3 *pPos);
extern int func_01ff8e94(const struct Vec3 *pA, const struct Vec3 *pB);
extern int func_ov022_02088338(void);
extern void func_ov022_0209fd54(struct Actor *pActor);
extern void func_ov022_020965b8(struct Actor *pActor);
extern void func_ov022_020b1a24(void *pObj);
extern void func_ov022_020b1c4c(void *pObj);
extern void func_ov022_0209bfc0(struct Actor *pActor);
extern void func_ov022_02097150(struct Actor *pActor);
extern int func_ov022_020ad7b0(struct Actor *pActor);
extern int func_ov022_02095524(void *pObj);
extern void func_ov002_02056a78(u8 nId, int nOn);
extern void func_ov022_02097d20(struct Actor *pActor);
extern void func_ov022_0209a3a4(struct Vec3 *pOut, struct Actor *pActor);
extern void func_ov107_020c5c54(struct Sub *pSub, const struct Vec3 *pPos);
extern void func_ov002_02078bac(int nArea, struct Sub *pSub, u8 nId);
extern void func_ov022_0209a68c(struct Actor *pActor, int nOn);
extern void func_0202aa9c(struct NodeAnim *pAnim);

void func_ov022_020a0008(struct Actor *pActor)
{
    struct Vec3 vecClamp;
    struct Vec3 vecReplay;
    struct Vec3 vecSubCopy;
    struct Vec3 vecFacing;
    struct Vec3 vecSubPos;
    int nGround;
    int nEnable;
    void *pNext;

    VEC_COPY(&pActor->vecPrevPos, &pActor->vecPos);
    VEC_COPY(&pActor->vecPos, &pActor->vecPos);

    pActor->nFacingAngle = (u16)(pActor->pNode->nAngle - 0x8000);
    pActor->nField47a = -1;
    pActor->nField47b = 0;
    func_ov022_020ad44c(&vecFacing, pActor);
    VEC_COPY(&pActor->vecFacing, &vecFacing);
    func_ov022_0209ca88(pActor);

    if (((pActor->nFlags & (1ULL << 33)) != 0 || (pActor->nFlags & (1ULL << 28)) != 0)
        && func_02030788() == 0) {
        pActor->nFlags2 |= (1ULL << 24);
    }
    pActor->pNode->nRenderFlags &= ~1;
    if (data_0204be04 == 0
        && pActor->nOwner == func_02030788()
        && func_ov022_0208868c() == 0
        && (pActor->nFlags & (1ULL << 16)) == 0) {
        func_ov022_020a2978(pActor);
    }

    if (func_02030788() == 0) {
        pActor->nAnimHandle = func_0202aee0(&pActor->pNode->anim, 0);
        pNext = func_ov022_0209a6f4(pActor);
        if (pNext != 0) {
            pActor->pfnState = (PfnState)pNext;
        }
        func_ov022_020a31b4(pActor);
        func_ov022_02096644(pActor);
        func_ov022_02096984(pActor);
        if (pActor->pfnState != 0) {
            pNext = pActor->pfnState(pActor);
            if (pNext != 0) {
                pActor->pfnState = (PfnState)pNext;
            } else {
                pActor->nStateTimer += func_ov022_02083f90();
            }
        }
        pNext = func_ov022_0209ab1c(pActor);
        if (pNext != 0) {
            pActor->pfnState = (PfnState)pNext;
        }
        func_ov022_02097f08(pActor);
        func_ov022_0209a1ac(pActor);
        func_ov022_0209a264(pActor);
        nGround = func_ov002_02072978(func_ov002_02072754(pActor->nSlotIndex)) - 0x2000;
        if (pActor->nRecoil > 0) {
            if (nGround <= pActor->vecPos.y) {
                pActor->nRecoil = 0;
            }
        }
        pActor->vecVel.x = pActor->vecStep.x;
        pActor->vecVel.y = 0;
        pActor->vecVel.z = pActor->vecStep.z;
        if ((pActor->nFlags & (1ULL << 36)) != 0
            && (pActor->nFlags2 & (1ULL << 7)) != 0
            && VEC_Mag(&pActor->vecVel) < 0x200) {
            pActor->vecVel.z = 0;
            pActor->vecVel.y = 0;
            pActor->vecVel.x = 0;
        }
        if ((pActor->nFlags2 & (1ULL << 23)) == 0) {
            func_0202de3c(&pActor->pNode, 1);
        }
        if (nGround <= pActor->pNode->vecPos.y) {
            VEC_COPY(&vecClamp, &pActor->pNode->vecPos);
            vecClamp.y = nGround;
            func_0202b450(pActor->pNode, &vecClamp);
        }
        pActor->pNode->nField148 = 0x900;
        pActor->vecStep.x = pActor->vecStep.y = pActor->vecStep.z = 0;
        if ((pActor->nFlags & (1ULL << 43)) != 0
            && func_01ff8e94(&pActor->pNode->vecPos, &pActor->vecPos) < 4) {
            pActor->nFlags &= ~(1ULL << 43);
        }
        if ((pActor->nFlags & (1ULL << 46)) != 0) {
            VEC_COPY(&vecReplay, &pActor->pNode->vecPos);
            if (pActor->nHasFloor != 0
                && vecReplay.y - pActor->nFloorY < 0x400) {
                vecReplay.y = pActor->nFloorY + 0x400;
                func_0202b450(pActor->pNode, &vecReplay);
                VEC_COPY(&pActor->vecPos, &vecReplay);
            }
            pActor->nFlags &= ~(1ULL << 46);
        }
        VEC_COPY(&pActor->vecPos, &pActor->pNode->vecPos);
    } else if (func_ov022_02088338() != 0) {
        func_ov022_02096644(pActor);
        func_ov022_02096984(pActor);
        func_ov022_0209fd54(pActor);
        pActor->nAnimHandle = func_0202aee0(&pActor->pNode->anim, 0);
    }

    if (pActor->nOwner == func_02030788() && pActor->nHp == 0) {
        pActor->nField2668 = 0;
    }
    func_ov022_020965b8(pActor);
    func_ov022_020b1a24(pActor->subA);
    func_ov022_020b1c4c(pActor->subB);
    func_ov022_0209bfc0(pActor);
    func_ov022_02097150(pActor);
    if (data_0204be04 == 0 && (pActor->nFlags & (1ULL << 8)) == 0) {
        if (func_ov022_020ad7b0(pActor) != 0
            && func_ov022_02095524(pActor->subC) == 0) {
            if (pActor->nHp != 0) {
                func_ov002_02056a78(pActor->nId, 1);
            }
        } else {
            func_ov002_02056a78(pActor->nId, 0);
        }
    }
    func_ov022_02097d20(pActor);
    nEnable = 0;
    if (pActor->pSub != 0) {
        struct Sub *pSub;

        func_ov022_0209a3a4(&vecSubPos, pActor);
        VEC_COPY(&vecSubCopy, &vecSubPos);
        pSub = pActor->pSub;
        VEC_COPY(&pSub->vecTarget, &vecSubCopy);
        func_ov107_020c5c54(pSub, &pSub->vecTarget);
        if ((pActor->nFlags & (1ULL << 34)) == 0
            && (pActor->pSub->nAim & 0x80) > 0
            && func_02030788() == 0) {
            pActor->nFlags2 |= (1ULL << 33);
        }
        if (pActor->nSlotIndex >= 0 && pActor->nHp != 0) {
            func_ov002_02078bac(func_ov002_02072754(pActor->nSlotIndex),
                                pActor->pSub, pActor->nId);
        }
    }
    if ((pActor->nFlags & (1ULL << 42)) != 0) {
        nEnable = 1;
    }
    if ((pActor->nFlags2 & (1ULL << 33)) != 0) {
        nEnable = 1;
    }
    func_ov022_0209a68c(pActor, nEnable);
    pActor->pNode->nRenderFlags |= 1;
    if (pActor->bSuppressDraw != 0) {
        return;
    }
    pActor->pNode->nRenderFlags |= 3;
    if ((pActor->pNode->nFlags & 0x20) == 0) {
        func_0202aa9c(&pActor->pNode->anim);
    }
    pActor->pNode->nRenderFlags &= ~3;
}

