typedef struct {
    int nFlags;                         /* +0x00, bit 0 restart, bit 2 busy */
    int nRate;                          /* +0x04 */
    int nPending;                       /* +0x08 */
} Ov002Session;

typedef int (*Ov002SessionProc)(void);

extern Ov002Session *NNSi_FndGetCurrentRootHeap(void);
extern unsigned long long func_020031d4(void);
extern int func_02020368(unsigned long long value, unsigned int nDiv, int nMode);
extern void func_ov002_0206f25c(void);
extern int func_ov002_0206f124(void);

/* Step the session. A restart request hands back the start routine; otherwise
 * a busy session just refreshes its rate and an idle one is nudged. */
Ov002SessionProc func_ov002_0206f184(void)
{
    Ov002Session *pSession;
    int nFlags;

    pSession = NNSi_FndGetCurrentRootHeap();
    nFlags = pSession->nFlags;

    if ((nFlags & 1) > 0) {
        return func_ov002_0206f124;
    }

    if ((nFlags & 4) > 0) {
        pSession->nRate = func_02020368(func_020031d4() << 6, 0x82ea, 0);
        return 0;
    }

    func_ov002_0206f25c();
    return 0;
}
