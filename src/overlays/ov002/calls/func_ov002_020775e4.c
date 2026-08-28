typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Ov002Vec3 {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct Ov002Rng {
    int nSeed;
    int nMult;
    int nInc;
} Ov002Rng;

typedef struct Ov002SpawnCtx {
    char pad000[0xc];
    int nBound;                 /* +0x0c, nonzero once the model is bound */
} Ov002SpawnCtx;

typedef struct Ov002Spawned {
    char pad000[8];
    char *pAnim;                /* +0x08 */
    Ov002Vec3 vHome;            /* +0x0c */
    s16 nSpanA;                 /* +0x18 */
    s16 nSpanB;                 /* +0x1a */
    u8 bStateA;                 /* +0x1c */
    u8 bStateB;                 /* +0x1d */
    s8 nDescB;                  /* +0x1e */
    s8 nDescC;                  /* +0x1f */
    s16 nMask;                  /* +0x20 */
    s16 nPhase;                 /* +0x22 */
    Ov002SpawnCtx *pCtx;        /* +0x24 */
    int nField28;               /* +0x28 */
    s8 nKind;                   /* +0x2c */
    u8 nSpotId;                 /* +0x2d */
    u16 nTier;                  /* +0x2e */
    u8 bFlag0 : 1;              /* +0x30 */
    u8 bFlag1 : 1;
    u8 bPlaced : 1;
    u8 bAtSpot : 1;
    char pad031;
    s8 nCtxIndex;               /* +0x32 */
    char pad033;
    s16 nSpin;                  /* +0x34 */
    s16 nHealth;                /* +0x36 */
    s16 nPower;                 /* +0x38 */
    char pad03a[2];
    int nSpeed;                 /* +0x3c */
    Ov002Vec3 vPos;             /* +0x40 */
    Ov002Vec3 vVel;             /* +0x4c */
    int nField58;               /* +0x58 */
} Ov002Spawned;

typedef struct Ov002SpotStage {
    char pad000[0x4e];
    u16 nRowStride;             /* +0x4e */
    char pad050[4];
    char *pRows;                /* +0x54 */
    char pad058[4];
    u32 *pFreeBits;             /* +0x5c */
    char aAnim[0x58];           /* +0x60, eleven entries of eight bytes */
    char aCtx[1];               /* +0xb8, entries of 0x184 bytes */
} Ov002SpotStage;

typedef struct Ov002SpotHolder {
    s8 nSpinIndex;              /* +0x00, wraps every four spawns */
    char pad001[3];
    Ov002SpotStage *pStage;     /* +0x04 */
} Ov002SpotHolder;

typedef struct Ov002SpotDesc {
    s8 nAnim;                   /* +0x00 */
    s8 nDescB;                  /* +0x01 */
    s8 nDescC;                  /* +0x02 */
    char pad003;
    s16 nHealth;                /* +0x04 */
    s16 nPower;                 /* +0x06 */
} Ov002SpotDesc;

extern Ov002SpotHolder data_ov002_0207fa28;
extern Ov002SpotDesc data_ov002_0207e67c[];
extern u8 data_0204c058;                    /* 0 = easy, 1 = hard, 2 = normal */

extern void func_02025668(u32 *pBits, int nIndex);      /* clear the free bit */
extern int func_ov002_0207285c(int nCtxIndex);          /* ctx -> model id */
extern void func_0202c5b8(Ov002SpawnCtx *pCtx, u16 nModel);
extern void func_0202c604(Ov002SpawnCtx *pCtx, Ov002Spawned *pRow);

/* Fills in the row for one spot and hands it back.  The spot's bit is cleared
   first, so the id is taken as soon as this runs.

   nMode picks how the row starts moving: 0 draws a scattered velocity off the
   stage's generator, 1 sends it straight up, and 2 and 3 leave it still, with 3
   also marking the row as sitting on its spot.  The mode global then rescales
   what the descriptor supplied: on easy the two descriptor shorts are halved,
   and on hard the velocity grows by half while the shorts are divided by
   three. */
Ov002Spawned *func_ov002_020775e4(int nSpotId, int nKind, int nTier,
                                  int nCtxIndex, const Ov002Vec3 *pPlace,
                                  int nMode, Ov002Rng *pRng)
{
    Ov002SpotStage *pStage;
    Ov002Spawned *pRow;
    Ov002SpotDesc *pDesc;
    int nAnim;
    int nModel;
    int nSpin;

    pDesc = &data_ov002_0207e67c[nKind];
    func_02025668(data_ov002_0207fa28.pStage->pFreeBits, nSpotId);

    pStage = data_ov002_0207fa28.pStage;
    pRow = (Ov002Spawned *)(pStage->pRows + pStage->nRowStride * nSpotId);
    pRow->pCtx = (Ov002SpawnCtx *)(pStage->aCtx + nCtxIndex * 0x184);
    pRow->nField28 = 0;
    pRow->nKind = (s8)nKind;
    pRow->nSpotId = (u8)nSpotId;
    pRow->nTier = (u16)nTier;
    pRow->bFlag0 = 0;
    pRow->bFlag1 = 0;
    pRow->bAtSpot = (nMode == 3);
    pRow->nHealth = pDesc->nHealth;
    pRow->nPower = pDesc->nPower;
    if (nKind == 1 && nMode != 0) {
        pRow->nHealth = -1;
    }
    pRow->nCtxIndex = (s8)nCtxIndex;

    if (nKind >= 6) {
        pRow->nSpeed = 0x500;
    } else {
        switch (nTier) {
        case 0:
            pRow->nSpeed = 0x200;
            break;
        case 1:
            pRow->nSpeed = 0x380;
            break;
        default:
            pRow->nSpeed = 0x500;
            break;
        }
    }

    pRow->vPos = *pPlace;

    switch (nMode) {
    case 0:
        pRng->nSeed = pRng->nMult * pRng->nSeed + pRng->nInc;
        pRow->vVel.x = (u16)((((u32)pRng->nSeed >> 16) * 0x440) >> 16) - 0x220;
        pRng->nSeed = pRng->nMult * pRng->nSeed + pRng->nInc;
        pRow->vVel.y = (u16)((((u32)pRng->nSeed >> 16) * 0x280) >> 16) + 0x280;
        pRng->nSeed = pRng->nMult * pRng->nSeed + pRng->nInc;
        pRow->vVel.z = (u16)((((u32)pRng->nSeed >> 16) * 0x440) >> 16) - 0x220;
        break;
    case 1:
        pRow->vVel.x = 0;
        pRow->vVel.y = 0x200;
        pRow->vVel.z = 0;
        break;
    case 2:
    case 3:
        pRow->vVel.x = 0;
        pRow->vVel.y = 0;
        pRow->vVel.z = 0;
        break;
    }

    /* Nested rather than an else-if chain: that is what keeps the hard-mode
       arm inline and pushes the easy-mode one past it, the way the ROM lays
       the two out. */
    if (data_0204c058 != 0) {
        if (data_0204c058 == 1) {
            pRow->vVel.x = pRow->vVel.x + pRow->vVel.x / 2;
            pRow->vVel.y = pRow->vVel.y + pRow->vVel.y / 2;
            pRow->vVel.z = pRow->vVel.z + pRow->vVel.z / 2;
            if (pRow->nHealth > 0) {
                pRow->nHealth = pRow->nHealth / 3;
            }
            pRow->nPower = pRow->nPower / 3;
        }
    } else {
        if (pRow->nHealth > 0) {
            pRow->nHealth = pRow->nHealth / 2;
        }
        pRow->nPower = pRow->nPower / 2;
    }

    pRow->nField58 = 0;
    if (pRow->pCtx->nBound == 0) {
        nModel = func_ov002_0207285c(nCtxIndex);
        if (nModel >= 0) {
            func_0202c5b8(pRow->pCtx, (u16)nModel);
        }
    }

    nAnim = pDesc->nAnim;
    if (nKind == 0 && nMode == 3) {
        nAnim = 6;
        pRow->nTier = pRow->nTier + 10;
    } else if (nKind == 0xf && nTier == 3) {
        nAnim = 7;
    }

    pRow->pAnim = data_ov002_0207fa28.pStage->aAnim + nAnim * 8;
    pRow->vHome = pRow->vPos;
    if (pRow->bAtSpot != 0) {
        pRow->vVel = pRow->vPos;
        nSpin = data_ov002_0207fa28.nSpinIndex;
        pRow->nSpin = (s16)(nSpin << 14);
        data_ov002_0207fa28.nSpinIndex = (s8)((nSpin + 1) & 3);
    }

    switch (nKind) {
    case 0:
        pRow->nSpanA = (s16)(pRow->nSpeed << 1);
        pRow->nSpanB = (s16)(pRow->nSpeed << 2);
        break;
    case 1:
        pRow->nSpanA = (s16)(pRow->nSpeed << 2);
        pRow->nSpanB = (s16)(pRow->nSpeed << 2);
        break;
    default:
        pRow->nSpanB = (s16)(pRow->nSpeed << 1);
        pRow->nSpanA = pRow->nSpanB;
        break;
    }

    pRow->bStateB = 0;
    pRow->bStateA = 0;
    pRow->nDescB = pDesc->nDescB;
    pRow->nDescC = pDesc->nDescC;
    pRow->nMask = 0x1f;
    pRow->nPhase = 0;
    func_0202c604(pRow->pCtx, pRow);
    return pRow;
}
