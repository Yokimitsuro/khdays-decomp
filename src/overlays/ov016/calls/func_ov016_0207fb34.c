/* func_ov016_0207fb34 -- Ov016_LiftStep: state function of a lift.  Works on a copy of the
 * position (+0xe0), which the sequence node (+0x254) mirrors; a cleared trigger flag
 * (GameState field / bit +0x2e4 / +0x2e6) resets the state (+0x2b8) to 0.  States: 0 takes
 * the home position (+0x2e8) and clears the counters; 1 waits for the trigger flag; 2 (host
 * only) queues a type-4 message and stays until it goes out; 3 idles (a peer waiting); 4 sets
 * the descent speed (-speed * frame delta, +0x2c8); 5 descends until the bottom (+0x2d8); 6
 * (host) queues a type-8 message; 7 idles; 8 rests at the bottom and clears the timer (+0x2bc);
 * 9 counts the wait (+0x2e0) then jumps to 10; 10 (host) queues a type-0xc message; 11 idles;
 * 12 sets the ascent speed; 13 ascends until the top (+0x2d4); 14 (host) queues a type-0x10
 * message; 15 idles; 16 rests at the top; 17 counts the wait then returns to state 2.  The
 * transform (+0x38) is put at the position (0202b450) and the sequence node (+0x1b0) drawn
 * (0202aa9c) while the model is bound (bit 2 of +0x12).  Always 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016LiftMessage {
    u8   nType;               /* 0x00 */
    u8   pad_01[3];
} Ov016LiftMessage;

typedef struct Ov016Lift {
    u8   pad_000[0x12];
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound */
    u8   pad_014[0x38 - 0x14];
    u8   transform[0xe0 - 0x38]; /* 0x038 */
    VecFx32 position;         /* 0x0e0 */
    u8   pad_0ec[0x1b0 - 0xec];
    u8   seqNode[0x254 - 0x1b0]; /* 0x1b0 */
    VecFx32 seqPosition;      /* 0x254 */
    u8   pad_260[0x2b8 - 0x260];
    char nState;              /* 0x2b8 */
    u8   pad_2b9[3];
    int  nTimer;              /* 0x2bc */
    int  nWord2c0;            /* 0x2c0 */
    int  nWord2c4;            /* 0x2c4 */
    int  nVelocity;           /* 0x2c8 */
    int  nWord2cc;            /* 0x2cc */
    int  nWord2d0;            /* 0x2d0 */
    int  nTop;                /* 0x2d4 */
    int  nBottom;             /* 0x2d8 */
    int  nSpeed;              /* 0x2dc */
    int  nWait;               /* 0x2e0 */
    u16  nTriggerField;       /* 0x2e4 */
    u8   nTriggerBit;         /* 0x2e6 */
    u8   pad_2e7;
    VecFx32 home;             /* 0x2e8 */
} Ov016Lift;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int  func_020235d0(u16 nField, u8 nBit);                       /* GameState_GetField */
extern int  func_02030788(void);                                      /* Session_GetLocalPlayerIndex */
extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern int  func_ov002_0207687c(void);                                /* frame delta */
extern void func_0202b450(void *pTransform, VecFx32 *pVec);           /* Actor_SetVecAndSyncChild */
extern void func_0202aa9c(void *pNode);                               /* Scene_DrawNode */

void *func_ov016_0207fb34(Ov016Lift *pSelf)
{
    VecFx32 position;
    Ov016LiftMessage msgStart;
    Ov016LiftMessage msgBottom;
    Ov016LiftMessage msgRise;
    Ov016LiftMessage msgTop;
    int bOk;

    position = pSelf->position;
    pSelf->seqPosition = position;
    if (func_020235d0(pSelf->nTriggerField, pSelf->nTriggerBit) == 0) {
        pSelf->nState = 0;
    }
    switch (pSelf->nState) {
    case 0:
        position = pSelf->home;
        pSelf->nWord2c4 = 0;
        pSelf->nVelocity = 0;
        pSelf->nWord2cc = 0;
        pSelf->nTimer = 0;
        pSelf->nState++;
    case 1:
        if (func_020235d0(pSelf->nTriggerField, pSelf->nTriggerBit) != 0) {
            pSelf->nState++;
        }
        break;
    case 2:
        if (func_02030788() == 0) {
            msgStart.nType = 4;
            if (func_ov002_020766e0(pSelf, &msgStart, 4) == 0) {
                return 0;
            }
        }
        pSelf->nState = 3;
        break;
    case 3:
        break;
    case 4:
        pSelf->nVelocity = FX_Mul(-pSelf->nSpeed, func_ov002_0207687c());
        pSelf->nState++;
    case 5:
        position.y += pSelf->nVelocity;
        if (position.y > pSelf->nBottom) {
            break;
        }
        position.y = pSelf->nBottom;
        pSelf->nState++;
    case 6:
        bOk = 1;
        if (func_02030788() == 0) {
            msgBottom.nType = 8;
            if (func_ov002_020766e0(pSelf, &msgBottom, 4) == 0) {
                bOk = 0;
            }
        }
        if (bOk) {
            pSelf->nState++;
        }
        break;
    case 7:
        break;
    case 8:
        position.y = pSelf->nBottom;
        pSelf->nVelocity = 0;
        pSelf->nTimer = 0;
        pSelf->nState++;
    case 9:
        pSelf->nTimer += func_ov002_0207687c();
        if (pSelf->nTimer >= pSelf->nWait) {
            pSelf->nState = 10;
        }
        break;
    case 10:
        if (func_02030788() == 0) {
            msgRise.nType = 0xc;
            if (func_ov002_020766e0(pSelf, &msgRise, 4) == 0) {
                return 0;
            }
        }
        pSelf->nState = 11;
        break;
    case 11:
        break;
    case 12:
        pSelf->nVelocity = FX_Mul(pSelf->nSpeed, func_ov002_0207687c());
        pSelf->nState++;
    case 13:
        position.y += pSelf->nVelocity;
        if (position.y < pSelf->nTop) {
            break;
        }
        position.y = pSelf->nTop;
        pSelf->nState++;
    case 14:
        bOk = 1;
        if (func_02030788() == 0) {
            msgTop.nType = 0x10;
            if (func_ov002_020766e0(pSelf, &msgTop, 4) == 0) {
                bOk = 0;
            }
        }
        if (bOk) {
            pSelf->nState++;
        }
        break;
    case 15:
        break;
    case 16:
        position.y = pSelf->nTop;
        pSelf->nVelocity = 0;
        pSelf->nTimer = 0;
        pSelf->nState++;
    case 17:
        pSelf->nTimer += func_ov002_0207687c();
        if (pSelf->nTimer >= pSelf->nWait) {
            pSelf->nState = 2;
        }
        break;
    }
    func_0202b450(pSelf->transform, &position);
    if (pSelf->nPieceFlags & 4) {
        func_0202aa9c(pSelf->seqNode);
    }
    return 0;
}
