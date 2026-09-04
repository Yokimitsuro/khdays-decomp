typedef unsigned int u32;
typedef signed int s32;

typedef void (*OSIrqFunction)(void *arg);

/* One 12-byte record per callback slot; see OSi_IrqCallback, which consumes it. */
typedef struct {
    OSIrqFunction pfnHandler;
    u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_020442a8[];
extern u32 data_027e0000;

/* The flat vector table sits at the very start of DTCM, one entry per interrupt bit. */
#define OSi_IrqTable ((OSIrqFunction *)&data_027e0000)

#define OS_IRQ_TABLE_MAX 22

/* Install one handler for every interrupt named in the mask.
 *
 * Most sources are plain entries in the DTCM vector table. The four DMA channels
 * and the four timers instead go through the callback slots, which OSi_IrqCallback
 * runs once and then clears; installing through here arms a slot to stay enabled
 * and carry no argument. The bit-to-slot mapping is the inverse of the bit table
 * in os_irq_callback_bits.c: bits 8..11 are DMA 0..3 and land in slots 0..3, bits
 * 3..6 are Timer 0..3 and land in slots 4..7.
 */
void OS_SetIrqFunction(u32 intrBits, OSIrqFunction function)
{
    s32 i;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1) {
        if (intrBits & 1) {
            OSiIrqSlot *slot = 0;

            if (i >= 8 && i <= 11) {
                slot = &data_020442a8[i - 8];
            } else if (i >= 3 && i <= 6) {
                slot = &data_020442a8[i + 1];
            } else {
                OSi_IrqTable[i] = function;
            }

            if (slot != 0) {
                slot->pfnHandler = function;
                slot->pArg = 0;
                slot->bKeepEnabled = 1;
            }
        }
    }
}
