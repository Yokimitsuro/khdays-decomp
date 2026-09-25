/* NitroSDK original assembly (libraries/os/src/os_protectionUnit.c). */

typedef int BOOL;
typedef unsigned int u32;

#define HW_C1_PROTECT_UNIT_ENABLE    0x00000001

asm void OS_EnableProtectionUnit (void)
{
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #HW_C1_PROTECT_UNIT_ENABLE
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}
