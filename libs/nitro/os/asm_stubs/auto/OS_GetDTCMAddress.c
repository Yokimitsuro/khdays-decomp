/* NitroSDK original assembly (libraries/os/src/os_tcm.c). */

typedef int BOOL;
typedef unsigned int u32;

#define OSi_TCM_REGION_BASE_MASK     0xfffff000

asm u32 OS_GetDTCMAddress (void)
{
    mrc p15, 0, r0, c9, c1, 0
    ldr r1, = OSi_TCM_REGION_BASE_MASK
    and r0, r0, r1
    bx lr
}
