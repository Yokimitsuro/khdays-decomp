typedef struct {
    int nFlags;                         /* +0x00 */
    int nRate;                          /* +0x04 */
    int nPending;                       /* +0x08 */
} Ov002Session;

typedef int (*Ov002SessionProc)(void);

extern Ov002Session *NNSi_FndGetCurrentRootHeap(void);
extern unsigned long long func_020031d4(void);
extern int func_02020368(unsigned long long value, unsigned int arg2, int arg3);
extern int func_ov002_0206f184(void);

/* Start a session: when the armed bit is set, clear the busy bit and hand back
 * the step routine. The current rate is recomputed either way. */
Ov002SessionProc func_ov002_0206f124(void)
{
    Ov002SessionProc pfnStep;
    Ov002Session *pSession;

    pfnStep = 0;
    pSession = NNSi_FndGetCurrentRootHeap();

    if ((pSession->nFlags & 2) > 0) {
        pSession->nFlags &= ~4;
        pfnStep = func_ov002_0206f184;
    }

    pSession->nRate = func_02020368(func_020031d4() << 6, 0x82ea, 0);
    pSession->nPending = 0;

    return pfnStep;
}
