asm void func_02025640(unsigned int *bits, int index)
{
    mov r2, r1, asr #4
    add r2, r1, r2, lsr #27
    mov ip, r2, asr #5
    and r1, r1, #0x1f
    ldr r2, [r0, ip, lsl #2]
    rsb r3, r1, #0x1f
    mov r1, #1
    orr r1, r2, r1, lsl r3
    str r1, [r0, ip, lsl #2]
    bx lr
}
