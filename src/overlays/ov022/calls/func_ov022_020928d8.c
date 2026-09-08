/* ov022: the wind effect's node hook, run once by the model walker.
 *
 * The effect registers this on its render object as the callback for one
 * geometry command; the walker then calls it for every node it reaches. It
 * only acts on the node named in the pool, and only while the walker is
 * actually reporting a node index. On that node it takes the two matrices the
 * walker has built so far, replaces the clip matrix's translation with the
 * effect's own world position, and reloads both through the geometry FIFO, so
 * everything drawn from here on rides the node's orientation but sits where
 * the effect is. Clearing the callback slot and its timing byte stops it
 * firing again for the rest of the walk.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* The walker's two matrices: the clip matrix carries a translation, the
 * directional one is only ever a rotation. */
typedef struct {
    int m[9];
    VecFx32 t;
} MtxFx43;

typedef struct {
    int m[9];
} MtxFx33;

struct WindEffect {
    u8 pad0000[0x138];
    VecFx32 vecPos;               /* 0x0138 */
};

struct RenderObj {
    u8 pad0000[4];
    void *pResMdl;                /* 0x0004 */
    u8 pad0008[0x24];
    struct WindEffect *pOwner;    /* 0x002c, the SDK's spare user slot */
};

struct RenderState {
    u8 pad0000[4];
    struct RenderObj *pRenderObj; /* 0x0004 */
    u32 nFlags;                   /* 0x0008, bit 4 = the node index is live */
    u8 pad000c[0x18];
    u32 pfnCallback;              /* 0x0024, this hook's own slot */
    u8 pad0028[0x6a];
    u8 nCallbackTiming;           /* 0x0092, the timing byte beside it */
    u8 pad0093[0x1b];
    u8 nNodeId;                   /* 0x00ae */
};

extern char data_ov022_020b24e4[];   /* "ef_wind_B01" */

extern int func_02016f10(void *pDict, const char *pszName);
extern void func_02016294(MtxFx43 *pClip, MtxFx33 *pDirection);
extern void func_01ff9f00(u32 nCmd, const void *pSrc, u32 nWords);

static inline void *GetNodeDict(void *pResMdl)
{
    return pResMdl != 0 ? (void *)((u8 *)pResMdl + 0x40) : (void *)0;
}

static inline int FindNodeByName(void *pResMdl, const char *pszName)
{
    void *pDict;

    pDict = GetNodeDict(pResMdl);
    return pDict != 0 ? func_02016f10(pDict, pszName) : -1;
}

static inline void SetMtxMode(u32 nMode)
{
    u32 nCmd;

    nCmd = nMode;
    func_01ff9f00(0x10, &nCmd, 1);
}

void func_ov022_020928d8(struct RenderState *pState)
{
    MtxFx33 mDirection;
    MtxFx43 mClip;
    struct RenderObj *pRenderObj;
    struct WindEffect *pOwner;
    int nWanted;
    int nNodeId;

    pRenderObj = pState->pRenderObj;
    pOwner = pRenderObj->pOwner;
    nWanted = FindNodeByName(pRenderObj->pResMdl, data_ov022_020b24e4);
    nNodeId = (pState->nFlags & 0x10) != 0 ? (int)pState->nNodeId : -1;
    if (nNodeId != nWanted) {
        return;
    }
    func_02016294(&mClip, &mDirection);
    mClip.t.x = pOwner->vecPos.x;
    mClip.t.y = pOwner->vecPos.y;
    mClip.t.z = pOwner->vecPos.z;
    SetMtxMode(2);
    /* The directional matrix is only a rotation, so the three words the 4x3
     * load reads past it are never used. */
    func_01ff9f00(0x17, &mDirection, 12);
    SetMtxMode(1);
    func_01ff9f00(0x17, &mClip, 12);
    SetMtxMode(2);
    pState->pfnCallback = 0;
    pState->nCallbackTiming = 0;
}
