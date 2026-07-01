asm void func_01ffa724(int s, const int *v, int *out)
{
    ldr r3, [r1]
    smull ip, r3, r0, r3
    mov ip, ip, lsr #0xc
    orr ip, ip, r3, lsl #20
    str ip, [r2]
    ldr r3, [r1, #4]
    smull ip, r3, r0, r3
    mov ip, ip, lsr #0xc
    orr ip, ip, r3, lsl #20
    str ip, [r2, #4]
    ldr r1, [r1, #8]
    smull r3, r1, r0, r1
    mov r0, r3, lsr #0xc
    orr r0, r0, r1, lsl #20
    str r0, [r2, #8]
    bx lr
}
