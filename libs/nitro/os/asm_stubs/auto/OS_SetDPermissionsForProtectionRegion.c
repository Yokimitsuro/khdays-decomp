/* NitroSDK original assembly (libraries/os/src/os_protectionRegion.c). */

typedef int BOOL;
typedef unsigned int u32;

asm void OS_SetDPermissionsForProtectionRegion (register u32 setMask, register u32 flags)
{
    mrc p15, 0, r2, c5, c0, 2
    bic r2, r2, r0
    orr r2, r2, r1
    mcr p15, 0, r2, c5, c0, 2
    bx lr
}
