/* ov022: build the wind effect for one actor.
 *
 * Registers the effect's animation against its own descriptor, opens the
 * actor's own resource container and loads the file the actor's index selects
 * out of it, binds that file to the animation and drops the container again.
 * The pose table then gives the row for this wind strength, clamped to nine,
 * and the table is freed straight away because only that row is wanted.
 * Finally the effect points its render object back at itself and arms the node
 * hook, so the walker calls func_ov022_020928d8 while drawing the model.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* One row of the pose table: the pair the wind strength selects. */
struct PoseRow {
    int nA;
    int nB;
};

/* The SDK render object the walker drives, embedded in the animation. */
struct RenderObj {
    u8 pad0000[0x2c];
    void *pOwner;                 /* 0x002c, the SDK's spare user slot */
    u8 pad0030[0x1c];
};

struct Anim {
    u8 pad0000[0x20];
    struct RenderObj obj;         /* 0x0020 */
    u8 pad006c[0x9c];
};

struct WindEffect {
    u8 nFlags;                    /* 0x0000 */
    u8 pad0001[3];
    struct Anim anim;             /* 0x0004 */
    u8 blkBind[0x24];             /* 0x010c */
    void *pFile;                  /* 0x0130 */
    u8 nSlotId;                   /* 0x0134 */
    u8 pad0135[3];
    VecFx32 vecPos;               /* 0x0138 */
    u8 pad0144[0x2c];
    int nField170;                /* 0x0170, the pair the tick owns */
    int nField174;                /* 0x0174 */
    struct PoseRow pose;          /* 0x0178 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                       /* 0x0009 */
    u8 pad000a[2];
    u32 nContainerIndex;          /* 0x000c */
};

extern char data_ov022_020b2b94[];
extern char data_ov022_020b2ba4[];
extern char data_ov022_020b2bb0[];

extern void func_ov022_020928d8(void *pState);

extern void func_0202a634(struct Anim *pAnim, char *pszDescriptor, int nA,
                          int nB);
extern void *func_02024ee8(char *pszName, int nHeap);
extern void *func_0201ef9c(u32 nFile, int nSlot);
extern void func_0202a3cc(void *pBind, struct Anim *pAnim, void *pFile,
                          int nSlot);
extern void func_02024fd4(void *pContainer);
extern void func_0202accc(struct Anim *pAnim, int nTrack, void *pBind,
                          int nGroup);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_02014e18(void *pObj, void *pfnHook, int nA, int nCommand,
                          int nTiming);

void func_ov022_02092a14(struct WindEffect *pEffect, int nCount,
                         struct Actor *pActor)
{
    struct PoseRow *pRow;
    void *pContainer;
    struct PoseRow *pTable;
    u32 nMask;

    if (nCount <= 0) {
        return;
    }
    pEffect->nSlotId = pActor->nId;
    func_0202a634(&pEffect->anim, data_ov022_020b2b94, 1, 5);
    pContainer = func_02024ee8(data_ov022_020b2ba4, 6);
    /* The mask is one value: the ROM loads 0xfffffc once and shifts it right
     * by fifteen for the index mask. */
    nMask = 0xfffffc;
    pEffect->pFile = func_0201ef9c(
            ((((u32)pContainer + 0x8000) & nMask) << 7) | 0x80000000
            | (pActor->nContainerIndex & (nMask >> 15)),
            pEffect->nSlotId + 7);
    func_0202a3cc(pEffect->blkBind, &pEffect->anim, pEffect->pFile,
                  pEffect->nSlotId + 7);
    func_02024fd4(pContainer);
    func_0202accc(&pEffect->anim, 0, pEffect->blkBind, 0);
    pTable = func_0201ef9c((u32)data_ov022_020b2bb0, 6);
    if (nCount > 9) {
        nCount = 9;
    }
    pRow = pTable;
    pRow += nCount - 1;
    pEffect->pose = *pRow;
    NNSi_FndFreeFromDefaultHeap(pTable);
    pEffect->anim.obj.pOwner = pEffect;
    func_02014e18(&pEffect->anim.obj, (void *)func_ov022_020928d8, 0, 6, 3);
    pEffect->nFlags |= 1;
    pEffect->nField170 = 0;
    pEffect->nField174 = 0;
}
