extern void func_020056b4(int a, int b, int c);

asm void func_020128c0(void *p)
{
    mov r1, #0x4000000
    ldr r2, [r1]
    ldr r1, [r1]
    and r2, r2, #7
    tst r1, #8
    ldrb r1, [r0, r2]
    movne r0, #1
    moveq r0, #0
    cmp r0, #0
    movne r2, #1
    moveq r2, #0
    cmp r1, #8
    ldr ip, =func_020056b4
    subge r1, r1, #8
    mov r0, #1
    bx ip
}
