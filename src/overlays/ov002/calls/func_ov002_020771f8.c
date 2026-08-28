typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Ov002PieceClass {
    char pad000[0x6c];
    int nReplayLimit;           /* +0x6c */
} Ov002PieceClass;

typedef struct Ov002PieceElement {
    char pad000[8];
    Ov002PieceClass *pOwner;    /* +0x08 */
    char pad00c[6];
    u16 wFlags;                 /* +0x12 */
    char pad014[0x28];
    short aAnimTracks[1];       /* +0x3c */
    char pad03e[0x172];
    int aClock[1];              /* +0x1b0 */
    s16 nDropScale;             /* +0x1b4 */
    u8 bDropsOn : 1;            /* +0x1b6 bit 0 */
    u8 nReplays : 7;            /* +0x1b6 bits 1..7 */
    u8 nAnimCounter;            /* +0x1b7 */
} Ov002PieceElement;

typedef void *Ov002StateFn(void *pElement);

extern int func_ov002_0207687c(void);           /* the module's time scale */
extern int func_ov002_0207c700(char *pElement, short *pTable, int nDelta,
                               int nFlag, int nLimit, int *pCounter);
extern void func_ov002_02076bd8(char *pElement, int nMode);
extern void func_ov002_0207c618(short *pAnim, int nTrack, int nFrame);
extern void func_0202af1c(short *pAnim);
extern void func_0202aa9c(short *pAnim);

extern Ov002StateFn func_ov002_0207cea4;

/* The recovery state a defeated piece sits in.  Each tick advances the piece's
   clock; while the animation is still running the piece just renders and stays
   here, and returning zero is what keeps it in this state.

   When the clock runs out the replay counter steps.  There are nReplays goes in
   all, packed into the top seven bits of the same byte whose bit 0 gates the
   payout; once they are spent the piece is put to sleep and the idle handler
   takes over.  Otherwise the next track is bound and played, and the piece
   comes back here for another go. */
Ov002StateFn *func_ov002_020771f8(Ov002PieceElement *pElement)
{
    Ov002PieceClass *pClass;
    int nScale;
    int bClockDone;
    u8 nCount;

    pClass = pElement->pOwner;
    nScale = func_ov002_0207687c();
    bClockDone = 0;
    if (func_ov002_0207c700((char *)pElement, pElement->aAnimTracks, nScale, 0,
                            pClass->nReplayLimit, pElement->aClock) == 0) {
        bClockDone = 1;
    }

    if ((pElement->wFlags & 4) != 0) {
        func_0202aa9c(pElement->aAnimTracks);
    }

    if (bClockDone != 0) {
        nCount = ++pElement->nAnimCounter;
        if (nCount < pElement->nReplays) {
            if ((pElement->wFlags & 4) != 0) {
                func_ov002_0207c618(pElement->aAnimTracks, nCount, 0);
                func_0202af1c(pElement->aAnimTracks);
            }
        } else {
            func_ov002_02076bd8((char *)pElement, 0);
            return func_ov002_0207cea4;
        }
    }
    return 0;
}
