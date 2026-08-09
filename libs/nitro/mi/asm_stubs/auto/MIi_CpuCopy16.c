typedef unsigned int u32;

/* NitroSDK halfword copy primitive. */
asm void MIi_CpuCopy16(register const void *source,
                       register void *destination, register u32 size)
{
    mov     ip, #0
copyNextHalfword:
    cmp     ip, r2
    ldrlth  r3, [r0, ip]
    strlth  r3, [r1, ip]
    addlt   ip, ip, #2
    blt     copyNextHalfword
    bx      lr
}
