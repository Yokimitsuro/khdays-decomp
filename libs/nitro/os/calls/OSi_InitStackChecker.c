/* NitroSDK libraries/os/src/os_interrupt.c: OS_SetIrqStackChecker. Plants the two canary words
 * at the bottom and top of the IRQ stack (the top of DTCM, below its 0x40-byte system area),
 * which OS_GetIrqStackStatus later checks. */
typedef unsigned int u32;

extern unsigned char data_027e0000[];          /* SDK_AUTOLOAD_DTCM_START */
extern void SDK_IRQ_STACKSIZE(void);           /* linker-defined: 0x800 */

#define HW_DTCM_IRQ_STACK_END           ((u32)data_027e0000 + 0x3f80)
#define OSi_IRQ_STACK_BOTTOM            HW_DTCM_IRQ_STACK_END
#define OSi_IRQ_STACK_TOP               (OSi_IRQ_STACK_BOTTOM - (u32)SDK_IRQ_STACKSIZE)
#define OSi_IRQ_STACK_CHECKNUM_BOTTOM   0xfddb597dUL
#define OSi_IRQ_STACK_CHECKNUM_TOP      0x7bf9dd5bUL

void OSi_InitStackChecker(void)
{
    /* 4, not sizeof(u32): the size_t operand makes mwcc share the DTCM base between the two stores */
    *(u32 *)(OSi_IRQ_STACK_BOTTOM - 4) = OSi_IRQ_STACK_CHECKNUM_BOTTOM;
    *(u32 *)(OSi_IRQ_STACK_TOP) = OSi_IRQ_STACK_CHECKNUM_TOP;
}
