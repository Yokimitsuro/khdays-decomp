extern volatile int data_02046444;

asm void func_0200dcf0(void)
{
    ldr r12, =data_02046444
loop:
    ldr r0, [r12, #0]
    cmp r0, #1
    beq loop
    bx lr
}
