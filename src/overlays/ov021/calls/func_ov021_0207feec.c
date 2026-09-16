/* func_ov021_0207feec -- Ov021_PrizeBoxStep: state function of the prize box, switching on
 * its state (+0x1b8).  0 (closed): the idle animation loops (Ov021_PrizeBoxAdvanceFrame
 * 0207fa7c).  2 (the open request was accepted): plays track 1 (the length from the
 * 02080f18 table, Ov021_PrizeBoxPlayAnim 0207fa40) and waits in 3 for it to end, then
 * either replays it (+0x1bd set, once) or returns to the closed track 0 and state 0.  5
 * (opened): sends the box its own "taken" notice (ov002 020767ec), state 7, releases the
 * render node (0202bc30), marks the box opened (bit 0 of +0x1b9) and hands out the prize
 * (the class entry at +0x78 + 6 * the prize index +0x1be): an item (type 0) makes the host
 * submit session command 0x10 {spawn id +0x1bb, the item index of the key (ov002 0206d144),
 * bucket, position} (ov002 0206fb84); munny (type 1) drops (value * 3 / 4096) of kinds 0, 2
 * and 3 at the position (ov002 02077cec); a keyed object (type 2) is revealed (ov002
 * 02073ed0, bit 1 of +0x1b9).  7 (taken): plays track 2, leaves the room (bit 3 of +0x12),
 * state 8, and spawns the box's effect at the position (slot 0x3f in mission 0x41d, ov002
 * 0206b84c, else 0x38; 02033d0c).  8: once track 2 ends, state 9 and the terminal state
 * (ov002 0207cea4).  1, 4 and 6 wait.  Then, while the model is bound (bit 2 of +0x12), the
 * node (+0x3c) is drawn (0202aa9c).  Returns 0. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021Prize {
    char  nType;              /* 0x00: 0 item, 1 munny, 2 keyed object, 3 nothing */
    u8    pad_01;
    short nValue;             /* 0x02: item key, amount or object key */
    u8    bFlag;              /* 0x04 */
    u8    pad_05;
} Ov021Prize;

typedef struct Ov021PrizeBoxDef {
    u8   pad_00[0x78];
    Ov021Prize aPrize[1];     /* 0x78 */
} Ov021PrizeBoxDef;

typedef struct Ov021ItemCommand {
    u8   nByte0;              /* 0x00 (the command kind goes here) */
    u8   nLow : 2;            /* 0x01 */
    u8   nBucket : 6;
    char nSpawnId;            /* 0x02 */
    u8   nItem;               /* 0x03 */
    u8   nByte4;              /* 0x04 */
    u8   pad_05[3];
    VecFx32 position;         /* 0x08 */
} Ov021ItemCommand;

typedef struct Ov021PrizeBox {
    u8   pad_000[8];
    Ov021PrizeBoxDef *pDef;   /* 0x008 */
    u8   pad_00c[4];
    u8   nBucket;             /* 0x010 */
    u8   pad_011;
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound, bit 3 = in the room */
    u8   pad_014[0x2c - 0x14];
    u8   renderNode[0x3c - 0x2c]; /* 0x02c */
    u16  nNodeFlagsB;         /* 0x03c: the model node */
    u8   pad_03e[0xe0 - 0x3e];
    VecFx32 position;         /* 0x0e0 */
    u8   pad_0ec[0x1b0 - 0xec];
    int  nFrame;              /* 0x1b0 */
    int  nLength;             /* 0x1b4 */
    u8   nState;              /* 0x1b8 */
    u8   nFlags;              /* 0x1b9: bit 0 opened, bit 1 object revealed */
    u8   nSlot;               /* 0x1ba */
    char nSpawnId;            /* 0x1bb */
    char nTrack;              /* 0x1bc */
    char bReplay;             /* 0x1bd */
    char nPrize;              /* 0x1be */
} Ov021PrizeBox;

