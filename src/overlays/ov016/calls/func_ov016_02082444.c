/* func_ov016_02082444 -- Ov016_HazardStep: state function of the hazard.  Nothing outside a
 * running scene (ov002 0206b758).  On the host (local player index 0, 02030788) while no sync
 * message is pending (+0x2bc == 0) it looks for a target: when the definition asks for it
 * (bit 0 of def +0x70) it walks the class tables of the target slot (def +0x72, every slot
 * 0..31 when -1; ov002 02076468) and the pieces of the target index (def +0x73, every piece up
 * to the table's count +0x50 when -1; ov002 02076a80) and hands the hazard's hit to the first
 * piece whose class has a hit handler (def +0x2c) that accepts it (Ov016_DeliverHitToTarget
 * 020823b0), remembering that slot and index.  When the resulting on/off state differs from
 * the hazard's (+0x2b8) a kind-0xc message {1, state, slot, index} is queued on the piece
 * (ov002 020766e0); once it goes out the state is stored and the sync byte set to 2.  Always
 * stays (0). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov016HazardDef {
    u8 pad_00[0x70];
    u16 nTargetFlags;         /* 0x70: bit 0 = look for a target */
    char nTargetSlot;         /* 0x72: -1 = every slot */
    char nTargetIndex;        /* 0x73: -1 = every piece */
} Ov016HazardDef;

typedef struct Ov016Hazard {
    u8 pad_000[0x8];
    Ov016HazardDef *pDef;     /* 0x08 */
    u8 pad_00c[0x2b8 - 0xc];
    int bOn;                  /* 0x2b8 */
    u8  nSyncState;           /* 0x2bc: 0 idle, 1 fresh, 2 message pending */
} Ov016Hazard;

typedef struct Ov016PieceDef {
    u8 pad_00[0x2c];
    void *pfnHit;             /* 0x2c */
} Ov016PieceDef;

typedef struct Ov016Piece {
    u8 pad_00[0x8];
    Ov016PieceDef *pDef;      /* 0x08 */
} Ov016Piece;

typedef struct Ov016ClassTable {
    u8 pad_00[0x50];
    u16 nCount;               /* 0x50 */
} Ov016ClassTable;

typedef struct Ov016HazardMessage {
    u8  nKind;                /* 0x00 */
    u8  pad_01[3];
    int bOn;                  /* 0x04 */
    u16 nSlot;                /* 0x08 */
    u16 nIndex;               /* 0x0a */
} Ov016HazardMessage;

extern int  func_ov002_0206b758(void);                                /* scene running? */
extern int  func_02030788(void);                                      /* Session_GetLocalPlayerIndex */
extern Ov016ClassTable *func_ov002_02076468(int nSlot);              /* class table of a slot */
extern Ov016Piece *func_ov002_02076a80(Ov016ClassTable *pTable, int nIndex); /* piece of a table */
extern int  func_ov016_020823b0(Ov016Hazard *pSelf, Ov016Piece *pTarget); /* Ov016_DeliverHitToTarget */
extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */

void *func_ov016_02082444(Ov016Hazard *pSelf)
{
    Ov016HazardDef *pDef;
    Ov016Piece *pPiece;
    int bOn;
    int nSlot;
    Ov016ClassTable *pTable;
    u16 nSlotHit;
    Ov016HazardMessage message;
    int nIndex;
    u16 nIndexHit;
    int nIndexEnd;
    int nSlotEnd;

    nSlotHit = 0xffff;
    nIndexHit = 0xffff;
    pDef = pSelf->pDef;
    if (func_ov002_0206b758() == 0) {
        return 0;
    }
    if (func_02030788() == 0 && pSelf->nSyncState == 0) {
        bOn = 0;
        if (pDef->nTargetFlags & 1) {
            nSlot = 0;
            nSlotEnd = 0x20;
            if (pDef->nTargetSlot >= 0) {
                nSlot = pDef->nTargetSlot;
                nSlotEnd = pDef->nTargetSlot + 1;
            }
            for (; nSlot < nSlotEnd; nSlot++) {
                pTable = func_ov002_02076468(nSlot);
                if (pTable != 0) {
                    nIndex = 0;
                    nIndexEnd = pTable->nCount;
                    if (pDef->nTargetIndex >= 0) {
                        nIndex = pDef->nTargetIndex;
                        nIndexEnd = pDef->nTargetIndex + 1;
                    }
                    for (; nIndex < nIndexEnd; nIndex++) {
                        pPiece = func_ov002_02076a80(pTable, nIndex);
                        if (pPiece != 0 && pPiece->pDef->pfnHit != 0 && func_ov016_020823b0(pSelf, pPiece)) {
                            nSlotHit = nSlot;
                            nIndexHit = nIndex;
                            bOn = 1;
                            break;
                        }
                    }
                    if (bOn) {
                        break;
                    }
                }
            }
        }
        if (pSelf->bOn != bOn) {
            message.nKind = 1;
            message.bOn = bOn;
            message.nSlot = nSlotHit;
            message.nIndex = nIndexHit;
            if (func_ov002_020766e0(pSelf, &message, 0xc) != 0) {
                pSelf->bOn = bOn;
                pSelf->nSyncState = 2;
            }
        }
    }
    return 0;
}
