/* ov022: place the actor's slot effect and start it.
 *
 * Runs only while the effect is live. It takes the actor's own position,
 * raises it, and steps one unit backwards along the facing the caller hands
 * in, so the effect sits behind the actor rather than inside it. Both of the
 * effect's animation tracks are rebound and rewound to frame zero, the scale
 * is set to the caller's value on all three axes, and the state byte marks it
 * running for the finisher that follows in the same tick.
 */

typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct SlotEffect {
    u8 nFlags;                   /* 0x0000, bit 0 marks the effect live */
    u8 nState;                   /* 0x0001 */
    u8 pad0002[2];
    u8 anim;                     /* 0x0004 */
    u8 pad0005[0xa3];
    VecFx32 vecPos;              /* 0x00a8 */
    VecFx32 vecScale;            /* 0x00b4 */
    u8 pad00c0[0x24];
    u8 blkChannels;              /* 0x00e4 */
};

/* Shared sin/cos table: [i*2] = sin, [i*2+1] = cos. */
extern short data_0203d210[];

extern void VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void func_0202accc(void *pAnim, int nTrack, void *pBlk, int nGroup);
extern void func_01fff774(void *pAnim, int nTrack, int nFrame);

void func_ov022_02092710(struct SlotEffect *pEffect, const VecFx32 *pvecPos,
                         int nAngle, int nScale)
{
    VecFx32 vPos;
    VecFx32 vOffset;
    int nIdx;

    if ((pEffect->nFlags & 1) == 0) {
        return;
    }
    vPos = *pvecPos;
    nIdx = nAngle >> 4;
    vOffset.x = -data_0203d210[nIdx * 2];
    vOffset.y = 0;
    vOffset.z = -data_0203d210[nIdx * 2 + 1];
    vPos.y = vPos.y + 0xf00;
    VEC_Add(&vPos, &vOffset, &vPos);
    pEffect->vecPos = vPos;
    func_0202accc(&pEffect->anim, 0, &pEffect->blkChannels, 0);
    func_0202accc(&pEffect->anim, 2, &pEffect->blkChannels, 0);
    func_01fff774(&pEffect->anim, 0, 0);
    func_01fff774(&pEffect->anim, 2, 0);
    pEffect->vecScale.z = nScale;
    pEffect->vecScale.y = nScale;
    pEffect->vecScale.x = nScale;
    pEffect->nState = 1;
}
