typedef unsigned int u32;

/* NitroSDK startup clear primitive; preserves the fill value in r0. */
asm void INITi_CpuClear32(register u32 value, register void *destination,
                          register u32 size)
{
    add     ip, r1, r2
clearNextWord:
    cmp     r1, ip
    stmltia r1!, {r0}
    blt     clearNextWord
    bx      lr
}
