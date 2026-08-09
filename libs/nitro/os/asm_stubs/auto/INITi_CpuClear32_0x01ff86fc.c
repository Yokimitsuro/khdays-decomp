typedef unsigned int u32;

/* Second linked copy of the NitroSDK startup clear primitive. */
asm void INITi_CpuClear32_0x01ff86fc(register u32 value,
                                    register void *destination,
                                    register u32 size)
{
    add     ip, r1, r2
clearNextWord:
    cmp     r1, ip
    stmltia r1!, {r0}
    blt     clearNextWord
    bx      lr
}
