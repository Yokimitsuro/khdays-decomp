typedef unsigned char u8;

/* The overlay's stopwatch.  Only the first three words matter here; the rest
 * of the context carries the total, the run, the split and the laps. */
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

extern long long func_020031d4(void);   /* the 64-bit tick counter */
/* The MSL divide.  The tree calls it by address rather than letting mwcc emit
 * its own _ll_sdiv reference. */
extern long long func_02020368(long long nValue, unsigned int nDiv, int nUnused);
extern int func_02030694(void);         /* Session_IsReady */
extern int func_02030670(void);         /* Session_IsActive */
extern unsigned int func_ov002_0206fb84(int nKind, unsigned short *pBuf);
extern void func_ov002_0206f788(int nCommand, int nDelta);

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
int func_ov002_0206f318(void)
{
    Ov002TickCtx *pCtx;
    Ov002TimerCommand cmd;
    int nNowMs;

    pCtx = data_ov002_0207fa08;
    nNowMs = (int)func_02020368(func_020031d4() << 6, 0x82ea, 0);
    if ((pCtx->nFlags & 4) > 0) {
        pCtx->nElapsed = 0;
    } else {
        pCtx->nElapsed = pCtx->nElapsed + (nNowMs - pCtx->nLastMs);
    }

    cmd.nCommand = 2;
    cmd.nDelta = pCtx->nElapsed;
    pCtx->nElapsed = 0;

    if (func_02030694()) {
        pCtx->nFlags |= 0x80;
    }
    if (func_02030670() == 0) {
        func_ov002_0206f788(cmd.nCommand, cmd.nDelta);
    } else {
        if (func_ov002_0206fb84(7, (unsigned short *)&cmd) == 0xffff) {
            return 0;
        }
    }
    return 1;
}
