/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef int BOOL;
typedef unsigned int u32;
typedef unsigned int OSProcMode;

#define HW_PSR_CPU_MODE_MASK         0x1f

asm OSProcMode OS_GetProcMode (void)
{
    mrs r0, cpsr
    and r0, r0, #HW_PSR_CPU_MODE_MASK
    bx lr
}
