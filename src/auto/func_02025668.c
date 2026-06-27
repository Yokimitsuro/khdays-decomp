asm void func_02025668(unsigned int *bits, int index)
{
    mov r2, r1, asr #4
    add r2, r1, r2, lsr #27
    and r1, r1, #0x1f
    mov r3, r2, asr #5
    rsb r2, r1, #0x1f
    mov r1, #1
    mvn r1, r1, lsl r2
    ldr r2, [r0, r3, lsl #2]
    and r1, r2, r1
    str r1, [r0, r3, lsl #2]
    bx lr
}
