/* NitroSDK original assembly (libraries/os/src/os_protectionRegion.c). */

typedef int BOOL;
typedef unsigned int u32;

asm void OS_SetProtectionRegion1 (u32 param)
{
    mcr p15, 0, r0, c6, c1, 0
    bx lr
}
