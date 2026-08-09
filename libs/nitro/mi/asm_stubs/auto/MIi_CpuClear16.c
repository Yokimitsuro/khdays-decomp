typedef unsigned short u16;
typedef unsigned int u32;

/* NitroSDK halfword clear primitive. */
asm void MIi_CpuClear16(register u16 value, register void *destination,
                        register u32 size)
{
    mov     r3, #0
clearNextHalfword:
    cmp     r3, r2
    strlth  r0, [r1, r3]
    addlt   r3, r3, #2
    blt     clearNextHalfword
    bx      lr
}
