/* func_ov021_02080828 -- Ov021_EmblemFlyToPlayer: one frame of the collected emblem's flight
 * into its player (+0x2bc).  Inside a running scene (ov002 0206b758) it aims at the player's
 * actor sub-object target (01fffde0, sub at +0x4ec, target +0x190 raised by the height +0x70),
 * normalises the direction (VEC_Normalize 01ff8d18, which also gives the distance) and
 * tightens the spiral (+0x2be grows by frame delta / 16 up to 0x1000): once fully tightened
 * and closer than 0x800 the flight is over (1).  Otherwise the sideways component (the
 * direction turned a quarter, scaled by (0x1000 - spiral) * the turn direction +0x2bd) is added
 * to the direction scaled by the spiral (VEC_MultAdd), the result scaled by twice the distance
 * (at most 0x800) and applied for the frame delta to the position (+0x2a8), which the sequence
 * node (+0xc0) follows.  0 while flying. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021PlayerSub {
    u8   pad_000[0x70];
    int  nHeight;             /* 0x070 */
    u8   pad_074[0x190 - 0x74];
    VecFx32 target;           /* 0x190 */
} Ov021PlayerSub;

typedef struct Ov021PlayerActor {
    u8   pad_000[0x4ec];
    Ov021PlayerSub *pSub;     /* 0x4ec */
} Ov021PlayerActor;

typedef struct Ov021Emblem {
    u8   pad_000[0xc0];
    VecFx32 seqPosition;      /* 0x0c0 */
    u8   pad_0cc[0x2a8 - 0xcc];
    VecFx32 position;         /* 0x2a8 */
    u8   pad_2b4[8];
    char nPlayer;             /* 0x2bc */
    char nDirection;          /* 0x2bd: +1 / -1 */
    short nSpiral;            /* 0x2be: 0 (sideways) .. 0x1000 (straight) */
} Ov021Emblem;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int   func_ov002_0206b758(void);                               /* scene running? */
extern int   func_ov002_0207687c(void);                               /* frame delta */
extern Ov021PlayerActor *func_01fffde0(int nPlayer);                  /* the player's actor */
extern void  VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern int   func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);             /* VEC_Normalize, returns the length */
extern void  VEC_MultAdd(int nScale, VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

int func_ov021_02080828(Ov021Emblem *pSelf)
{
    VecFx32 side;
    VecFx32 dir;
    VecFx32 target;
    VecFx32 step;
    Ov021PlayerSub *pSub;
    int nDelta;
    int nDist;
    int nSpeed;

    if (func_ov002_0206b758() != 0) {
        nDelta = func_ov002_0207687c();
        pSub = func_01fffde0(pSelf->nPlayer)->pSub;
        target = pSub->target;
        target.y += pSub->nHeight;
        VEC_Subtract(&target, &pSelf->position, &dir);
        nDist = func_01ff8d18(&dir, &dir);
        pSelf->nSpiral += nDelta >> 4;
        if (pSelf->nSpiral > 0x1000) {
            pSelf->nSpiral = 0x1000;
        }
        if (pSelf->nSpiral >= 0x1000 && nDist < 0x800) {
            return 1;
        }
        side.x = FX_Mul(-dir.z, (0x1000 - pSelf->nSpiral) * pSelf->nDirection);
        side.z = FX_Mul(dir.x, (0x1000 - pSelf->nSpiral) * pSelf->nDirection);
        side.y = 0;
        VEC_MultAdd(pSelf->nSpiral, &dir, &side, &side);
        nSpeed = nDist * 2;
        if (nSpeed > 0x800) {
            nSpeed = 0x800;
        }
        step.x = FX_Mul(side.x, nSpeed);
        step.y = FX_Mul(side.y, nSpeed);
        step.z = FX_Mul(side.z, nSpeed);
        VEC_MultAdd(nDelta, &step, &pSelf->position, &pSelf->position);
        pSelf->seqPosition = pSelf->position;
    }
    return 0;
}
