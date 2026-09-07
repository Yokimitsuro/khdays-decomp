/* ov022 actor state entry.
 *
 * Two shapes drive this one. The three-word copy at the top is a struct
 * assignment: mwcc emits ldm/stm only for struct-to-struct copies, never for
 * separately computed words. And the seven bit clears are a 64-bit bitfield --
 * that is why each one loads and stores BOTH words and ANDs the untouched half
 * with an all-ones mask built by mvn/sub.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    u32 x, y, z;
};

struct ActorNode {
    u32 nFlags;
    u16 nNodeFlags;
    u16 nPad;
    u8 nRest[0x7a];
    u16 nField82;
    u8 nRest2[0xc4];
    u32 nField148;
};

struct Actor {
    unsigned long long nFlags;
    u8 pad08[0x18];
    struct ActorNode *pNode;         /* 0x20 */
    u8 pad24[0x40];
    u16 nField64;                    /* 0x64 */
    u8 pad66[0x74e];
    u8 nField7b4;                    /* 0x7b4 */
    u8 pad7b5[0x135];
    struct Vec3 vecZero;             /* 0x8ec */
    u8 pad8f8[0xbd4];
    u32 nField14cc;                  /* 0x4cc from a later base */
};

extern const struct Vec3 data_02041dc8;
extern int func_ov022_020a37d0(void);

extern void func_ov022_020a2954(u32 *pActor);
extern void func_ov022_020acebc(int pActor, int nScale);
extern void func_0202af2c(u16 *pFlags);
extern int func_ov022_02098834(u32 *pActor, int nState, u32 nPrev);

int func_ov022_020a35f4(u32 *pActor, int nState)
{
    struct Actor *pSelf = (struct Actor *)pActor;
    struct ActorNode *pNode;
    int (*pfnHandler)(u32 *, int);
    int bAllowed;
    int nResult;
    u32 nPrev;

    nPrev = pActor[0x133];
    pSelf->vecZero = data_02041dc8;
    nResult = 0;
    pActor[0x133] = 0;
    *((char *)pActor + 0x2bb2) = -1;

    pNode = pSelf->pNode;
    pNode->nField82 = 0;
    pNode->nNodeFlags |= 0x20;
    if (nState != 1 && nState != 2) {
        pSelf->nField7b4 = 0;
    }
    if (pActor[0x13b] != 0) {
        *(u32 *)(pActor[0x13b] + 0x54) = 0x1000;
        *(u32 *)(pActor[0x13b] + 0x70) = 0xa00;
    }
    pSelf->pNode->nField148 = 0x900;
    pSelf->nField64 = 0x666;

    func_ov022_020a2954(pActor);
    func_ov022_020acebc((int)pActor, 0x1000);

    pSelf->nFlags &= ~(1ULL << 1);
    pSelf->nFlags &= ~(1ULL << 20);
    pSelf->nFlags &= ~(1ULL << 21);
    pSelf->nFlags &= ~(1ULL << 3);
    pSelf->nFlags &= ~(1ULL << 22);
    pSelf->nFlags &= ~(1ULL << 26);
    pSelf->nFlags &= ~(1ULL << 14);
    pSelf->nFlags &= ~(1ULL << 49);

    if ((pSelf->pNode->nFlags & 0x20) == 0) {
        func_0202af2c(&pSelf->pNode->nNodeFlags);
    }
    if (nState < 0x21) {
        nResult = func_ov022_02098834(pActor, nState, nPrev);
    }
    bAllowed = 1;
    pfnHandler = (int (*)(u32 *, int))pActor[0x1a1];
    if (pfnHandler != 0) {
        if (nState == 0x10 || nState == 0x1c) {
            bAllowed = 0;
        }
        if (bAllowed) {
            int nOverride = pfnHandler(pActor, nState);
            if (nOverride != 0) {
                nResult = nOverride;
            }
        }
    }
    if (nResult == 0) {
        nResult = (int)&func_ov022_020a37d0;
    }
    return nResult;
}
