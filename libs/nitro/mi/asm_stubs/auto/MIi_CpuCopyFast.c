typedef unsigned int u32;

/* NitroSDK fast word-copy primitive. */
asm void MIi_CpuCopyFast(register const void *source,
                         register void *destination, register u32 size)
{
    stmdb   sp!, {r4, r5, r6, r7, r8, r9, r10}
    add     r10, r1, r2
    mov     ip, r2, lsr #5
    add     ip, r1, ip, lsl #5
copyNextBlock:
    cmp     r1, ip
    ldmltia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    stmltia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
    blt     copyNextBlock
copyNextWord:
    cmp     r1, r10
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt     copyNextWord
    ldmia   sp!, {r4, r5, r6, r7, r8, r9, r10}
    bx      lr
}
