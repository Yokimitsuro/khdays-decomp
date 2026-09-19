typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct MtxFx33 {
    int m[3][3];
} MtxFx33;

typedef struct Ov084RadialBurstFrame {
    MtxFx33 mRotation;
    VecFx32 vSpawnPosition;
    VecFx32 vRadialOffset;
    VecFx32 vOrigin;
} Ov084RadialBurstFrame;

typedef struct Ov084HeadingSource {
    u8 pad00[0x80];
    u16 nHeading;
} Ov084HeadingSource;

typedef struct Ov084EffectPart {
    u8 pad00[2];
    s8 nState;
    u8 pad03;
    int nLifetime;
    u8 pad08[0x22];
    short nPhase;
    u8 pad2c[0xa0];
    VecFx32 vPosition;
} Ov084EffectPart;

typedef struct Ov084SceneFlags {
    u8 bSlotSpawnEnabled : 1;
    u8 rest : 7;
} Ov084SceneFlags;

typedef struct Ov084SceneState {
    u32 nFlags;
    u8 pad04[0x1c];
    Ov084HeadingSource *pHeadingSource;
    u8 pad24[0x456];
    u8 nPendingMode;
    u8 nPendingIndex;
    u8 pad47c[0x218];
    Ov084SceneFlags slotSpawnFlags;
    u8 pad695[0x25eb];
    u8 aSlotPool[4];
} Ov084SceneState;

extern Ov084SceneState *data_ov084_020b9a20;
extern const short data_0203d210[];

extern void MTX_RotY33_(MtxFx33 *m, int nSin, int nCos);
extern void MTX_MultVec33(VecFx32 *src, MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *dst);
extern void func_ov084_020b929c(int slotPool, VecFx32 *position);
extern int func_02030788(void);
extern void func_02033d0c(int slotId, int variant, VecFx32 *position,
                          int flags);

int func_ov084_020b8b18(void *pContext, Ov084EffectPart *pPart, int nDelta)
{
    const short *pSinCosTable;
    MtxFx33 *pRotation;
    Ov084RadialBurstFrame f;
    int nSpawnVariant;
    int nAngle;
    Ov084SceneState *pScene;

    pScene = data_ov084_020b9a20;
    pPart->nState = 4;
    pPart->nLifetime = 0x3000;
    nSpawnVariant = 0;
    if (pPart->nPhase == 2) {
        f.vOrigin = pPart->vPosition;
        pSinCosTable = data_0203d210;
        nAngle = (u16)(pScene->pHeadingSource->nHeading - 0x8000);
        pRotation = &f.mRotation;
        do {
            int nTrigIndex = nAngle >> 4;

            f.vRadialOffset.x = 0;
            f.vRadialOffset.y = 0;
            f.vRadialOffset.z = 0x3000;
            MTX_RotY33_(pRotation,
                        -pSinCosTable[nTrigIndex * 2],
                        -pSinCosTable[nTrigIndex * 2 + 1]);
            MTX_MultVec33(&f.vRadialOffset, pRotation, &f.vRadialOffset);
            VEC_Add(&f.vRadialOffset, &f.vOrigin, &f.vSpawnPosition);
            func_ov084_020b929c((int)pScene->aSlotPool, &f.vSpawnPosition);
            nAngle = (u16)(nAngle + 0x5555);
            nSpawnVariant++;
        } while (nSpawnVariant < 3);
        func_02030788();
        nSpawnVariant = 1;
    } else if (pPart->nPhase == 1
               && func_02030788() == 0
               && (int)(*(long long *)pScene & 0x10000) == 0) {
        pScene->nPendingMode = 3;
        pScene->nPendingIndex = nSpawnVariant;
    }
    if (pScene->slotSpawnFlags.bSlotSpawnEnabled != 0) {
        func_02033d0c(0xd6, nSpawnVariant, &pPart->vPosition, 0);
    }
    return 0;
}

