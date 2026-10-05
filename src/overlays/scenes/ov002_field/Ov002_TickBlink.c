typedef struct {
    unsigned long long nLastTick;       /* +0x00 */
    int nPhase;                         /* +0x08 */
    int pad0c;
    int nPending;                       /* +0x10 */
} Ov002Blink;

extern Ov002Blink *data_ov002_0207fa18;

extern unsigned long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void Ov002_DrawTileCursor2x2(int nPhase);
extern void Ov002_UploadHudTileRow(void);

/* Flip the blink phase once the interval has elapsed, then remember the tick
 * and drain any pending work. */
void Ov002_TickBlink(void)
{
    unsigned long long nNow;
    Ov002Blink *pBlink;

    nNow = OS_GetTick();
    pBlink = data_ov002_0207fa18;

    if (func_02020368((nNow - pBlink->nLastTick) << 6, 0x82ea) > 0x12c) {
        pBlink->nPhase ^= 1;
        Ov002_DrawTileCursor2x2(data_ov002_0207fa18->nPhase);
        pBlink = data_ov002_0207fa18;
        pBlink->nLastTick = nNow;
    }

    if (pBlink->nPending != 0) {
        Ov002_UploadHudTileRow();
    }
}
