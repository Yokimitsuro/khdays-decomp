/* Ov016_FollowerComplete -- Ov016_FollowerComplete: once every player has held its follower, walk
 * the seat owner's piece list (ov002 02073880 for the follower's bucket slot, list +0x80) and,
 * at the first piece whose kind byte (+0x19c) is 'm', fire the completion hooks (ov233
 * 020cc5a8 with the piece and its kind, then ov022 020888b8 with 0 / 1). Nothing happens without a record set (ov002
 * 0207386c == -1) or without an owner. */

#include "nitro/types.h"
#include "game/engine.h"

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
    u8 nRoom;               /* 0x10 */
} Ov016Follower;

extern int  Ov002_Event_GetField18(void);                    /* record set state */
extern int  Ov002_GetCtxTableByte(int nRoom);             /* bucket -> seat slot */
extern Ov016Owner *Ov002_GetPieceOwner(int nSlot);        /* seat owner */
extern void *List_First(void *pList);                  /* List_First */
extern void Ov233_NotifyPartsThenBase(Ov016Piece *pPiece, int nKind);
extern void func_ov022_020888b8(int nA, int nB);

void Ov016_FollowerComplete(Ov016Follower *pSelf)
{
    Ov016Owner *pOwner;
    Ov016Piece **ppPiece;
    Ov016Piece *pPiece;

    if (Ov002_Event_GetField18() == -1) {
        return;
    }
    pOwner = Ov002_GetPieceOwner(Ov002_GetCtxTableByte(pSelf->nRoom));
    if (pOwner == 0) {
        return;
    }
    ppPiece = List_First(pOwner->pieceList);
    pPiece = (ppPiece == 0) ? 0 : *ppPiece;
    while (pPiece != 0) {
        if (pPiece->nKindByte == 'm') {
            Ov233_NotifyPartsThenBase(pPiece, pPiece->nKindByte);
            func_ov022_020888b8(0, 1);
            return;
        }
        ppPiece = (Ov016Piece **)List_Next(pOwner->pieceList);
        pPiece = (ppPiece == 0) ? 0 : *ppPiece;
    }
}
