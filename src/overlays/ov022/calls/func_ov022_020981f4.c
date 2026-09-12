/* Ov022_StepIdleActor -- one frame of an actor standing idle; returns the
 * state change it made, or 0.
 *
 * On the local machine (player index 0) the actor's flag-2 bit 0 goes up. The
 * move rate takes the fast or slow value by the global speed flag. Then, by
 * the actor's flags: bit 9 of the second word tries state 0xc if its follow
 * block agrees; bit 14 tries state 8 if its slot block agrees; otherwise the
 * pending action is tried and, when nothing came of it, an actor holding the
 * 0x800 button without bit 4 of its first word (and either without bit 36 or
 * without bit 7 of the second) goes to state 8 when the slot block agrees and
 * the aim angle is set, or to state 0xb when the follow block agrees.
 *
 * A state change arms the hold timer; otherwise an actor with input bit 2
 * takes the fast or slow move and turn rates by the same global flag.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* Ov022Actor */
struct Actor {
    u64 nFlags;                      /* 0x0000 */
    u8 pad0008[0x10];
    u16 nButtons;                    /* 0x0018 */
    u8 pad001a[0xa];
    u32 nInputMask;                  /* 0x0024 */
    u8 pad0028[0x43c];
    u64 nFlags2;                     /* 0x0464 */
    u8 pad046c[0x44];
    int nMoveRate;                   /* 0x04b0 */
    u8 pad04b4[4];
    int nWalkSpeed;                   /* 0x04b8 */
    u8 pad04bc[0xc];
    int nHoldTimer;                  /* 0x04c8 */
    u8 pad04cc[0xba4];
    u8 slotBlk[0x11c];               /* 0x1070 */
    u8 blkFollow[1];                 /* 0x118c */
    u8 pad118d[0x192f];
    int nAimAngle;                   /* 0x2abc */
};

#define FLAG_BIT4 (1ULL << 4)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG2_BIT0 (1ULL << 0)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT9 (1ULL << 9)
#define FLAG2_BIT14 (1ULL << 14)
#define BUTTON_0x800 0x800
#define INPUT_BIT2 0x4
#define RATE_FAST 0x1200
#define RATE_SLOW 0xc00
#define TURN_FAST 0x4cd
#define TURN_SLOW 0x333
#define HOLD_FRAMES 0x3000
#define STATE_8 8
#define STATE_B 0xb
#define STATE_C 0xc
#define NO_ANGLE (-1)

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick: picks the fast recoil and rates */

extern int func_02030788(void);
extern int func_ov022_020926f8(u8 *pBlk);
extern int func_ov022_020928c0(u8 *pBlk);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);
extern int func_ov022_020983ec(struct Actor *pActor, int nArg);

int func_ov022_020981f4(struct Actor *pActor)
{
    int nResult;
    int bFast;

    nResult = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT0;
    }
    pActor->nMoveRate = data_ov022_020b2eb0 ? RATE_FAST : RATE_SLOW;
    if ((pActor->nFlags2 & FLAG2_BIT9) != 0) {
        if (func_ov022_020926f8(pActor->slotBlk) != 0) {
            nResult = func_ov022_020a35f4(pActor, STATE_C);
        }
    } else if ((pActor->nFlags2 & FLAG2_BIT14) != 0) {
        if (func_ov022_020928c0(pActor->blkFollow) != 0) {
            nResult = func_ov022_020a35f4(pActor, STATE_8);
        }
    } else {
        nResult = func_ov022_020983ec(pActor, 0);
        if (nResult == 0 && (pActor->nButtons & BUTTON_0x800) == BUTTON_0x800
            && (pActor->nFlags & FLAG_BIT4) == 0
            && ((pActor->nFlags & FLAG_BIT36) == 0 || (pActor->nFlags2 & FLAG2_BIT7) == 0)) {
            if (func_ov022_020928c0(pActor->blkFollow) != 0 && pActor->nAimAngle != NO_ANGLE) {
                nResult = func_ov022_020a35f4(pActor, STATE_8);
            } else if (func_ov022_020926f8(pActor->slotBlk) != 0) {
                nResult = func_ov022_020a35f4(pActor, STATE_B);
            }
        }
    }
    if (nResult != 0) {
        pActor->nHoldTimer = HOLD_FRAMES;
    }
    if (nResult == 0 && (pActor->nInputMask & INPUT_BIT2) != 0) {
        bFast = data_ov022_020b2eb0;
        pActor->nMoveRate = bFast ? RATE_FAST : RATE_SLOW;
        pActor->nWalkSpeed = bFast ? TURN_FAST : TURN_SLOW;
    }
    return nResult;
}
