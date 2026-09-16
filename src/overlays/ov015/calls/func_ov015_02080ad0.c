/* func_ov015_02080ad0 -- Ov015_SpotAssignPlayer: the spot's assign message.  When the
 * player's actor (01fffde0 of the message byte) is in interaction state 0xc (ov022
 * 020ad61c) that state is cleared (020ad5f4), the player is recorded in the class table
 * (+0x180), the owner pickup dropped (+0x54) and the nearest free entry of the spot's kind
 * table searched from the target (+0x30) within 0x400000 (02080884).  Without one the
 * rejected callback (+0x50) fires; otherwise the entry becomes current (+0x179), the
 * assigned callback (+0x48) fires with it and the live bit (bit 1 of +0x40) is dropped.
 * Always returns 0. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015PlayerActor {
    u8  pad_000[0x4ec];
    void *pSub;               /* 0x4ec */
} Ov015PlayerActor;

typedef struct Ov015SpotDef {
    u8  pad_000[0x179];
    s8  nCurrent;             /* 0x179 */
    u8  pad_17a[6];
    s8  nPlayer;              /* 0x180 */
} Ov015SpotDef;

typedef struct Ov015Spot {
    u8  pad_00[8];
    Ov015SpotDef *pDef;       /* 0x08 */
    u8  pad_0c[4];
    u8  nKind;                /* 0x10 */
    u8  pad_11[0x30 - 0x11];
    VecFx32 target;           /* 0x30 */
    void *pActor;             /* 0x3c */
    u8  nSpotFlags;           /* 0x40: bit 1 live */
    u8  pad_41[7];
    void (*pfnAssigned)(void *pActor, void *pSub, u8 nEntry); /* 0x48 */
    u8  pad_4c[4];
    void (*pfnRejected)(void *pActor, void *pSub);            /* 0x50 */
    void *pOwner;             /* 0x54 */
} Ov015Spot;

extern Ov015PlayerActor *func_01fffde0(int nPlayer);                       /* the player's actor */
extern int  func_ov022_020ad61c(void *pActor, int nState);                 /* actor in interaction state */
extern void func_ov022_020ad5f4(void *pActor, u16 nState, int bOn);        /* set / clear an interaction state */
extern int  func_ov015_02080884(Ov015Spot *pSpot, Ov015SpotDef *pDef, VecFx32 *pFrom, u32 nTable, int nRange, u16 *pVisited, int nDepth); /* nearest free entry */

int func_ov015_02080ad0(Ov015Spot *pSpot, u8 *pMessage, int nArg2, int nArg3)
{
    Ov015SpotDef *pDef;
    Ov015PlayerActor *pPlayer;
    u16 nVisited;
    int nEntry;

    pDef = pSpot->pDef;
    pPlayer = func_01fffde0(*pMessage);
    if (func_ov022_020ad61c(pPlayer, 0xc) != 0) {
        func_ov022_020ad5f4(pPlayer, 0xc, 0);
        pDef->nPlayer = *pMessage;
        pSpot->pOwner = 0;
        nVisited = 0;
        nEntry = func_ov015_02080884(pSpot, pDef, &pSpot->target, pSpot->nKind, 0x400000, &nVisited, 0);
        if (nEntry != -1) {
            pDef->nCurrent = nEntry;
            pSpot->pfnAssigned(pSpot->pActor, pPlayer->pSub, nEntry);
            pSpot->nSpotFlags &= ~2;
        } else {
            pSpot->pfnRejected(pSpot->pActor, pPlayer->pSub);
        }
    }
    return 0;
}
