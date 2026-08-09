typedef unsigned int u32;

/* NitroSDK fixed-destination word-send primitive. */
asm void MIi_CpuSend32(register const void *source,
                       register volatile void *destination, register u32 size)
{
    add     ip, r0, r2
sendNextWord:
    cmp     r0, ip
    ldmltia r0!, {r2}
    strlt   r2, [r1]
    blt     sendNextWord
    bx      lr
}
