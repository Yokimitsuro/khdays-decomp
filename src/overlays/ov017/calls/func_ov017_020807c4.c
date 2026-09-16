/* func_ov017_020807c4 -- Ov017_ItemGivenStep: state function of an item that a player has
 * taken.  The timer (+0x1b0) advances by the frame delta (ov002 0207687c).  In state 5, at
 * 0xc000, the piece moves to state 6 and the host (02030788 == 0), inside a running scene
 * (ov002 0206b758), hands the item over: in a session (02030670) by queueing a type-3
 * message (kind 4, the peers' handlers do the rest), otherwise by calling the player's actor
 * sub-object hook at +0x1bc directly with the spawn id, the key entry's low flag byte (+0x42)
 * and its key (+0x40) (entry from ov002 0206d144 / 0206d194 on the item key +0x1b6).  At
 * 0x1d000 the item is spent: bit 1 of its GameState field is set, its taken field / bit
 * (+0x1ba / +0x1bc) written 1, the piece retired (ov002 02076bd8), state 7, the host queues
 * a type-4 message and the terminal state (ov002 0207cea4) is returned.  Otherwise 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov017ItemMessage {
    u8   nType;               /* 0x00 */
    u8   pad_01[3];
} Ov017ItemMessage;

typedef struct Ov017Item {
    u8   pad_000[0x14];
    u16  nStateField;         /* 0x014: GameState field */
    u8   nStateBit;           /* 0x016 */
    u8   pad_017[0x1b0 - 0x17];
    int  nTimer;              /* 0x1b0 */
    u8   nState;              /* 0x1b4 */
    u8   pad_1b5;
    short nItemKey;           /* 0x1b6 */
    u8   nPlayer;             /* 0x1b8 */
    char nSpawnId;            /* 0x1b9 */
    u16  nTakenField;         /* 0x1ba */
    u8   nTakenBit;           /* 0x1bc */
} Ov017Item;

typedef struct Ov017KeyEntry {
    u8   pad_00[0x40];
    u16  nKey;                /* 0x40 */
    short nFlags;             /* 0x42 */
} Ov017KeyEntry;

typedef struct Ov017PlayerSub {
    u8   pad_000[0x1bc];
    void (*pfnGiveItem)(struct Ov017PlayerSub *pSub, int nSpawnId, int nFlags, int nKey); /* 0x1bc */
} Ov017PlayerSub;

typedef struct Ov017PlayerActor {
    u8   pad_000[0x4ec];
    Ov017PlayerSub *pSub;     /* 0x4ec */
} Ov017PlayerActor;

extern int   func_ov002_0207687c(void);                               /* frame delta */
extern int   func_02030788(void);                                     /* Session_GetLocalPlayerIndex */
extern int   func_ov002_0206b758(void);                               /* scene running? */
extern Ov017PlayerActor *func_01fffde0(int nPlayer);                  /* the player's actor */
extern int   func_ov002_0206d144(short nKey);                         /* key -> entry index */
extern Ov017KeyEntry *func_ov002_0206d194(short nIndex);              /* entry index -> entry */
extern int   func_02030670(void);                                     /* Session_IsActive */
extern int   func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern int   func_020235d0(u16 nField, u8 nBit);                      /* GameState_GetField */
extern void  func_020235e8(u16 nField, u8 nBit, u16 nValue);          /* GameState_SetField */
extern void  func_ov002_02076bd8(void *pPiece, int nMode);            /* retire a piece */
extern void *func_ov002_0207cea4(void *pPiece);                       /* terminal state */

void *func_ov017_020807c4(Ov017Item *pSelf)
{
    Ov017ItemMessage msgGive;
    Ov017ItemMessage msgDone;
    Ov017PlayerActor *pActor;
    Ov017KeyEntry *pEntry;
    int nDelta;
    int nState;
    u8 nSpawn;
    int nFlags;
    int nKey;

    nDelta = func_ov002_0207687c();
    pSelf->nTimer += nDelta;
    if (pSelf->nState == 5 && pSelf->nTimer >= 0xc000) {
        pSelf->nState = 6;
        if (func_02030788() == 0 && func_ov002_0206b758() != 0) {
            pActor = func_01fffde0(pSelf->nPlayer);
            pEntry = func_ov002_0206d194(func_ov002_0206d144(pSelf->nItemKey));
            if (func_02030670() != 0) {
                msgGive.nType = 3;
                func_ov002_020766e0(pSelf, &msgGive, 4);
            } else {
                nFlags = pEntry->nFlags & 0xff;
                nKey = pEntry->nKey;
                nSpawn = pSelf->nSpawnId;
                if (pActor->pSub->pfnGiveItem != 0) {
                    pActor->pSub->pfnGiveItem(pActor->pSub, nSpawn, nFlags, nKey);
                }
            }
        }
    }
    if (pSelf->nTimer + nDelta >= 0x1d000) {
        nState = func_020235d0(pSelf->nStateField, pSelf->nStateBit);
        func_020235e8(pSelf->nStateField, pSelf->nStateBit, (nState & 0xffff0001) | 2);
        func_020235e8(pSelf->nTakenField, pSelf->nTakenBit, 1);
        func_ov002_02076bd8(pSelf, 0);
        pSelf->nState = 7;
        if (func_02030788() == 0) {
            msgDone.nType = 4;
            func_ov002_020766e0(pSelf, &msgDone, 4);
        }
        return func_ov002_0207cea4;
    }
    return 0;
}
