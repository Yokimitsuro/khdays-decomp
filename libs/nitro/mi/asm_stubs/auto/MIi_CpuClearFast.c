typedef unsigned int u32;

/* NitroSDK fast word-fill primitive. */
asm void MIi_CpuClearFast(register u32 value,
                          register void *destination, register u32 size)
{
    stmdb   sp!, {r4, r5, r6, r7, r8, r9}
    add     r9, r1, r2
    mov     ip, r2, lsr #5
    add     ip, r1, ip, lsl #5
    mov     r2, r0
    mov     r3, r2
    mov     r4, r2
    mov     r5, r2
    mov     r6, r2
    mov     r7, r2
    mov     r8, r2
clearNextBlock:
    cmp     r1, ip
    stmltia r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
    blt     clearNextBlock
clearNextWord:
    cmp     r1, r9
    stmltia r1!, {r0}
    blt     clearNextWord
    ldmia   sp!, {r4, r5, r6, r7, r8, r9}
    bx      lr
}
