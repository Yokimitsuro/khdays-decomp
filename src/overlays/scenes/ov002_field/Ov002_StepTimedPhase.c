
/* The overlay's stopwatch.  Only the first three words matter here; the rest
 * of the context carries the total, the run, the split and the laps. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    int nFlags;             /* 0x00 */
    int nLastMs;            /* 0x04 */
    unsigned int nElapsed;  /* 0x08 */
} Ov002TickCtx;

/* The little command the phase step builds on its own frame.  Only the command
 * byte is filled in here; the rest is left as the frame found it, and the
 * session builder is handed the whole thing. */
typedef struct {
    u8 pad0000;
    u8 nCommand;            /* 0x01 */
    u8 pad0002[2];
    int nDelta;             /* 0x04 */
} Ov002TimerCommand;

extern Ov002TickCtx *data_ov002_0207fa08;

extern long long OS_GetTick(void);   /* the 64-bit tick counter */
/* The MSL divide.  The tree calls it by address rather than letting mwcc emit
 * its own _ll_sdiv reference. */
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern unsigned int Ov002_BuildSessionCommand(int nKind, unsigned short *pBuf);
extern void Ov002_ApplyTimerCommand(int nCommand, int nDelta);

/* Advances the timed phase by however long has passed, then reports it.
 *
 * The tick counter is turned into milliseconds the NitroSDK way -- times 64
 * over 33514 -- and the difference from the phase's start is added to what has
 * accrued.  A phase carrying flag 4 accrues nothing instead.
 *
 * The accrual is then handed over and cleared, so each call reports only its
 * own slice.  In a live session that goes out as command 7, and a sentinel of
 * 0xffff means the session refused it; otherwise it is applied locally.
 *
 * Answers zero only for that refusal, one every other time.
 */
int Ov002_StepTimedPhase(void)
{
    Ov002TickCtx *pCtx;
    Ov002TimerCommand cmd;
    int nNowMs;

    pCtx = data_ov002_0207fa08;
    nNowMs = (int)func_02020368(OS_GetTick() << 6, 0x82ea);
    if ((pCtx->nFlags & 4) > 0) {
        pCtx->nElapsed = 0;
    } else {
        pCtx->nElapsed = pCtx->nElapsed + (nNowMs - pCtx->nLastMs);
    }

    cmd.nCommand = 2;
    cmd.nDelta = pCtx->nElapsed;
    pCtx->nElapsed = 0;

    if (Session_IsReady()) {
        pCtx->nFlags |= 0x80;
    }
    if (Session_IsActive() == 0) {
        Ov002_ApplyTimerCommand(cmd.nCommand, cmd.nDelta);
    } else {
        if (Ov002_BuildSessionCommand(7, (unsigned short *)&cmd) == 0xffff) {
            return 0;
        }
    }
    return 1;
}
