/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef int BOOL;
typedef unsigned int u32;
typedef unsigned int OSIntrMode;

#define HW_PSR_IRQ_FIQ_DISABLE       0xc0

asm OSIntrMode OS_DisableInterrupts_IrqAndFiq (void)
{
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_IRQ_FIQ_DISABLE
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_IRQ_FIQ_DISABLE
    bx lr
}