extern int   func_ov002_0207687c(void);                               /* frame delta */
extern int   func_ov021_0207fa7c(Ov021PrizeBox *pSelf, void *pNode, int nDelta, int bLoop); /* Ov021_PrizeBoxAdvanceFrame */
extern void  func_ov021_0207fa40(Ov021PrizeBox *pSelf, void *pNode, int nTrack, int nLength, int nFrame); /* Ov021_PrizeBoxPlayAnim */
extern void  func_ov002_020767ec(void *pPiece);                       /* the piece was taken */
extern void  func_0202bc30(void *pNode);                              /* release the node's resources */
extern int   func_02030788(void);                                     /* Session_GetLocalPlayerIndex */
extern int   func_ov002_0206d144(short nKey);                         /* key -> entry index */
extern int   func_ov002_0206fb84(int nKind, void *pCommand);          /* Ov002_BuildSessionCommand */
extern void  func_ov002_02077cec(const u8 *aAmount, int nCtxIndex, const VecFx32 *pPlace); /* spawn the drops */
extern void  func_ov002_02073ed0(int nKey, int bShow, int nPriority);  /* show / hide a keyed object's node */
extern int   func_ov002_0206b84c(void);                               /* the mission id */
extern int   func_02033d0c(int nSlot, int nId, VecFx32 *pPos, u16 nFlags); /* Slot_Spawn */
extern void  func_0202aa9c(void *pNode);                              /* Scene_DrawNode */
extern void *func_ov002_0207cea4(void *pPiece);                       /* terminal state */
extern const s8 data_ov021_02080f18[];                                /* track lengths in frames */

void *func_ov021_0207feec(Ov021PrizeBox *pSelf)
{
    Ov021ItemCommand command;
    Ov021PrizeBoxDef *pDef;
    int nDelta;
    u8 nAmount;

    pDef = pSelf->pDef;
    nDelta = func_ov002_0207687c();
    switch (pSelf->nState) {
    case 0:
        func_ov021_0207fa7c(pSelf, &pSelf->nNodeFlagsB, nDelta, 1);
        break;
    case 1:
        break;
    case 2:
        pSelf->nTrack = 1;
        pSelf->nLength = data_ov021_02080f18[pSelf->nTrack] << 12;
        func_ov021_0207fa40(pSelf, &pSelf->nNodeFlagsB, pSelf->nTrack, pSelf->nLength, 0);
        pSelf->nState = 3;
        break;
    case 3:
        if (!func_ov021_0207fa7c(pSelf, &pSelf->nNodeFlagsB, nDelta, 0)) {
            if (pSelf->bReplay != 0) {
                func_ov021_0207fa40(pSelf, &pSelf->nNodeFlagsB, pSelf->nTrack, pSelf->nLength, 0);
                pSelf->bReplay = 0;
            } else {
                pSelf->nTrack = 0;
                pSelf->nLength = data_ov021_02080f18[pSelf->nTrack] << 12;
                func_ov021_0207fa40(pSelf, &pSelf->nNodeFlagsB, pSelf->nTrack, pSelf->nLength, 0);
                pSelf->nState = 0;
            }
        }
        break;
    case 4:
        break;
    case 5:
        func_ov002_020767ec(pSelf);
        pSelf->nState = 7;
        func_0202bc30(pSelf->renderNode);
        pSelf->nFlags |= 1;
        switch (pDef->aPrize[pSelf->nPrize].nType) {
        case 0:
            if (func_02030788() == 0) {
                command.nSpawnId = pSelf->nSpawnId;
                command.nItem = func_ov002_0206d144(pDef->aPrize[pSelf->nPrize].nValue);
                command.nBucket = pSelf->nBucket;
                command.position = pSelf->position;
                command.nLow = 1;
                command.nByte4 = 0;
                func_ov002_0206fb84(0x10, &command);
            }
            break;
        case 1: {
            u8 aDrop[6] = {0, 0, 0, 0, 0, 0};
            nAmount = (pDef->aPrize[pSelf->nPrize].nValue * 3) >> 12;
            aDrop[0] = nAmount;
            aDrop[2] = nAmount;
            aDrop[3] = nAmount;
            func_ov002_02077cec(aDrop, pSelf->nBucket, &pSelf->position);
            break;
        }
        case 2:
            func_ov002_02073ed0(pDef->aPrize[pSelf->nPrize].nValue, 1, -1);
            pSelf->nFlags |= 2;
            break;
        }
        break;
    case 6:
        break;
    case 7:
        pSelf->nTrack = 2;
        pSelf->nLength = data_ov021_02080f18[pSelf->nTrack] << 12;
        func_ov021_0207fa40(pSelf, &pSelf->nNodeFlagsB, pSelf->nTrack, pSelf->nLength, 0);
        pSelf->nPieceFlags &= ~8;
        pSelf->nState = 8;
        if (func_ov002_0206b84c() == 0x41d) {
            func_02033d0c(0x3f, 0, &pSelf->position, 0);
        } else {
            func_02033d0c(0x38, 0, &pSelf->position, 0);
        }
        break;
    case 8:
        if (!func_ov021_0207fa7c(pSelf, &pSelf->nNodeFlagsB, nDelta, 0)) {
            pSelf->nState = 9;
            return func_ov002_0207cea4;
        }
        break;
    }
    if (pSelf->nPieceFlags & 4) {
        func_0202aa9c(&pSelf->nNodeFlagsB);
    }
    return 0;
}
