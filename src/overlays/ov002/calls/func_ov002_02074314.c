typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct Ov002Piece Ov002Piece;

typedef struct Ov002Owner {
    char pad000[0x80];
    char list[0xc];
} Ov002Owner;

extern int func_ov022_02088474(int nPeer);          /* peer -> owner slot */
extern Vec3 *func_ov022_020881f8(int nPeer);        /* where the peer is */
extern int func_ov002_0207386c(void);
extern Ov002Owner *func_ov002_02073880(int nSlot);
extern Ov002Piece **func_01fffd70(void *pList);     /* first */
extern Ov002Piece **func_01fffd8c(void *pList);     /* next */
extern int func_ov002_02074260(Ov002Piece *pPiece, const Vec3 *pPos, int nArg);

/* Asks every piece the peer owns whether it answers for the peer's position,
 * and stops at the first that does.
 *
 * The position is taken before anything is checked, so it is the peer's place
 * at the moment of asking rather than wherever it ends up.  A settled record
 * set, a peer with no owner slot, or a slot with no owner at all all answer no
 * without walking anything.
 */
int func_ov002_02074314(int nPeer, int nArg)
{
    Vec3 vPos;
    Ov002Piece **ppPiece;
    Ov002Piece *pPiece;
    Ov002Owner *pOwner;
    int nSlot;

    nSlot = func_ov022_02088474(nPeer);
    vPos = *func_ov022_020881f8(nPeer);

    if (func_ov002_0207386c() != -1 && nSlot >= 0
        && (pOwner = func_ov002_02073880(nSlot)) != 0) {
        ppPiece = func_01fffd70(pOwner->list);
        pPiece = (ppPiece == 0) ? 0 : *ppPiece;
        while (pPiece != 0) {
            if (func_ov002_02074260(pPiece, &vPos, nArg) != 0) {
                return 1;
            }
            ppPiece = func_01fffd8c(pOwner->list);
            pPiece = (ppPiece == 0) ? 0 : *ppPiece;
        }
    }
    return 0;
}
