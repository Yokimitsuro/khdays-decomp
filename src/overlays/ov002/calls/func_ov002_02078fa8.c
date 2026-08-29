typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

/* The description a piece works from; the two slots a piece can occupy each
   have their own binding and their own spawn argument. */
typedef struct Ov002PieceInfo {
    char pad000[0x74];
    int aBinding[2];            /* 0x74 */
    char pad07c[2];
    s16 nSpawnKind;             /* 0x7e, negative when nothing is spawned */
    s16 aSpawnArg[2];           /* 0x80 */
} Ov002PieceInfo;

typedef struct Ov002PieceObj {
    char pad000[8];
    Ov002PieceInfo *pInfo;      /* 0x08 */
    char pad00c[6];
    u16 nFlags;                 /* 0x12, bit 2 live, bit 3 bound */
    char pad014[0x28];
    char anim[0xa4];            /* 0x3c, the piece's animation node */
    char spawn[0xd4];           /* 0xe0, the spawn parameters */
    int nProgress;              /* 0x1b4 */
    u8 nSlot;                   /* 0x1b8 */
    u8 nState;                  /* 0x1b9 */
    u8 nDenom;                  /* 0x1ba */
    u8 bLatched;                /* 0x1bb */
} Ov002PieceObj;

/* MSL's signed divide helper: the quotient comes back in the low word and
   the remainder in the high one, which is why the caller shifts. */
extern long long func_02020400(int nNum, int nDen);
extern void func_ov002_0207c618(void *pNode, int nPhase,
                               int nMode);
extern void func_0202af1c(void *pNode);
extern void func_02033d0c(int nKind, int nArg, void *pParams, int nFlags);

/* Move a piece to another slot.
 *
 * The phase the animation is rebound at comes from the remainder of the old
 * slot position over the piece cycle, so a live piece keeps its place in the
 * cycle across the move; its node is then re-enabled.  The piece is put back
 * into state 2 with its progress cleared, picks up whether the new slot has
 * a binding at all, and if the description asks for a spawn on that slot the
 * spawn is kicked off.
 */
void func_ov002_02078fa8(Ov002PieceObj *pObj, int nSlot)
{
    Ov002PieceInfo *pInfo;
    long long qDiv;

    qDiv = func_02020400(pObj->nSlot * 2 + 1, pObj->nDenom);
    pInfo = pObj->pInfo;
    pObj->nState = 2;
    pObj->nSlot = (u8)nSlot;
    pObj->nProgress = 0;

    if ((pObj->nFlags & 4) != 0) {
        func_ov002_0207c618(pObj->anim, (int)(qDiv >> 32), 0);
        func_0202af1c(pObj->anim);
        pObj->bLatched &= ~1;
    }

    if (pInfo->aBinding[pObj->nSlot] == 0) {
        pObj->nFlags &= ~8;
    } else {
        pObj->nFlags |= 8;
    }

    if (pInfo->nSpawnKind >= 0 && pInfo->aSpawnArg[nSlot] >= 0) {
        func_02033d0c(pInfo->nSpawnKind, pInfo->aSpawnArg[nSlot],
                      pObj->spawn, 0);
    }
}
