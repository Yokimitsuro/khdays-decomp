/* func_ov016_02080480 -- Ov016_FollowerStep: per-frame update of the follower, only on the seat
 * that owns its bucket (ov002 0207285c == 0206ba48).  It advances its accumulator (02080440),
 * takes the trailed player's position (ov022 020881f8, held at height 0x333) and facing
 * (02088254), turns its own angle (+0x1b8) toward the player's by 1/turn-rate of the wrapped
 * difference (snapping within 0x40), stands 0x1800 behind the player along that angle
 * (the target point), moves the node there (0202b450) with the facing angle + 0x8000 (+0xa8,
 * flag bit 5) and unit scale, and accumulates the hold timer (+0x1b4) by the frame delta.
 * When the player pieces no longer hold (020802e4) the timer restarts and the player's bit is
 * cleared from the held mask kept in bits 1..15 of the follower's GameState field; when the
 * timer passes the duration (+0x1b0) the player's bit is set and, if that completes all four
 * bits, Ov016_FollowerComplete (020803b4) fires.  Always returns 0. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016Follower {
    u8 pad_000[0x10];
    u8  nBucket;              /* 0x10 */
    u8  pad_011[3];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017[0x28 - 0x17];
    u32 nNodeFlagsA;          /* 0x28: bit 5 = facing set */
    u16 nNodeFlagsB;          /* 0x2c */
    u8  pad_02e[0xa8 - 0x2e];
    u16 nNodeFacing;          /* 0xa8 */
    u8  pad_0aa[0xdc - 0xaa];
    VecFx32 scale;            /* 0xdc */
    u8  pad_0e8[0x1b0 - 0xe8];
    int nDuration;            /* 0x1b0 */
    int nHoldTimer;           /* 0x1b4 */
    int nAngle;               /* 0x1b8 */
    u8  pad_1bc[0x1c4 - 0x1bc];
    u16 nTurnRate;            /* 0x1c4 */
    u8  nPlayer;              /* 0x1c6 */
} Ov016Follower;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int  func_ov002_0207285c(int nBucket);                 /* bucket -> seat slot */
extern int  func_ov002_0206ba48(void);                        /* the seat being run */
extern void func_ov016_02080440(Ov016Follower *pSelf);
extern VecFx32 *func_ov022_020881f8(int nSeat);               /* where the seat is */
extern int  func_ov022_02088254(int nSeat);                   /* the seat's facing */
extern int  func_02020400(int nNumerator, int nDenominator);  /* _s32_div_f */
extern void func_0202b450(void *pTransform, VecFx32 *pVec);   /* Actor_SetVecAndSyncChild */
extern int  func_ov002_0207687c(void);                        /* frame delta */
extern int  func_ov016_020802e4(Ov016Follower *pSelf, VecFx32 *pFrom, VecFx32 *pAt);
extern int  func_020235d0(u16 nField, u8 nBit);               /* GameState_GetField */
extern void func_020235e8(u16 nField, u8 nBit, u16 nValue);   /* GameState_SetField */
extern void func_ov016_020803b4(Ov016Follower *pSelf);
extern const short data_0203d210[];                           /* FX_SinCosTable_ */

int func_ov016_02080480(Ov016Follower *pSelf)
{
    VecFx32 pos;
    VecFx32 target;
    int nPlayer;
    int nFacing;
    int nDelta;
    u32 nAngle;
    u16 nHeld;
    u32 nOld;
    int nNodeFacing;
    u32 nValue;
    u32 nState;

    if (func_ov002_0207285c(pSelf->nBucket) != func_ov002_0206ba48()) {
        return 0;
    }
    func_ov016_02080440(pSelf);
    nPlayer = pSelf->nPlayer;
    pos = *func_ov022_020881f8(nPlayer);
    pos.y = 0x333;
    nFacing = func_ov022_02088254(nPlayer);
    nDelta = nFacing - pSelf->nAngle;
    if (nDelta >= 0x8000) {
        nDelta -= 0x10000;
    }
    if (nDelta >= 0x8000) {
        nDelta -= 0x10000;
    }
    if (nDelta <= -0x8000) {
        nDelta += 0x10000;
    }
    if (nDelta <= -0x8000) {
        nDelta += 0x10000;
    }
    if (nDelta > 0x40 || nDelta < -0x40) {
        pSelf->nAngle += func_02020400(nDelta, pSelf->nTurnRate);
    } else {
        pSelf->nAngle = nFacing;
    }
    nAngle = pSelf->nAngle & 0xffff;
    pSelf->nAngle = nAngle;
    target.x = pos.x - FX_Mul(data_0203d210[((u16)(nAngle + 0x8000) >> 4) * 2], 0x1800);
    target.y = pos.y;
    target.z = pos.z - FX_Mul(data_0203d210[((u16)(pSelf->nAngle + 0x8000) >> 4) * 2 + 1], 0x1800);
    func_0202b450(&pSelf->nNodeFlagsA, &pos);
    nNodeFacing = pSelf->nAngle + 0x8000;
    if ((pSelf->nNodeFlagsA & 0x20) == 0) {
        pSelf->nNodeFacing = nNodeFacing;
        pSelf->nNodeFlagsB |= 0x20;
    }
    pSelf->scale.x = 0x1000;
    pSelf->scale.y = 0x1000;
    pSelf->scale.z = 0x1000;
    pSelf->nHoldTimer += func_ov002_0207687c();
    if (!func_ov016_020802e4(pSelf, &pos, &target)) {
        pSelf->nHoldTimer = 0;
        nState = func_020235d0(pSelf->nStateField, pSelf->nStateBit);
        nHeld = (u16)((nState & 0xfffe) >> 1) & ~(1 << pSelf->nPlayer);
        nState = func_020235d0(pSelf->nStateField, pSelf->nStateBit);
        func_020235e8(pSelf->nStateField, pSelf->nStateBit, (nState & 0xffff0001) | (nHeld << 1));
    }
    if (pSelf->nHoldTimer > pSelf->nDuration) {
        nState = func_020235d0(pSelf->nStateField, pSelf->nStateBit);
        nOld = (u16)((nState & 0xfffe) >> 1);
        nHeld = (u16)((1 << pSelf->nPlayer) | nOld);
        nState = func_020235d0(pSelf->nStateField, pSelf->nStateBit);
        func_020235e8(pSelf->nStateField, pSelf->nStateBit, (nState & 0xffff0001) | (nHeld << 1));
        if (nHeld != nOld && (nHeld & 0xf) == 0xf) {
            func_ov016_020803b4(pSelf);
        }
    }
    return 0;
}
