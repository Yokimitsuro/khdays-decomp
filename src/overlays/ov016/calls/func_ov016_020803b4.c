/* func_ov016_020803b4 -- Ov016_FollowerComplete: once every player has held its follower, walk
 * the seat owner's piece list (ov002 02073880 for the follower's bucket slot, list +0x80) and,
 * at the first piece whose kind byte (+0x19c) is 'm', fire the completion hooks (ov233
 * 020cc5a8 with the piece and its kind, then ov022 020888b8 with 0 / 1). Nothing happens without a record set (ov002
 * 0207386c == -1) or without an owner. */
typedef unsigned char u8;

typedef struct Ov016Piece {
    u8 pad_000[0x19c];
    u8 nKindByte;             /* 0x19c */
} Ov016Piece;

typedef struct Ov016Owner {
    u8 pad_000[0x80];
    u8 pieceList[0xc];        /* 0x80 */
} Ov016Owner;

typedef struct Ov016Follower {
    u8 pad_000[0x10];
    u8 nBucket;               /* 0x10 */
} Ov016Follower;

extern int  func_ov002_0207386c(void);                    /* record set state */
extern int  func_ov002_0207285c(int nBucket);             /* bucket -> seat slot */
extern Ov016Owner *func_ov002_02073880(int nSlot);        /* seat owner */
extern void *func_01fffd70(void *pList);                  /* List_First */
extern void *func_01fffd8c(void *pList);                  /* List_Next */
extern void func_ov233_020cc5a8(Ov016Piece *pPiece, int nKind);
extern void func_ov022_020888b8(int nA, int nB);

void func_ov016_020803b4(Ov016Follower *pSelf)
{
    Ov016Owner *pOwner;
    Ov016Piece **ppPiece;
    Ov016Piece *pPiece;

    if (func_ov002_0207386c() == -1) {
        return;
    }
    pOwner = func_ov002_02073880(func_ov002_0207285c(pSelf->nBucket));
    if (pOwner == 0) {
        return;
    }
    ppPiece = func_01fffd70(pOwner->pieceList);
    pPiece = (ppPiece == 0) ? 0 : *ppPiece;
    while (pPiece != 0) {
        if (pPiece->nKindByte == 'm') {
            func_ov233_020cc5a8(pPiece, pPiece->nKindByte);
            func_ov022_020888b8(0, 1);
            return;
        }
        ppPiece = func_01fffd8c(pOwner->pieceList);
        pPiece = (ppPiece == 0) ? 0 : *ppPiece;
    }
}
