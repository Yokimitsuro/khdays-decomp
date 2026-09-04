typedef unsigned int u32;

typedef void (*OSIrqFunction)(void *arg);

/* One 12-byte record per callback slot; see OSi_IrqCallback, which consumes it. */
typedef struct {
    OSIrqFunction pfnHandler;
    u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_020442a8[];
extern u32 OS_EnableIrqMask(u32 mask);

/* The four DMA channels occupy interrupt bits 8..11 and callback slots 0..3. */
#define OS_IRQ_DMA0_BIT 8

/* Arm one DMA channel's one-shot callback.
 *
 * OS_EnableIrqMask returns the enable word as it stood before, so masking it with
 * this source's own bit records whether the channel was already enabled. That is
 * exactly what OSi_IrqCallback consults to decide whether to disable it again.
 */
void OSi_EnterDmaCallback(u32 dmaNo, OSIrqFunction function, void *arg)
{
    u32 mask = 1 << (dmaNo + OS_IRQ_DMA0_BIT);

    data_020442a8[dmaNo].pfnHandler = function;
    data_020442a8[dmaNo].pArg = arg;
    data_020442a8[dmaNo].bKeepEnabled = OS_EnableIrqMask(mask) & mask;
}
