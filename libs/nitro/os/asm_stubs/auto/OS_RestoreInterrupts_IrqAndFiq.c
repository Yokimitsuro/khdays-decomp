/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef int BOOL;
typedef unsigned int u32;
typedef unsigned int OSIntrMode;

#define HW_PSR_IRQ_FIQ_DISABLE       0xc0

asm OSIntrMode OS_RestoreInterrupts_IrqAndFiq (register OSIntrMode state)
{
    mrs r1, cpsr
    bic r2, r1, #HW_PSR_IRQ_FIQ_DISABLE
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #HW_PSR_IRQ_FIQ_DISABLE
    bx lr
}
