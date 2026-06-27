extern char data_0204430c[];

asm void func_02001a94(void *target)
{
    ldr r1, =data_0204430c
    mov r2, #0
    ldr r1, [r1, #0x2c]
    b check
loop:
    mov r2, r1
    ldr r1, [r1, #0x68]
check:
    cmp r1, #0
    cmpne r1, r0
    bne loop
    cmp r2, #0
    ldrne r0, [r0, #0x68]
    strne r0, [r2, #0x68]
    bxne lr
    ldr r1, [r0, #0x68]
    ldr r0, =data_0204430c
    str r1, [r0, #0x2c]
    bx lr
}
