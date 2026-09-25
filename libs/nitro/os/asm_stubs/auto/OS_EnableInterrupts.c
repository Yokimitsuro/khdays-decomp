/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef int BOOL;
typedef unsigned int u32;
typedef unsigned int OSIntrMode;

#define HW_PSR_IRQ_DISABLE           0x80

asm OSIntrMode OS_EnableInterrupts (void)
{
    mrs r0, cpsr
    bic r1, r0, #HW_PSR_IRQ_DISABLE
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_IRQ_DISABLE
    bx lr
}
