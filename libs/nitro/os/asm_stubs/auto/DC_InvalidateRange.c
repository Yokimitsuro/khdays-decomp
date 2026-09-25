/* NitroSDK original assembly (libraries/os/src/os_cache.c). */

typedef int BOOL;
typedef unsigned int u32;

#define HW_CACHE_LINE_SIZE           32

asm void DC_InvalidateRange (register void * startAddr, register u32 nBytes)
{
    add r1, r1, r0
    bic r0, r0, #HW_CACHE_LINE_SIZE - 1
@1:
    mcr p15, 0, r0, c7, c6, 1
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, r1
    blt @1
    bx lr
}
