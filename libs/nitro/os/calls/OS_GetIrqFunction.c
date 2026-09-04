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

/* Return the handler installed for the lowest interrupt named in the mask.
 *
 * This is the read side of OS_SetIrqFunction and uses the same bit-to-slot map:
 * bits 8..11 are DMA 0..3 in slots 0..3 and bits 3..6 are Timer 0..3 in slots 4..7,
 * while every other bit is a plain entry of the DTCM vector table.
 */
OSIrqFunction OS_GetIrqFunction(u32 intrBits)
{
    s32 i;
    OSIrqFunction *entry = OSi_IrqTable;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1, entry++) {
        if (intrBits & 1) {
            if (i >= 8 && i <= 11) {
                return data_020442a8[i - 8].pfnHandler;
            }
            if (i >= 3 && i <= 6) {
                return data_020442a8[i + 1].pfnHandler;
            }
            return *entry;
        }
    }
    return 0;
}
