/* NitroSDK original assembly (libraries/os/src/os_cache.c). */

typedef int BOOL;
typedef unsigned int u32;

#define HW_C7_CACHE_SET_NO_SHIFT     30
#define HW_CACHE_LINE_SIZE           32
#define HW_DCACHE_SIZE               0x1000

asm void DC_StoreAll (void)
{
    mov r1, #0
@1:
    mov r0, #0
@2:
    orr r2, r1, r0
    mcr p15, 0, r2, c7, c10, 2
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, #HW_DCACHE_SIZE / 4
    blt @2
    add r1, r1, #1 << HW_C7_CACHE_SET_NO_SHIFT
    cmp r1, #0
    bne @1
    bx lr
}
