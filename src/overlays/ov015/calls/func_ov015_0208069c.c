/* func_ov015_0208069c -- Ov015_SpotDriveActor: while the spot holds an actor (+0x3c),
 * refresh the actor's node against the spot's target (+0x30, ov107 020c5c54).  When the
 * spot is armed (bit 0 of +0x40), the class table names a current entry (+0x179 >= 0) and
 * the spot has an occupied callback (+0x4c): if the actor has arrived (bit 2 of its +0x40)
 * the callback is fired with the arriving player's sub-actor (01fffde0 of +0x180, +0x4ec)
 * and the entry id, and the entry's pickup (entry +0x8, via 020807f4) has its position
 * handler invoked three times; otherwise the spot is marked pending (bit 6 of +0x40). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02 */
    u8  pad_03[5];
    void *pPickup;            /* 0x08 */
    u8  pad_0c[0x18 - 0x0c];
} Ov015SpotEntry;

typedef struct Ov015SpotDef {
    u8  pad_000[0x179];
    s8  nCurrent;             /* 0x179: current entry id */
    u8  pad_17a[6];
    s8  nPlayer;              /* 0x180: player index */
} Ov015SpotDef;

typedef struct Ov015DrivenActor {
    u8  pad_00[0x40];
    int nMoveBits0 : 2;       /* 0x40 */
    int bArrived : 1;         /* 0x40: bit 2 = arrived */
} Ov015DrivenActor;

typedef struct Ov015PlayerActor {
    u8  pad_000[0x4ec];
    void *pSub;               /* 0x4ec */
} Ov015PlayerActor;

typedef struct Ov015Spot {
    u8  pad_00[8];
    Ov015SpotDef *pDef;       /* 0x08 */
    u8  pad_0c[4];
    u8  nKind;                /* 0x10 */
    u8  pad_11[0x30 - 0x11];
    VecFx32 target;           /* 0x30 */
    Ov015DrivenActor *pActor; /* 0x3c */
    u8  nSpotFlags;           /* 0x40: bit 0 armed, bit 6 pending */
    u8  pad_41[0xb];
    void (*pfnOccupied)(Ov015DrivenActor *pActor, void *pSub, u8 nEntry); /* 0x4c */
} Ov015Spot;

extern void func_ov107_020c5c54(Ov015DrivenActor *pActor, VecFx32 *pTarget, int nArg2, int nArg3);
extern Ov015PlayerActor *func_01fffde0(int nPlayer);                                /* the player's actor */
extern Ov015SpotEntry *func_ov015_020807f4(Ov015Spot *pSpot, Ov015SpotDef *pDef, int nTable, int nId, int bByKey);
extern VecFx32 *func_ov002_02076cc8(void *pPiece);                                  /* the piece's position handler */

void func_ov015_0208069c(Ov015Spot *pSpot, int nArg1, int nArg2, int nArg3)
{
    Ov015SpotDef *pDef;
    Ov015SpotEntry *pEntry;
    void *pPickup;

    pDef = pSpot->pDef;
    if (pSpot->pActor != 0) {
        func_ov107_020c5c54(pSpot->pActor, &pSpot->target, nArg2, nArg3);
        if ((pSpot->nSpotFlags & 1) && pDef->nCurrent >= 0 && pSpot->pfnOccupied != 0 && pSpot->pActor != 0) {
            if (pSpot->pActor->bArrived) {
                pSpot->pfnOccupied(pSpot->pActor, func_01fffde0(pDef->nPlayer)->pSub, *(u8 *)&pDef->nCurrent);
                pEntry = func_ov015_020807f4(pSpot, pDef, pSpot->nKind, pDef->nCurrent, 0);
                if (pEntry != 0) {
                    pPickup = pEntry->pPickup;
                    func_ov002_02076cc8(pPickup);
                    func_ov002_02076cc8(pPickup);
                    func_ov002_02076cc8(pPickup);
                }
            } else {
                pSpot->nSpotFlags |= 0x40;
            }
        }
    }
}
