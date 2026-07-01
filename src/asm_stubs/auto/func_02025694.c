asm int func_02025694(int *r0, int r1)
{
    mov r2, r1, asr #4
    add r2, r1, r2, lsr #27
    mov r2, r2, asr #5
    and r1, r1, #0x1f
    ldr r0, [r0, r2, lsl #2]
    rsb r2, r1, #0x1f
    mov r1, #1
    and r0, r0, r1, lsl r2
    bx lr
}
