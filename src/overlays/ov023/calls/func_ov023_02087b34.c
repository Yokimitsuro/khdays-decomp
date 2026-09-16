/* func_ov023_02087b34 -- Ov023_MotionAdvance: advance an actor's motion state (the block at +4
 * of the actor) by nStep: its sequence tracks are updated (0202a818 on +0x324), the control
 * word at +0x344 gets bit 0 and the animation is advanced (020279e0).  Then the nine track
 * slots (+0x42c, an index into the 0x58-byte tracks at +0x58 or -1) are scanned for the first
 * whose track position has a y of 0xcd or more; its slot index is returned, else -1. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023MotionTrack {
    VecFx32 vPos;             /* 0x00 */
    u8   pad_0c[0x58 - 0xc];
} Ov023MotionTrack;           /* 0x58 */

typedef struct Ov023MotionState {  /* at +4 of the actor */
    u8   pad_000[0x58];
    Ov023MotionTrack aTrack[1]; /* 0x058 */
    u8   pad_0b0[0x324 - 0xb0];
    u8   sequence[0x20];      /* 0x324 */
    u32  nAnimControl;        /* 0x344 */
    u8   pad_348[0x42c - 0x348];
    int  aTrackIndex[9];      /* 0x42c */
} Ov023MotionState;

extern void func_0202a818(void *pSequence, int nStep);              /* Sequence_UpdateTracks */
extern void func_020279e0(u32 *pAnimControl);                       /* Anim_Advance */

int func_ov023_02087b34(Ov023MotionState *pState, int nStep)
{
    VecFx32 vPos;
    int nResult;
    int i;
    int nTrack;

    nResult = -1;
    func_0202a818(pState->sequence, nStep);
    pState->nAnimControl |= 1;
    func_020279e0(&pState->nAnimControl);
    for (i = 0; i < 9; i++) {
        vPos.x = vPos.y = vPos.z = 0;
        nTrack = pState->aTrackIndex[i];
        if (nTrack != -1) {
            vPos = pState->aTrack[nTrack].vPos;
        }
        if (vPos.y >= 0xcd) {
            nResult = i;
            break;
        }
    }
    return nResult;
}
