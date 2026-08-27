/*
 * Nudges the session once a frame while it sits idle in a waiting state.
 *
 * Nothing happens while the story flag is set, outside the three waiting
 * states, or while the nudge is disabled. Otherwise the local machine's busy
 * state decides which way it goes.
 *
 * Busy: the frame counter is reset, the busy notice is queued, and the stage
 * moves to one. Idle: a stage of minus one fires immediately, and a stage of
 * one counts frames until the timeout - sixty or ninety depending on the
 * setting - and fires when it is reached. Firing queues the idle notice and
 * puts the stage back to zero. Anything else waits another frame.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002IdleNudge {
    u8 nFlags;
    s8 nStage;
    u16 nTicks;
} Ov002IdleNudge;

typedef struct Ov002RootContext {
    char pad0000[0x8b58];
    int nState;
    char pad8b5c[0x1b0];
    Ov002IdleNudge nudge;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_02023588(int nFlagId);
extern int func_ov002_0206b758(void);
extern int func_01fffe14(void);
extern int func_ov002_0206b7d4(int nIndex);
extern int func_02023c40(void);
extern int func_ov002_0207299c(void);
extern int func_ov002_020729b4(void);
extern void func_02033770(int nArg, int nKind);
extern int func_020335c8(void);

void func_ov002_0206a11c(void)
{
    Ov002RootContext *pCtx;
    Ov002IdleNudge *pNudge;
    int bBusy;
    int bFire;
    u8 nLimit;

    pCtx = data_ov002_0207fa00;
    bBusy = 0;
    pNudge = &pCtx->nudge;
    if (func_02023588(0x20e3) != 0) {
        return;
    }
    if (pCtx->nState != 7 && pCtx->nState != 1 && pCtx->nState != 5) {
        return;
    }
    if ((pNudge->nFlags & 1) == 0) {
        return;
    }

    if (func_ov002_0206b758() != 0) {
        bBusy = func_ov002_0206b7d4(func_01fffe14());
    }

    if (bBusy == 0) {
        bFire = 0;
        if (pNudge->nStage == -1) {
            bFire = 1;
        } else if (pNudge->nStage == 1) {
            nLimit = (u8)(func_02023c40() == 1 ? 0x3c : 0x5a);
            if (pNudge->nTicks < nLimit) {
                pNudge->nTicks++;
                if (pNudge->nTicks >= nLimit) {
                    bFire = 1;
                }
            }
        }
        if (bFire == 0) {
            return;
        }
        func_02033770(func_ov002_0207299c(), 0x1e);
        pNudge->nStage = 0;
        return;
    }

    if (func_020335c8() != 0) {
        return;
    }
    pNudge->nTicks = 0;
    func_02033770(func_ov002_020729b4(), 0x1e);
    pNudge->nStage = 1;
}
