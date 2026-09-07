/* MobiClip: the frame pacing alarm -- one firing per decoded frame.
 *
 * Waits for the vertical blank to mark a frame as presented, then hands the
 * decoder the buffer that has just come free -- the front buffer index goes
 * through the stream's own callback to become an address. A firing that
 * arrives before the previous one was serviced re-arms one tick later and
 * gives up its turn.
 *
 * The next deadline comes from the frame count and the stream's time base
 * rather than from this firing, so rounding never accumulates.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

#define TICKS_PER_FRAME_NUMERATOR 0x000007fd88400000ULL

struct MobiClipFrameTimer {
    void *pDecoder;
    u8 alarm[0x2c];
    s64 nStartTick;
    u8 nState;
    u8 nFrontBuffer;
    u8 bPrimed;
    u8 pad003b;
    u32 pad003c;
    int nDecoded;
    u32 nConsumed;
    int nPresented;
    u64 nTimeBase;
    int (*pfnBufferForIndex)(int nIndex);
};

extern void func_ov024_02085080(void *pDecoder);
extern void func_ov024_0208505c(void *pDecoder, int nValue, int nCount, int nFlags);
extern void func_ov024_0208421c(struct MobiClipFrameTimer *pTimer);
extern s64 func_020031d4(void);
extern void OS_SetAlarm(void *pAlarm, u64 nTick, void *pfnHandler, void *pArg);

void func_ov024_0208421c(struct MobiClipFrameTimer *pTimer)
{
    int nAhead = pTimer->nDecoded - (int)pTimer->nConsumed;
    s64 nElapsed;
    u64 nDue;

    if (nAhead > 0) {
        if (nAhead <= 3 && pTimer->nState < 4) {
            func_ov024_02085080(pTimer->pDecoder);
        } else if (pTimer->bPrimed == 0) {
            OS_SetAlarm(pTimer->alarm, 1, (void *)&func_ov024_0208421c, pTimer);
            return;
        } else {
            func_ov024_0208505c(pTimer->pDecoder,
                                pTimer->pfnBufferForIndex((signed char)pTimer->nFrontBuffer),
                                0x100, 0);
            pTimer->bPrimed = 0;
        }
    } else if (pTimer->bPrimed == 0) {
        OS_SetAlarm(pTimer->alarm, 1, (void *)&func_ov024_0208421c, pTimer);
        return;
    } else {
        pTimer->bPrimed = 0;
    }

    pTimer->nConsumed++;
    nElapsed = func_020031d4() - pTimer->nStartTick;
    nDue = (pTimer->nConsumed + 1) * TICKS_PER_FRAME_NUMERATOR / pTimer->nTimeBase;
    OS_SetAlarm(pTimer->alarm, nDue - nElapsed,
                (void *)&func_ov024_0208421c, pTimer);
}
