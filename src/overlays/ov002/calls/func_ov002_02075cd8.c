typedef struct {
    unsigned long long nLastTick;       /* +0x00 */
    int nPhase;                         /* +0x08 */
    int pad0c;
    int nPending;                       /* +0x10 */
} Ov002Blink;

extern Ov002Blink *data_ov002_0207fa18;

extern unsigned long long func_020031d4(void);
extern unsigned long long func_02020368(unsigned long long value, unsigned int nDiv,
                                        int nMode);
extern void func_ov002_02075c64(int nPhase);
extern void func_ov002_02075cac(void);

/* Flip the blink phase once the interval has elapsed, then remember the tick
 * and drain any pending work. */
void func_ov002_02075cd8(void)
{
    unsigned long long nNow;
    Ov002Blink *pBlink;

    nNow = func_020031d4();
    pBlink = data_ov002_0207fa18;

    if (func_02020368((nNow - pBlink->nLastTick) << 6, 0x82ea, 0) > 0x12c) {
        pBlink->nPhase ^= 1;
        func_ov002_02075c64(data_ov002_0207fa18->nPhase);
        pBlink = data_ov002_0207fa18;
        pBlink->nLastTick = nNow;
    }

    if (pBlink->nPending != 0) {
        func_ov002_02075cac();
    }
}
