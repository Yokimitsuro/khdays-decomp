/* func_ov016_020802e4 -- Ov016_FollowerCheckPieces: walk the seat owner's piece list (ov002
 * 02073880 for the follower's bucket slot, list +0x80) and ask Ov016_FollowerPieceHolds
 * (020801a0) for each piece with the follower's position pFrom, range (+0x1ac), anchor pAt,
 * angle (+0x1b8) and cone (+0x1c8); the first piece that does not hold answers 0, an empty
 * list answers 0, otherwise 1. Without a record set (ov002 0207386c == -1) or an owner: 0. */
typedef unsigned char u8;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016Piece Ov016Piece;

typedef struct Ov016Owner {
    u8 pad_000[0x80];
    u8 pieceList[0xc];        /* 0x80 */
} Ov016Owner;

typedef struct Ov016Follower {
    u8 pad_000[0x10];
    u8 nBucket;               /* 0x10 */
    u8 pad_011[0x1ac - 0x11];
    int nRange;               /* 0x1ac */
    int nHoldTimer;           /* 0x1b0 */
    int nDuration;            /* 0x1b4 */
    int nAngle;               /* 0x1b8 */
    u8 pad_1bc[0x1c8 - 0x1bc];
    int nCone;                /* 0x1c8 */
} Ov016Follower;

extern int  func_ov002_0207386c(void);                    /* record set state */
extern int  func_ov002_0207285c(int nBucket);             /* bucket -> seat slot */
extern Ov016Owner *func_ov002_02073880(int nSlot);        /* seat owner */
extern void *func_01fffd70(void *pList);                  /* List_First */
extern void *func_01fffd8c(void *pList);                  /* List_Next */
extern int  func_ov016_020801a0(Ov016Piece *pPiece, VecFx32 *pFrom, int nRange, VecFx32 *pAt, int nAngle, int nCone);

int func_ov016_020802e4(Ov016Follower *pSelf, VecFx32 *pFrom, VecFx32 *pAt)
{
    Ov016Owner *pOwner;
    Ov016Piece **ppPiece;
    Ov016Piece *pPiece;
    int nCount;

    if (func_ov002_0207386c() == -1) {
        return 0;
    }
    pOwner = func_ov002_02073880(func_ov002_0207285c(pSelf->nBucket));
    if (pOwner == 0) {
        return 0;
    }
    nCount = 0;
    ppPiece = func_01fffd70(pOwner->pieceList);
    pPiece = (ppPiece == 0) ? 0 : *ppPiece;
    while (pPiece != 0) {
        if (func_ov016_020801a0(pPiece, pFrom, pSelf->nRange, pAt, pSelf->nAngle, pSelf->nCone)) {
            return 0;
        }
        ppPiece = func_01fffd8c(pOwner->pieceList);
        pPiece = (ppPiece == 0) ? 0 : *ppPiece;
        nCount++;
    }
    if (nCount == 0) {
        return 0;
    }
    return 1;
}
