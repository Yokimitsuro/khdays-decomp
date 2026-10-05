typedef struct {
    int nFlags;                         /* +0x00 */
    int nRate;                          /* +0x04 */
    int nPending;                       /* +0x08 */
} Ov002Session;

typedef int (*Ov002SessionProc)(void);

extern Ov002Session *NNSi_FndGetCurrentRootHeap(void);
extern unsigned long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int Ov002_StepSession(void);

/* Start a session: when the armed bit is set, clear the busy bit and hand back
 * the step routine. The current rate is recomputed either way. */
Ov002SessionProc Ov002_StartSession(void)
{
    Ov002SessionProc pfnStep;
    Ov002Session *pSession;

    pfnStep = 0;
    pSession = NNSi_FndGetCurrentRootHeap();

    if ((pSession->nFlags & 2) > 0) {
        pSession->nFlags &= ~4;
        pfnStep = Ov002_StepSession;
    }

    pSession->nRate = (int)func_02020368(OS_GetTick() << 6, 0x82ea);
    pSession->nPending = 0;

    return pfnStep;
}
