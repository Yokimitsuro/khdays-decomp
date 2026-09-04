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

/* The four timers occupy interrupt bits 3..6 and callback slots 4..7, so their
   part of the table starts four records in. */
#define OS_IRQ_TIMER0_BIT  3
#define OSi_TimerSlots     (&data_020442a8[4])

/* Arm one timer's one-shot callback.
 *
 * Unlike the DMA path this always marks the slot as staying enabled and discards
 * what OS_EnableIrqMask reports: a timer keeps running, so the source is meant to
 * stay armed whether or not it already was.
 */
void OSi_EnterTimerCallback(u32 timerNo, OSIrqFunction function, void *arg)
{
    OSi_TimerSlots[timerNo].pfnHandler = function;
    OSi_TimerSlots[timerNo].pArg = arg;

    OS_EnableIrqMask(1 << (timerNo + OS_IRQ_TIMER0_BIT));

    OSi_TimerSlots[timerNo].bKeepEnabled = 1;
}
