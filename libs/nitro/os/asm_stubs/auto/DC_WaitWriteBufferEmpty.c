/* NitroSDK original assembly (libraries/os/src/os_cache.c). */

typedef int BOOL;
typedef unsigned int u32;

asm void DC_WaitWriteBufferEmpty (void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4
    bx lr
}
